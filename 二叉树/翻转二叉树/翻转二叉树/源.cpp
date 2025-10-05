#include <iostream>
#include <vector>
using namespace std;

// 二叉树节点定义
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    // 翻转二叉树
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        // 递归翻转左右子树
        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);
        // 交换当前节点的左右子树
        root->left = right;
        root->right = left;
        return root;
    }

    // 前序遍历（根->左->右）并输出结果
    void preorderTraversal(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        cout << root->val << " ";       // 访问根节点
        preorderTraversal(root->left);  // 遍历左子树
        preorderTraversal(root->right); // 遍历右子树
    }
};

int main() {
    // 构建示例二叉树
    TreeNode* n1 = new TreeNode(4);
    TreeNode* n2 = new TreeNode(2);
    TreeNode* n3 = new TreeNode(7);
    TreeNode* n4 = new TreeNode(1);
    TreeNode* n5 = new TreeNode(3);
    TreeNode* n6 = new TreeNode(6);
    TreeNode* n7 = new TreeNode(9);

    // 构建树结构
    n1->left = n2;
    n1->right = n3;
    n2->left = n4;
    n2->right = n5;
    n3->left = n6;
    n3->right = n7;

    Solution s;

    // 输出翻转前的前序遍历结果
    cout << "翻转前的前序遍历结果: ";
    s.preorderTraversal(n1);
    cout << endl;

    // 翻转二叉树
    s.invertTree(n1);

    // 输出翻转后的前序遍历结果
    cout << "翻转后的前序遍历结果: ";
    s.preorderTraversal(n1);
    cout << endl;

    // 释放内存
    delete n1; delete n2; delete n3;
    delete n4; delete n5; delete n6; delete n7;

    return 0;
}
