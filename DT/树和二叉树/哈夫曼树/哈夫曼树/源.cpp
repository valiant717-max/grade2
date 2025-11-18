#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

// 哈夫曼树节点结构
struct HuffmanNode {
    char data;          // 字符（叶子节点有效，非叶子节点为'\0'）
    int weight;         // 权值（字符出现频率）
    HuffmanNode* left;  // 左子树
    HuffmanNode* right; // 右子树

    // 构造函数
    HuffmanNode(char d, int w) : data(d), weight(w), left(nullptr), right(nullptr) {}
};

// 优先队列比较器（小根堆，权值小的节点优先）
struct CompareNode {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->weight > b->weight; // 注意：优先队列默认大根堆，此处反转实现小根堆
    }
};

// 哈夫曼树与编码类
class HuffmanCode {
private:
    HuffmanNode* root;                          // 哈夫曼树根节点
    unordered_map<char, string> codeMap;        // 字符→编码映射表

    // 递归销毁哈夫曼树
    void destroyTree(HuffmanNode* node) {
        if (node == nullptr) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

    // 递归生成哈夫曼编码（左0右1）
    void generateCodes(HuffmanNode* node, string currentCode) {
        if (node == nullptr) return;
        // 叶子节点：记录编码
        if (node->left == nullptr && node->right == nullptr) {
            codeMap[node->data] = currentCode;
            return;
        }
        // 非叶子节点：左分支加0，右分支加1
        generateCodes(node->left, currentCode + "0");
        generateCodes(node->right, currentCode + "1");
    }

public:
    // 构造函数
    HuffmanCode() : root(nullptr) {}

    // 析构函数
    ~HuffmanCode() {
        destroyTree(root);
    }

    // 1. 构建哈夫曼树（输入：字符-频率映射）
    void buildTree(const unordered_map<char, int>& freqMap) {
        // 初始化优先队列（小根堆），存储所有叶子节点
        priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNode> minHeap;
        for (const auto& pair : freqMap) {
            minHeap.push(new HuffmanNode(pair.first, pair.second));
        }

        // 合并节点直至只剩一棵树
        while (minHeap.size() > 1) {
            // 取出权值最小的两个节点
            HuffmanNode* left = minHeap.top();
            minHeap.pop();
            HuffmanNode* right = minHeap.top();
            minHeap.pop();

            // 构建新节点（权值为两者之和，数据域为空）
            HuffmanNode* parent = new HuffmanNode('\0', left->weight + right->weight);
            parent->left = left;
            parent->right = right;

            // 将新节点加入堆
            minHeap.push(parent);
        }

        // 堆中最后一个节点即为根节点
        if (!minHeap.empty()) {
            root = minHeap.top();
        }
    }

    // 2. 生成哈夫曼编码表
    void buildCodeMap() {
        if (root == nullptr) {
            cout << "哈夫曼树未构建！" << endl;
            return;
        }
        codeMap.clear();
        generateCodes(root, ""); // 从根节点开始，初始编码为空
    }

    // 3. 获取编码表
    const unordered_map<char, string>& getCodeMap() const {
        return codeMap;
    }

    // 4. 对字符串进行编码
    string encode(const string& text) {
        string encoded;
        for (char c : text) {
            if (codeMap.find(c) == codeMap.end()) {
                throw runtime_error("字符 " + string(1, c) + " 不在编码表中！");
            }
            encoded += codeMap[c];
        }
        return encoded;
    }

    // 5. 对编码进行解码
    string decode(const string& encodedText) {
        if (root == nullptr) {
            throw runtime_error("哈夫曼树未构建！");
        }

        string decoded;
        HuffmanNode* curr = root;

        for (char bit : encodedText) {
            // 根据0/1移动到左/右子树
            if (bit == '0') {
                curr = curr->left;
            }
            else if (bit == '1') {
                curr = curr->right;
            }
            else {
                throw runtime_error("无效的编码位：" + string(1, bit));
            }

            // 到达叶子节点，解码一个字符
            if (curr->left == nullptr && curr->right == nullptr) {
                decoded += curr->data;
                curr = root; // 重置指针，准备解码下一个字符
            }
        }

        return decoded;
    }
};

// 测试函数
int main() {
    // 示例：统计字符串中字符的频率
    string text = "abracadabra";
    unordered_map<char, int> freqMap;
    for (char c : text) {
        freqMap[c]++;
    }

    // 构建哈夫曼树和编码
    HuffmanCode huffman;
    huffman.buildTree(freqMap);
    huffman.buildCodeMap();

    // 输出编码表
    cout << "哈夫曼编码表：" << endl;
    const auto& codeMap = huffman.getCodeMap();
    for (const auto& pair : codeMap) {
        cout << pair.first << " : " << pair.second << endl;
    }

    // 编码
    string encoded = huffman.encode(text);
    cout << "\n原字符串：" << text << endl;
    cout << "编码结果：" << encoded << endl;

    // 解码
    string decoded = huffman.decode(encoded);
    cout << "解码结果：" << decoded << endl;

    return 0;
}