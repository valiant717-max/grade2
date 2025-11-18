#include <iostream>
using namespace std;

// 线索链表节点结构
struct ThreadNode {
    int data;               // 节点值
    ThreadNode* left;       // 左孩子或前驱线索
    ThreadNode* right;      // 右孩子或后继线索
    int ltag, rtag;         // 标志位：0=指向孩子，1=指向线索
    ThreadNode(int x) : data(x), left(nullptr), right(nullptr), ltag(0), rtag(0) {}
};

// 全局变量：记录中序遍历的前驱节点（用于线索化）
ThreadNode* pre = nullptr;

// 1. 中序线索化二叉树（递归实现）
void inThread(ThreadNode* root) {
    if (root == nullptr) return;

    inThread(root->left);   // 线索化左子树

    // 处理当前节点的前驱线索（左空则指向pre）
    if (root->left == nullptr) {
        root->left = pre;   // 左指针改为前驱线索
        root->ltag = 1;     // 标记为线索
    }

    // 处理前驱节点的后继线索（pre的右空则指向当前节点）
    if (pre != nullptr && pre->right == nullptr) {
        pre->right = root;  // pre的右指针改为后继线索（指向当前节点）
        pre->rtag = 1;      // 标记为线索
    }

    pre = root;             // 更新前驱为当前节点
    inThread(root->right);  // 线索化右子树
}

// 2. 创建线索链表（封装线索化过程）
ThreadNode* createThreadTree(ThreadNode* root) {
    if (root == nullptr) return nullptr;
    pre = nullptr;          // 初始化前驱
    inThread(root);         // 中序线索化
    pre->right = nullptr;   // 处理最后一个节点的后继线索（指向空）
    pre->rtag = 1;
    return root;
}

// 3. 中序遍历线索链表（无需递归/栈，直接通过线索跳转）
void inOrderTraverse(ThreadNode* root) {
    if (root == nullptr) return;

    ThreadNode* p = root;
    // 找到中序遍历的第一个节点（最左节点）
    while (p->ltag == 0) {
        p = p->left;
    }

    while (p != nullptr) {
        cout << p->data << " ";  // 访问当前节点

        // 若右指针是线索，直接跳转到后继节点
        if (p->rtag == 1) {
            p = p->right;
        }
        else {
            // 否则进入右子树，再找右子树的最左节点（下一个访问节点）
            p = p->right;
            while (p != nullptr && p->ltag == 0) {
                p = p->left;
            }
        }
    }
}

// 辅助函数：构建普通二叉树（用于测试）
ThreadNode* buildBinaryTree() {
    // 手动构建示例树：
    //       1
    //      / \
    //     2   3
    //    /   /
    //   4   5
    ThreadNode* node1 = new ThreadNode(1);
    ThreadNode* node2 = new ThreadNode(2);
    ThreadNode* node3 = new ThreadNode(3);
    ThreadNode* node4 = new ThreadNode(4);
    ThreadNode* node5 = new ThreadNode(5);

    node1->left = node2;
    node1->right = node3;
    node2->left = node4;
    node3->left = node5;

    return node1;
}

// 主函数测试
int main() {
    // 构建普通二叉树
    ThreadNode* root = buildBinaryTree();
    // 线索化
    createThreadTree(root);
    // 中序遍历线索链表（预期结果：4 2 1 5 3）
    cout << "中序线索链表遍历结果：";
    inOrderTraverse(root);
    cout << endl;

    return 0;
}