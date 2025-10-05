#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// 二叉树节点定义
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 1. 递归实现深度优先遍历（前序）
void dfsRecursive(TreeNode* root, vector<int>& result) {
    if (root == nullptr) return;  // 递归终止条件：空节点
    result.push_back(root->val);  // 访问根节点
    dfsRecursive(root->left, result);  // 递归遍历左子树
    dfsRecursive(root->right, result); // 递归遍历右子树
}

// 2. 栈实现深度优先遍历（前序）
vector<int> dfsStack(TreeNode* root) {
    vector<int> result;
    if (root == nullptr) return result;

    stack<TreeNode*> st;  // 用栈存储待访问的节点
    st.push(root);        // 根节点先入栈

    while (!st.empty()) {
        TreeNode* node = st.top();  // 取出栈顶节点（当前节点）
        st.pop();
        result.push_back(node->val);  // 访问当前节点

        // 注意：栈是后进先出，所以先压右子树，再压左子树
        // 保证左子树先被访问（符合前序遍历顺序）
        if (node->right != nullptr) {
            st.push(node->right);
        }
        if (node->left != nullptr) {
            st.push(node->left);
        }
    }
    return result;
}

// 辅助函数：打印遍历结果
void printResult(const vector<int>& result, const string& method) {
    cout << method << " 遍历结果：";
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;
}

// 构建示例二叉树
TreeNode* buildExampleTree() {
    /*
    构建的二叉树结构：
        1
       / \
      2   3
     / \
    4   5
    预期前序遍历结果：1 2 4 5 3
    */
    TreeNode* node4 = new TreeNode(4);//返回指向新节点的指针
    TreeNode* node5 = new TreeNode(5);
    TreeNode* node2 = new TreeNode(2);
    node2->left = node4;
    node2->right = node5;

    TreeNode* node3 = new TreeNode(3);
    TreeNode* root = new TreeNode(1);
    root->left = node2;
    root->right = node3;

    return root;
}

// 释放二叉树内存
void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    TreeNode* root = buildExampleTree();

    // 递归方式遍历
    vector<int> recursiveResult;
    dfsRecursive(root, recursiveResult);
    printResult(recursiveResult, "递归");

    // 栈方式遍历
    vector<int> stackResult = dfsStack(root);
    printResult(stackResult, "栈");

    // 释放内存
    deleteTree(root);
    return 0;
}
