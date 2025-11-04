#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <limits> // For numeric_limits
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <cstdint>
#include <algorithm>
using namespace std;

// 定义一些常量，用于固定大小数组的长度
#define MAX_TITLE_LENGTH 256
#define MAX_AUTHORS_LENGTH 512
#define MAX_KEYWORDS_PER_PAPER 6 // 固定数量的关键词
#define MAX_KEYWORD_LENGTH 64    // 每个关键词的最大长度
#define MAX_ABSTRACT_LENGTH 1024
#define MAX_PAPERS 1000          // 全局顺序表的最大论文数量

/**
 * @brief 定义单个学术论文的数据结构。
 */
struct Paper {
    int id;                                             // 论文ID
    char title[MAX_TITLE_LENGTH];                       // 论文标题
    char authorsString[MAX_AUTHORS_LENGTH];             // 合并后的作者字符串，作者之间用 ';' 分隔
    char keywords[MAX_KEYWORDS_PER_PAPER][MAX_KEYWORD_LENGTH]; // 固定数量的关键词二维字符数组
    int actualKeywordCount;                             // 实际存储的关键词数量
    int year;                                           // 发表年份
    int citations;                                      // 引用次数
    char abstractSnippet[MAX_ABSTRACT_LENGTH];          // 摘要片段
};

/**
 * @brief 定义存储论文的顺序表结构。
 */
struct PaperList {
    Paper papers[MAX_PAPERS / 4]; // 固定大小的论文结构体数组
    int count;                // 当前存储的论文数量
    // 构造函数，初始化count为0
    PaperList() : count(0) {}
};

// 声明全局顺序表实例
PaperList paperList;

// 前置声明（BST 相关接口）
int getNewBSTNodeIndex();
void resetBST();
bool insertPaperIntoBST(const char* title, int paperIndex);
int searchBST(const char* title);
void buildBSTFromPapers();
void searchTitleInteractive();
// Hash table (by paper ID) 前置声明
int getNewHashNodeIndex();
bool insertIDIntoHashTable(int paperID, int paperIndex);
int searchHashByID(int paperID);
void buildHashFromPapers();
void searchByIDInteractive();
// KMP 前置声明
void buildNextArray(const string& pattern, vector<int>& next);
int kmpSearch(const string& text, const string& pattern, const vector<int>& next);
void searchKMPInteractive();
// Graph (paper association) 前置声明
void buildGraphFromPapers();
void bfsSearchRelatedInteractive();
// Top-N 推荐前置声明
void searchTopNInteractive();
// 排序函数前置声明
void sortByYearDesc();
void sortByCitationsDesc();
void sortByTitleAsc();
// 合并功能与显示辅助函数前置声明
PaperList createSampleNewPaperListByYearDesc();
PaperList mergeSortedPaperListsByYearDesc(const PaperList& a, const PaperList& b);
void displayPaperListBrief(const PaperList& pl);
// 前置声明需要的函数
void displayAllPapersBrief();
void addPaperInteractive();
void deletePaperInteractive();
bool savePapersToFile(const string& filename);


/**
 * @brief 从竖线分隔（|）的文件中加载论文数据到全局顺序表 paperList。
 * 支持首行表头，会自动跳过。
 *
 * @param filename 文件名（例如 "papers.txt"）
 * @return true 加载成功
 * @return false 加载失败
 */
bool loadPapersFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "无法打开文件：" << filename << endl;
        return false;
    }

    paperList.count = 0; // 重置全局顺序表
    string line;
    bool headerSkipped = false;

    while (getline(file, line)) {
        if (line.empty()) continue;

        // 跳过首行（表头）
        if (!headerSkipped) {
            headerSkipped = true;
            continue;
        }

        stringstream ss(line);
        string token;
        vector<string> fields;

        // 按竖线 '|' 分割
        while (getline(ss, token, '|')) {
            fields.push_back(token);
        }

        if (fields.size() < 12) {
            cerr << " 数据格式错误（字段数量不足）：" << line << endl;
            continue;
        }

        Paper p{};
        try {
            // 依次提取字段
            p.id = stoi(fields[0]);
            strncpy(p.title, fields[1].c_str(), MAX_TITLE_LENGTH - 1);
            strncpy(p.authorsString, fields[2].c_str(), MAX_AUTHORS_LENGTH - 1);

            // 提取关键词（字段 3~8）
            p.actualKeywordCount = 0;
            for (int i = 3; i <= 8; ++i) {
                if (i < fields.size() && !fields[i].empty()) {
                    strncpy(p.keywords[p.actualKeywordCount], fields[i].c_str(), MAX_KEYWORD_LENGTH - 1);
                    p.actualKeywordCount++;
                }
            }

            p.year = stoi(fields[9]);
            p.citations = stoi(fields[10]);
            strncpy(p.abstractSnippet, fields[11].c_str(), MAX_ABSTRACT_LENGTH - 1);

            // 加入全局表
            if (paperList.count < MAX_PAPERS) {
                paperList.papers[paperList.count++] = p;
            }
            else {
                cerr << "达到最大论文数量上限（" << MAX_PAPERS << "），停止加载。" << endl;
                break;
            }

        }
        catch (const exception& e) {
            cerr << "解析出错：" << e.what() << "（行：" << line << "）" << endl;
        }
    }

    file.close();

    // 加载完成后构建 BST（按标题索引）、哈希表（按ID索引）以及论文关联图以便快速查找和遍历
    buildBSTFromPapers();
    buildHashFromPapers();
    buildGraphFromPapers();

    cout << "共加载 " << paperList.count << " 篇论文。" << endl;
    return paperList.count > 0;
}


//使用模块化编程的思想，每个功能都应被视为一个独立的模块，
//实现在不同的源文件和头文件中，并通过 include 语句引入

// 在这里引入你实现的功能模块头文件，如：
//#include "Paper.h"


// 可在这里自由添加全局常量\变量
// #define MAX_PAPERS 1000   // 全局顺序表的最大论文数量

void displayMenu() {
    cout << "\n--- 学术文献管理与关联分析系统 ---" << endl;
    cout << "1. 加载论文数据" << endl;
    cout << "2. 显示所有论文 (简要信息)" << endl;
    cout << "3. 添加新论文" << endl;
    cout << "4. 删除论文" << endl;
    cout << "5. 保存当前数据到文件" << endl;
    cout << "6. 按ID查找论文" << endl;
    cout << "7. 按标题查找论文 (BST)" << endl;
    cout << "8. 按内容模糊查找论文 (KMP)" << endl;
    cout << "9. 按年份降序排序并显示" << endl;
    cout << "10. 按引用次数降序排序并显示" << endl;
    cout << "11. 按标题字母顺序排序并显示" << endl;
    cout << "12. 合并两个有序论文列表" << endl;
    cout << "13. 查找相关论文 (BFS)" << endl;
    cout << "14. 获取关键词推荐 (Top-N)" << endl;


    cout << "0. 退出" << endl;
    cout << "请输入您的选择: ";
}

int main() {//主函数中可以自由添加局部变量、交互输入信息
    cout << "=== 学术文献管理系统启动 ===" << endl;
    cout << "正在初始化..." << endl;
    //cout << "工作目录: " << filesystem::current_path().string() << endl << endl;

    int choice;
    bool dataLoaded = false;

    do {
        displayMenu();
        cin >> choice;

        // --- 输入验证和错误处理 ---
        if (cin.fail()) { // 如果输入失败（例如输入了非数字字符）
            cout << "无效的输入，请输入一个数字选项。" << endl;
            cin.clear(); // 清除错误标志
            // 忽略并丢弃当前行中所有剩余的无效输入，直到遇到换行符
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1; // 将 choice 设置为一个无效值，以便循环继续
            continue;    // 跳过本次循环的剩余部分，重新显示菜单
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1: { // 加载论文数据，数据文件名默认为 papers.txt
            if (loadPapersFromFile("papers.txt")) {
                dataLoaded = true; //加载成功后设置标志为true
                cout << "论文数据加载成功！" << endl;
            }
            else {
                cout << "论文数据加载失败！" << endl;
            }
            break;
        }
        case 2: {// 显示所有论文 (简要信息)
            if (dataLoaded) {
                //ToDo: 在此处调用显示所有论文的功能函数
                displayAllPapersBrief();
            }
            else {
                cout << "请先加载论文数据。" << std::endl;
            }
            break;
        }
        case 3: { // 添加新论文
            if (dataLoaded) {
                //ToDo: 在此处调用添加新论文的功能函数
                addPaperInteractive();
            }
            else {
                cout << "请先加载论文数据。" << std::endl;
            }
            break;
        }
        case 4: { // 删除论文
            if (dataLoaded) {
                //ToDo: 在此处调用删除论文的功能函数
                deletePaperInteractive();
            }
            else {
                cout << "请先加载论文数据。" << std::endl;
            }
            break;
        }
        case 5: { // 保存当前数据到文件
            if (dataLoaded) {
                //ToDo: 在此处调用保存数据的功能函数
                savePapersToFile("papers_saved.txt");
            }
            else {
                cout << "请先加载论文数据。" << std::endl;
            }
            break;
        }
        case 6: { // 按ID查找论文
            if (dataLoaded) {

                //ToDo: 在此处调用按ID查找论文的功能函数
                searchByIDInteractive();

            }
            else {
                cout << "请先加载论文数据。" << std::endl;
            }
            break;
        }
        case 7: { // 按标题查找论文 (BST)
            if (dataLoaded) {
                // 按 ID 查找论文（使用哈希表）
                searchTitleInteractive();

            }
            else {
                cout << "请先加载论文数据。" << std::endl;
            }
            break;
        }
        case 8: { // 按内容模糊查找论文 (KMP)
            if (dataLoaded) {
                // 调用交互式 KMP 搜索标题和摘要
                searchKMPInteractive();
            }
            else {
                cout << "请先加载论文数据。" << std::endl;
            }
            break;
        }
        case 9: // 按年份降序排序并显示
            if (dataLoaded) {
                sortByYearDesc();
                displayAllPapersBrief();
            }
            else {
                cout << "请先加载论文数据。" << std::endl;
            }
            break;
        case 10: // 按引用次数降序排序并显示
            if (dataLoaded) {
                sortByCitationsDesc();
                displayAllPapersBrief();
            }
            else {
                cout << "请先加载论文数据。" << std::endl;
            }
            break;
        case 11: // 按标题字母顺序排序并显示
            if (dataLoaded) {
                sortByTitleAsc();
                displayAllPapersBrief();
            }
            else {
                cout << "请先加载论文数据。" << std::endl;
            }
            break;
        case 12: { // 合并两个有序论文列表
            if (dataLoaded) {
                // 先确保全局列表按年份降序排序（作为示例标准）
                sortByYearDesc();
                // 创建一个示例的、已按年份降序排序的新导入列表
                PaperList newList = createSampleNewPaperListByYearDesc();
                // 合并两个已排序的列表（按年份降序）
                PaperList merged = mergeSortedPaperListsByYearDesc(paperList, newList);
                // 显示合并后的结果
                displayPaperListBrief(merged);
            }
            else {
                cout << "请先加载论文数据。" << std::endl;
            }
            break;
        }
        case 13: { // 查找相关论文 (BFS)
            if (dataLoaded) {
                // 交互式 BFS 查找相关论文
                bfsSearchRelatedInteractive();
            }
            else {
                cout << "请先加载论文数据。" << std::endl;
            }
            break;
        }
        case 14: { // 获取关键词推荐 (Top-N)
            if (dataLoaded) {
                // 交互式 Top-N 关键词推荐
                searchTopNInteractive();
            }
            else {
                cout << "请先加载论文数据。" << std::endl;
            }
            break;
        }
        case 0:
            cout << "感谢使用，再见！" << endl;
            cout << "\n按回车键退出..." << endl;
            cin.get();
            break;
        default:
            cout << "无效的选择，请重新输入。" << std::endl;
            break;
        }
    } while (choice != 0);

    return 0;
}



// 显示所有论文简要信息
void displayAllPapersBrief() {
    if (paperList.count == 0) {
        cout << "当前没有论文数据。" << endl;
        return;
    }
    cout << "\n--- 所有论文 (共 " << paperList.count << " 篇) ---" << endl;
    for (int i = 0; i < paperList.count; ++i) {
        Paper& p = paperList.papers[i];
        cout << "ID: " << p.id << " | 标题: " << p.title << " | 年份: " << p.year << " | 引用: " << p.citations << endl;
    }
}

// 添加新论文（交互式）
void addPaperInteractive() {
    if (paperList.count >= MAX_PAPERS) {
        cout << "顺序表已满，无法添加新论文。" << endl;
        return;
    }

    Paper p{};
    string tmp;

    cout << "请输入新论文 ID (整数): ";
    if (!(cin >> p.id)) {
        cout << "输入格式错误：ID 必须为整数。" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "请输入标题: ";
    getline(cin, tmp);
    strncpy(p.title, tmp.c_str(), MAX_TITLE_LENGTH - 1);
    p.title[MAX_TITLE_LENGTH - 1] = '\0';

    cout << "请输入合并后的作者字符串（作者之间用 ; 分隔）: ";
    getline(cin, tmp);
    strncpy(p.authorsString, tmp.c_str(), MAX_AUTHORS_LENGTH - 1);
    p.authorsString[MAX_AUTHORS_LENGTH - 1] = '\0';

    // 关键词数量输入
    int kcount = 0;
    cout << "请输入关键词数量 (0 - " << MAX_KEYWORDS_PER_PAPER << "): ";
    if (!(cin >> kcount)) {
        cout << "输入格式错误：关键词数量必须为整数。" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    if (kcount < 0) kcount = 0;
    if (kcount > MAX_KEYWORDS_PER_PAPER) kcount = MAX_KEYWORDS_PER_PAPER;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    p.actualKeywordCount = 0;
    for (int i = 0; i < kcount; ++i) {
        cout << "请输入第 " << (i + 1) << " 个关键词: ";
        getline(cin, tmp);
        strncpy(p.keywords[p.actualKeywordCount], tmp.c_str(), MAX_KEYWORD_LENGTH - 1);
        p.keywords[p.actualKeywordCount][MAX_KEYWORD_LENGTH - 1] = '\0';
        p.actualKeywordCount++;
    }

    cout << "请输入发表年份 (整数): ";
    if (!(cin >> p.year)) {
        cout << "输入格式错误：年份必须为整数。" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "请输入引用次数 (整数): ";
    if (!(cin >> p.citations)) {
        cout << "输入格式错误：引用次数必须为整数。" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "请输入摘要片段: ";
    getline(cin, tmp);
    strncpy(p.abstractSnippet, tmp.c_str(), MAX_ABSTRACT_LENGTH - 1);
    p.abstractSnippet[MAX_ABSTRACT_LENGTH - 1] = '\0';

    // 添加到顺序表末尾
    paperList.papers[paperList.count++] = p;
    cout << "论文添加成功。" << endl;

    // 将新论文插入 BST（增量插入）。如果插入失败且树已满，可选择触发完全重建。
    int newIndex = paperList.count - 1;
    if (!insertPaperIntoBST(p.title, newIndex)) {
        // 如果因容量等原因插入失败，尝试完全重建（作为回退策略）
        buildBSTFromPapers();
    }
    // 同步插入哈希表（ID -> 索引），作为按 ID 快速查找
    if (!insertIDIntoHashTable(p.id, newIndex)) {
        buildHashFromPapers();
    }
    // 重建/更新论文关联图（当前策略为完全重建，简单且安全）
    buildGraphFromPapers();
}

// 删除论文（按 ID）
void deletePaperInteractive() {
    if (paperList.count == 0) {
        cout << "当前没有论文数据可删除。" << endl;
        return;
    }
    cout << "请输入要删除的论文 ID: ";
    int id;
    if (!(cin >> id)) {
        cout << "输入格式错误：ID 必须为整数。" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int idx = -1;
    for (int i = 0; i < paperList.count; ++i) {
        if (paperList.papers[i].id == id) { idx = i; break; }
    }
    if (idx == -1) {
        cout << "未找到论文 ID " << id << "。" << endl;
        return;
    }

    // 向前移动覆盖
    for (int i = idx; i < paperList.count - 1; ++i) {
        paperList.papers[i] = paperList.papers[i + 1];
    }
    paperList.count--;
    cout << "论文 ID " << id << " 已删除。" << endl;
}

// 保存当前数据到文件
bool savePapersToFile(const string& filename) {
    ofstream ofs(filename);
    if (!ofs.is_open()) {
        cerr << "文件写入失败：无法打开 " << filename << endl;
        return false;
    }

    // 写表头
    ofs << "ID|Title|AuthorsString|Keyword1|Keyword2|Keyword3|Keyword4|Keyword5|Keyword6|Year|Citations|AbstractSnippet\n";
    for (int i = 0; i < paperList.count; ++i) {
        Paper& p = paperList.papers[i];
        ofs << p.id << "|";
        // 标题、作者、关键词、年份、引用、摘要
        ofs << p.title << "|";
        ofs << p.authorsString << "|";
        // 写 6 个关键词槽
        for (int k = 0; k < MAX_KEYWORDS_PER_PAPER; ++k) {
            if (k < p.actualKeywordCount) ofs << p.keywords[k];
            ofs << "|";
        }
        ofs << p.year << "|" << p.citations << "|" << p.abstractSnippet << "\n";
    }
    ofs.close();
    cout << "数据已成功保存到 " << filename << endl;
    return true;
}

// ================= BST（按标题的二叉搜索树）实现 =================
// BST 节点：存储标题（键）以及对应的全局论文数组索引
struct BSTNode {
    char title[MAX_TITLE_LENGTH];
    int paper_index; // 在 paperList.papers 中的索引
    int left_child_idx;
    int right_child_idx;
};

static vector<BSTNode> BST_NODES; // 动态节点数组
static int bst_root_index = -1; // -1 表示空树

// 分配一个新的 BST 节点，返回其索引
int getNewBSTNodeIndex() {
    BSTNode n;
    n.title[0] = '\0';
    n.paper_index = -1;
    n.left_child_idx = -1;
    n.right_child_idx = -1;
    BST_NODES.push_back(n);
    return (int)BST_NODES.size() - 1;
}

// 重置 BST（清空）
void resetBST() {
    bst_root_index = -1;
    BST_NODES.clear();
}

// 将论文标题和其索引插入 BST（迭代实现）
bool insertPaperIntoBST(const char* title, int paperIndex) {
    if (!title) return false;
    if (bst_root_index == -1) {
        int idx = getNewBSTNodeIndex();
        if (idx == -1) {
            cerr << "BST 节点已满，无法插入标题: " << title << endl;
            return false;
        }
        strncpy(BST_NODES[idx].title, title, MAX_TITLE_LENGTH - 1);
        BST_NODES[idx].title[MAX_TITLE_LENGTH - 1] = '\0';
        BST_NODES[idx].paper_index = paperIndex;
        bst_root_index = idx;
        return true;
    }

    int cur = bst_root_index;
    int parent = -1;
    while (cur != -1) {
        int cmp = strcmp(title, BST_NODES[cur].title);
        if (cmp == 0) {
            cerr << "警告：标题重复，忽略插入：" << title << endl;
            return false; // 简单策略：忽略重复
        }
        parent = cur;
        if (cmp < 0) cur = BST_NODES[cur].left_child_idx;
        else cur = BST_NODES[cur].right_child_idx;
    }

    int newIdx = getNewBSTNodeIndex();
    if (newIdx == -1) {
        cerr << "BST 节点已满，无法插入标题: " << title << endl;
        return false;
    }
    strncpy(BST_NODES[newIdx].title, title, MAX_TITLE_LENGTH - 1);
    BST_NODES[newIdx].title[MAX_TITLE_LENGTH - 1] = '\0';
    BST_NODES[newIdx].paper_index = paperIndex;
    // 将新节点链接到父节点
    if (strcmp(title, BST_NODES[parent].title) < 0) BST_NODES[parent].left_child_idx = newIdx;
    else BST_NODES[parent].right_child_idx = newIdx;
    return true;
}

// 在 BST 中按标题查找，成功返回 paperList 的索引，失败返回 -1
int searchBST(const char* title) {
    if (bst_root_index == -1) return -1;
    int cur = bst_root_index;
    while (cur != -1) {
        int cmp = strcmp(title, BST_NODES[cur].title);
        if (cmp == 0) return BST_NODES[cur].paper_index;
        if (cmp < 0) cur = BST_NODES[cur].left_child_idx;
        else cur = BST_NODES[cur].right_child_idx;
    }
    return -1;
}

// 根据当前 paperList 重建整个 BST（在加载或大改后使用）
void buildBSTFromPapers() {
    resetBST();
    for (int i = 0; i < paperList.count; ++i) {
        insertPaperIntoBST(paperList.papers[i].title, i);
    }
}

// 交互式按标题查找并显示全文摘要等信息
void searchTitleInteractive() {
    cout << "请输入要查找的论文标题: ";
    string query;
    getline(cin, query);
    if (query.empty()) {
        cout << "输入为空，取消查找。" << endl;
        return;
    }
    int foundIdx = searchBST(query.c_str());
    if (foundIdx == -1) {
        cout << "未找到标题为 '" << query << "' 的论文。" << endl;
        return;
    }
    Paper& p = paperList.papers[foundIdx];
    cout << "\n--- 找到论文详细信息 ---" << endl;
    cout << "ID: " << p.id << endl;
    cout << "标题: " << p.title << endl;
    cout << "作者: " << p.authorsString << endl;
    cout << "关键词: ";
    for (int k = 0; k < p.actualKeywordCount; ++k) {
        if (k) cout << ", ";
        cout << p.keywords[k];
    }
    cout << endl;
    cout << "年份: " << p.year << " | 引用: " << p.citations << endl;
    cout << "摘要片段: " << p.abstractSnippet << endl;
}

// ================= 哈希表（按论文 ID 的链地址法）实现 =================
struct HashNode {
    int paper_id;     // 原始论文 ID
    int paper_index;  // 在 paperList.papers 中的索引
    int next_idx;     // 冲突链下一个节点的索引，-1 表示终端
};

static vector<HashNode> HASH_NODES; // 动态节点池
static vector<int> hash_buckets; // 动态桶表，保存链表头节点索引

int getNewHashNodeIndex() {
    HashNode n;
    n.paper_id = -1;
    n.paper_index = -1;
    n.next_idx = -1;
    HASH_NODES.push_back(n);
    return (int)HASH_NODES.size() - 1;
}

// 简单哈希函数：对正负 ID 做取绝对值后模表长
// 表长动态设置为论文数的两倍加一，以保持较低的装载因子
int hashFunctionForID(int paperID) {
    int key = paperID >= 0 ? paperID : -paperID;
    return key % hash_buckets.size();
}

// 插入（链地址法，头插）
bool insertIDIntoHashTable(int paperID, int paperIndex) {
    if (hash_buckets.empty()) return false;
    int bucket = hashFunctionForID(paperID);
    // 检查是否已存在相同 ID
    int cur = hash_buckets[bucket];
    while (cur != -1) {
        if (HASH_NODES[cur].paper_id == paperID) {
            cerr << "警告：ID " << paperID << " 已存在于哈希表，忽略插入。" << endl;
            return false;
        }
        cur = HASH_NODES[cur].next_idx;
    }

    int newIdx = getNewHashNodeIndex();
    HASH_NODES[newIdx].paper_id = paperID;
    HASH_NODES[newIdx].paper_index = paperIndex;
    // 头插到链表
    HASH_NODES[newIdx].next_idx = hash_buckets[bucket];
    hash_buckets[bucket] = newIdx;
    return true;
}

int searchHashByID(int paperID) {
    if (hash_buckets.empty()) return -1;
    int bucket = hashFunctionForID(paperID);
    int cur = hash_buckets[bucket];
    while (cur != -1) {
        if (HASH_NODES[cur].paper_id == paperID) return HASH_NODES[cur].paper_index;
        cur = HASH_NODES[cur].next_idx;
    }
    return -1;
}

void buildHashFromPapers() {
    // 设置桶数为论文数的两倍加一，以保持较低的装载因子
    int bucketCount = paperList.count * 2 + 1;
    hash_buckets.assign(bucketCount, -1);
    HASH_NODES.clear();
    // 插入所有论文
    for (int i = 0; i < paperList.count; ++i) {
        insertIDIntoHashTable(paperList.papers[i].id, i);
    }
}

void searchByIDInteractive() {
    cout << "请输入要查找的论文 ID: ";
    int id;
    if (!(cin >> id)) {
        cout << "输入格式错误：ID 必须为整数。" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int foundIdx = searchHashByID(id);
    if (foundIdx == -1) {
        cout << "未找到 ID 为 '" << id << "' 的论文。" << endl;
        return;
    }
    Paper& p = paperList.papers[foundIdx];
    cout << "\n--- 找到论文详细信息 ---" << endl;
    cout << "ID: " << p.id << endl;
    cout << "标题: " << p.title << endl;
    cout << "作者: " << p.authorsString << endl;
    cout << "关键词: ";
    for (int k = 0; k < p.actualKeywordCount; ++k) {
        if (k) cout << ", ";
        cout << p.keywords[k];
    }
    cout << endl;
    cout << "年份: " << p.year << " | 引用: " << p.citations << endl;
    cout << "摘要片段: " << p.abstractSnippet << endl;
}

// ================= KMP 字符串匹配实现 =================
// 构建 next 数组（next[i] 表示 pattern[0..i] 的最长相等前后缀的末尾索引）
void buildNextArray(const string& pattern, vector<int>& next) {
    int m = (int)pattern.size();
    next.assign(m, -1);
    if (m == 0) return;
    int j = -1;
    next[0] = -1;
    for (int i = 1; i < m; ++i) {
        while (j != -1 && pattern[j + 1] != pattern[i]) j = next[j];
        if (pattern[j + 1] == pattern[i]) ++j;
        next[i] = j;
    }
}

// 在 text 中查找 pattern 的第一次出现（返回起始索引或 -1）
int kmpSearch(const string& text, const string& pattern, const vector<int>& next) {
    int n = (int)text.size();
    int m = (int)pattern.size();
    if (m == 0) return 0;
    if (n < m) return -1;
    int j = -1;
    for (int i = 0; i < n; ++i) {
        while (j != -1 && pattern[j + 1] != text[i]) j = next[j];
        if (pattern[j + 1] == text[i]) ++j;
        if (j == m - 1) {
            return i - (m - 1);
        }
    }
    return -1;
}

// 交互式 KMP 搜索（在标题和摘要中查找关键词/短语）
void searchKMPInteractive() {
    cout << "请输入要搜索的关键词/短语（在标题或摘要中）： ";
    string query;
    getline(cin, query);
    if (query.empty()) {
        cout << "输入为空，取消搜索。" << endl;
        return;
    }

    vector<int> next;
    buildNextArray(query, next);

    vector<int> matches;
    for (int i = 0; i < paperList.count; ++i) {
        string title(paperList.papers[i].title);
        string abs(paperList.papers[i].abstractSnippet);
        if (kmpSearch(title, query, next) != -1 || kmpSearch(abs, query, next) != -1) {
            matches.push_back(i);
        }
    }

    if (matches.empty()) {
        cout << "未找到包含 '" << query << "' 的论文。" << endl;
        return;
    }

    cout << "\n找到 " << matches.size() << " 篇匹配的论文：" << endl;
    for (int idx : matches) {
        Paper& p = paperList.papers[idx];
        cout << "ID: " << p.id << " | 标题: " << p.title << " | 年份: " << p.year << " | 引用: " << p.citations << endl;
    }
}

// ================ 排序实现 ==================
// 按年份降序
void sortByYearDesc() {
    if (paperList.count <= 1) return;
    std::sort(paperList.papers, paperList.papers + paperList.count, [](const Paper& a, const Paper& b) {
        return a.year > b.year; // 年份降序
        });
}

// 按引用次数降序
void sortByCitationsDesc() {
    if (paperList.count <= 1) return;
    std::sort(paperList.papers, paperList.papers + paperList.count, [](const Paper& a, const Paper& b) {
        return a.citations > b.citations; // 引用次数降序
        });
}

// 按标题字母升序（区分大小写，按 C 字符串比较）
void sortByTitleAsc() {
    if (paperList.count <= 1) return;
    std::sort(paperList.papers, paperList.papers + paperList.count, [](const Paper& a, const Paper& b) {
        return strcmp(a.title, b.title) < 0;
        });
}

// 显示任意 PaperList 的简要信息
void displayPaperListBrief(const PaperList& pl) {
    if (pl.count == 0) {
        cout << "当前列表没有论文数据。" << endl;
        return;
    }
    cout << "\n--- 列表 (共 " << pl.count << " 篇) ---" << endl;
    for (int i = 0; i < pl.count; ++i) {
        const Paper& p = pl.papers[i];
        cout << "ID: " << p.id << " | 标题: " << p.title << " | 年份: " << p.year << " | 引用: " << p.citations << endl;
    }
}

// 为示例创建一个按年份降序排序的新导入论文列表（可以替换为从文件读取）
PaperList createSampleNewPaperListByYearDesc() {
    PaperList res;
    // 手动填充几条样例数据，确保按年份降序排列
    Paper p1{}; p1.id = 9001; strncpy(p1.title, "Sample Paper A", MAX_TITLE_LENGTH - 1); p1.year = 2025; p1.citations = 5; p1.actualKeywordCount = 0; strncpy(p1.abstractSnippet, "Sample abstract A.", MAX_ABSTRACT_LENGTH - 1);
    Paper p2{}; p2.id = 9002; strncpy(p2.title, "Sample Paper B", MAX_TITLE_LENGTH - 1); p2.year = 2023; p2.citations = 2; p2.actualKeywordCount = 0; strncpy(p2.abstractSnippet, "Sample abstract B.", MAX_ABSTRACT_LENGTH - 1);
    Paper p3{}; p3.id = 9003; strncpy(p3.title, "Sample Paper C", MAX_TITLE_LENGTH - 1); p3.year = 2022; p3.citations = 10; p3.actualKeywordCount = 0; strncpy(p3.abstractSnippet, "Sample abstract C.", MAX_ABSTRACT_LENGTH - 1);
    res.papers[res.count++] = p1;
    res.papers[res.count++] = p2;
    res.papers[res.count++] = p3;
    // 已按年份降序（2025,2023,2022）
    return res;
}

// 合并两个按年份降序排序的 PaperList，返回新的按年份降序排序的 PaperList
PaperList mergeSortedPaperListsByYearDesc(const PaperList& a, const PaperList& b) {
    PaperList res;
    int i = 0, j = 0;
    while (i < a.count && j < b.count) {
        if (a.papers[i].year > b.papers[j].year) {
            if (res.count < MAX_PAPERS) res.papers[res.count++] = a.papers[i++]; else break;
        }
        else {
            if (res.count < MAX_PAPERS) res.papers[res.count++] = b.papers[j++]; else break;
        }
    }
    while (i < a.count && res.count < MAX_PAPERS) res.papers[res.count++] = a.papers[i++];
    while (j < b.count && res.count < MAX_PAPERS) res.papers[res.count++] = b.papers[j++];
    if (i < a.count || j < b.count) {
        cerr << "警告：合并结果超过最大容量，剩余论文被丢弃。" << endl;
    }
    return res;
}

// ================= 论文关联图（无向图，邻接表 + 动态边池） =================
struct Edge {
    int to_idx;    // 目标论文在 paperList.papers 中的索引
    int next_idx;  // 邻接链中下一个边的索引，-1 表示链尾或无效
};

class PaperGraph {
private:
    Edge* EDGE_POOL = nullptr; // 边池（在堆上分配）
    int edge_pool_cap = 0;     // 边池容量
    int next_free_edge_idx = 0; // 下一个可用边索引

    int* head = nullptr;       // 每个顶点的邻接表头（堆分配）
    int paper_count = 0;       // 当前图中的论文数量

public:
    PaperGraph() : EDGE_POOL(nullptr), edge_pool_cap(0), next_free_edge_idx(0), head(nullptr), paper_count(0) {}

    ~PaperGraph() {
        if (EDGE_POOL) delete[] EDGE_POOL;
        if (head) delete[] head;
    }

    void reset(int n) {
        // 重新设置顶点数并（按需要）分配/扩展边池
        paper_count = n;
        // 分配头数组（每个顶点的邻接表头）
        if (head) delete[] head;
        head = new int[n];
        for (int i = 0; i < n; ++i) head[i] = -1;

        // 计算需要的边池容量：保守估计为 n*(n-1)（无向图双向边计入）
        long long desired = (long long)n * (long long)(n - 1);
        if (desired < 1) desired = 1;
        if (desired > INT32_MAX) desired = INT32_MAX; // 避免溢出
        int desired_cap = (int)desired;

        if (!EDGE_POOL) {
            EDGE_POOL = new Edge[desired_cap];
            edge_pool_cap = desired_cap;
        }
        else if (desired_cap > edge_pool_cap) {
            // 扩容：分配新池并释放旧池
            delete[] EDGE_POOL;
            EDGE_POOL = new Edge[desired_cap];
            edge_pool_cap = desired_cap;
        }
        next_free_edge_idx = 0;
    }

    // 在 u 的邻接表头插入一条指向 v 的边（头插）
    bool addDirectedEdge(int u, int v) {
        if (u < 0 || u >= paper_count) return false;
        if (next_free_edge_idx >= edge_pool_cap) return false; // 池满
        int eidx = next_free_edge_idx++;
        EDGE_POOL[eidx].to_idx = v;
        EDGE_POOL[eidx].next_idx = head[u];
        head[u] = eidx;
        return true;
    }

    // 添加无向边：在 u->v 和 v->u 各插入一条有向边
    bool addUndirectedEdge(int u, int v) {
        if (u == v || u < 0 || v < 0 || u >= paper_count || v >= paper_count) return false;
        // 需要两个连续的槽位；检查剩余容量
        if (next_free_edge_idx + 1 > edge_pool_cap) return false;
        bool a = addDirectedEdge(u, v);
        bool b = addDirectedEdge(v, u);
        return a && b;
    }

    // 获取顶点 u 的邻接表头索引
    int getHeadIndex(int u) const {
        if (!head) return -1;
        return u >= 0 && u < paper_count ? head[u] : -1;
    }

    // 获取指定边的目标顶点
    int getEdgeTarget(int edge_idx) const {
        if (!EDGE_POOL) return -1;
        return edge_idx >= 0 && edge_idx < next_free_edge_idx ? EDGE_POOL[edge_idx].to_idx : -1;
    }

    // 获取指定边的下一条边索引
    int getNextEdge(int edge_idx) const {
        if (!EDGE_POOL) return -1;
        return edge_idx >= 0 && edge_idx < next_free_edge_idx ? EDGE_POOL[edge_idx].next_idx : -1;
    }

    // 获取当前图中的论文数量
    int size() const { return paper_count; }
};

// 全局图实例
static PaperGraph paperGraph;

// 判断两篇论文是否共享至少一个关键词
bool papersShareKeyword(const Paper& a, const Paper& b) {
    // 遍历关键词少的一方以减少比较次数
    int na = a.actualKeywordCount;
    int nb = b.actualKeywordCount;
    if (na <= 0 || nb <= 0) return false;
    if (na <= nb) {
        for (int i = 0; i < na; ++i) {
            for (int j = 0; j < nb; ++j) {
                if (strcmp(a.keywords[i], b.keywords[j]) == 0) return true;
            }
        }
    }
    else {
        for (int i = 0; i < nb; ++i) {
            for (int j = 0; j < na; ++j) {
                if (strcmp(b.keywords[i], a.keywords[j]) == 0) return true;
            }
        }
    }
    return false;
}

// 构建论文关联图：对每对论文（i<j）检测关键词共享并添加无向边
void buildGraphFromPapers() {
    paperGraph.reset(paperList.count);
    int n = paperList.count;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (papersShareKeyword(paperList.papers[i], paperList.papers[j])) {
                if (!paperGraph.addUndirectedEdge(i, j)) {
                    cerr << "警告：添加边 (" << i << "," << j << ") 失败。" << endl;
                }
            }
        }
    }
}

// ================= 队列实现（用于 BFS） =================
struct IntQueue {
    int data[MAX_PAPERS];
    int head;
    int tail;
    int sz;
    void init() { head = 0; tail = 0; sz = 0; }
    bool isEmpty() const { return sz == 0; }
    bool isFull() const { return sz == MAX_PAPERS; }
    bool enqueue(int v) {
        if (isFull()) return false;
        data[tail] = v;
        tail = (tail + 1) % MAX_PAPERS;
        ++sz;
        return true;
    }
    int dequeue() {
        if (isEmpty()) return -1;
        int v = data[head];
        head = (head + 1) % MAX_PAPERS;
        --sz;
        return v;
    }
};

// 交互式 BFS：从指定起始论文 ID 开始，按图（关键词共享）遍历并显示简要信息
void bfsSearchRelatedInteractive() {
    cout << "请输入起始论文 ID: ";
    int id;
    if (!(cin >> id)) {
        cout << "输入格式错误：ID 必须为整数。" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int startIdx = searchHashByID(id);
    if (startIdx == -1) {
        cout << "未找到起始论文 ID " << id << " 。" << endl;
        return;
    }

    int n = paperList.count;
    vector<char> visited(n, 0);
    IntQueue q; q.init();
    visited[startIdx] = 1;
    q.enqueue(startIdx);

    cout << "\n--- BFS 遍历结果（从 ID=" << id << " 开始）---" << endl;
    while (!q.isEmpty()) {
        int u = q.dequeue();
        if (u < 0 || u >= n) continue;
        Paper& p = paperList.papers[u];
        cout << "ID: " << p.id << " | 标题: " << p.title << " | 年份: " << p.year << " | 引用: " << p.citations << endl;
        // 遍历邻居
        for (int e = paperGraph.getHeadIndex(u); e != -1; e = paperGraph.getNextEdge(e)) {
            int v = paperGraph.getEdgeTarget(e);
            if (v < 0 || v >= n) continue;
            if (!visited[v]) {
                visited[v] = 1;
                q.enqueue(v);
            }
        }
    }
}

// ================= Top-N 推荐（最小堆）实现 =================
struct RecommendItem {
    int paper_idx;
    int score; // 共享关键词数量
};

struct MinHeap {
    RecommendItem data[MAX_PAPERS];
    int cap;
    int sz;
    void init(int capacity) { cap = capacity; sz = 0; }
    bool empty() const { return sz == 0; }
    RecommendItem top() const { return data[0]; }
    void swapItem(int i, int j) { RecommendItem t = data[i]; data[i] = data[j]; data[j] = t; }
    void siftUp(int idx) {
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (data[parent].score <= data[idx].score) break;
            swapItem(parent, idx);
            idx = parent;
        }
    }
    void siftDown(int idx) {
        while (true) {
            int l = idx * 2 + 1;
            int r = l + 1;
            int smallest = idx;
            if (l < sz && data[l].score < data[smallest].score) smallest = l;
            if (r < sz && data[r].score < data[smallest].score) smallest = r;
            if (smallest == idx) break;
            swapItem(smallest, idx);
            idx = smallest;
        }
    }
    bool push(const RecommendItem& it) {
        if (sz >= cap) return false;
        data[sz] = it;
        siftUp(sz);
        ++sz;
        return true;
    }
    // replace top with it (when sz==cap and it.score > top.score)
    void replaceTop(const RecommendItem& it) {
        if (sz == 0) return;
        data[0] = it;
        siftDown(0);
    }
    RecommendItem popTop() {
        RecommendItem ret = data[0];
        data[0] = data[sz - 1];
        --sz;
        siftDown(0);
        return ret;
    }
};

// 计算两个论文之间共享关键词的数量
int countSharedKeywords(const Paper& a, const Paper& b) {
    int na = a.actualKeywordCount;
    int nb = b.actualKeywordCount;
    if (na <= 0 || nb <= 0) return 0;
    int cnt = 0;
    for (int i = 0; i < na; ++i) {
        for (int j = 0; j < nb; ++j) {
            if (strcmp(a.keywords[i], b.keywords[j]) == 0) ++cnt;
        }
    }
    return cnt;
}

void searchTopNInteractive() {
    cout << "请输入起始论文 ID: ";
    int id;
    if (!(cin >> id)) {
        cout << "输入格式错误：ID 必须为整数。" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cout << "请输入推荐数量 N: ";
    int N;
    if (!(cin >> N)) {
        cout << "输入格式错误：N 必须为整数。" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (N <= 0) {
        cout << "N 必须大于 0。" << endl;
        return;
    }

    int startIdx = searchHashByID(id);
    if (startIdx == -1) {
        cout << "未找到起始论文 ID " << id << " 。" << endl;
        return;
    }

    if (N > MAX_PAPERS) N = MAX_PAPERS;
    MinHeap heap; heap.init(N);

    for (int i = 0; i < paperList.count; ++i) {
        if (i == startIdx) continue;
        int sim = countSharedKeywords(paperList.papers[startIdx], paperList.papers[i]);
        if (sim <= 0) continue;
        RecommendItem it{ i, sim };
        if (heap.sz < heap.cap) {
            heap.push(it);
        }
        else {
            if (sim > heap.top().score) {
                heap.replaceTop(it);
            }
        }
    }

    if (heap.empty()) {
        cout << "未找到任何具有共享关键词的论文作为推荐。" << endl;
        return;
    }

    // 将堆中元素取出到数组并按相似度降序排列
    vector<RecommendItem> results;
    while (!heap.empty()) {
        results.push_back(heap.popTop());
    }
    // results currently in ascending order of score (since min-heap), reverse to descending
    sort(results.begin(), results.end(), [](const RecommendItem& a, const RecommendItem& b) {
        return a.score > b.score;
        });

    cout << "\nTop-" << results.size() << " 推荐（按相似度降序）：" << endl;
    for (const auto& r : results) {
        const Paper& p = paperList.papers[r.paper_idx];
        cout << "ID: " << p.id << " | 标题: " << p.title << " | 年份: " << p.year << " | 引用: " << p.citations << " | 相似度: " << r.score << endl;
    }
}