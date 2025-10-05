#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(NULL), right(NULL) {}
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}	
};

class Solution {
public:
	int maxDepth(TreeNode* root) {
		if (root == nullptr) return 0;
		return max(maxDepth(root->left), maxDepth(root->right)) + 1;
	}
};

// 构建测试用例1：深度为3的二叉树
TreeNode* buildTestTree1() {
    /*
        构建的二叉树结构：
              3
             / \
            9  20
              /  \
             15   7
        最大深度应为3
    */
    TreeNode* node15 = new TreeNode(15);
    TreeNode* node7 = new TreeNode(7);
    TreeNode* node20 = new TreeNode(20, node15, node7);
    TreeNode* node9 = new TreeNode(9);
    TreeNode* root = new TreeNode(3, node9, node20);
    return root;
}

// 构建测试用例2：深度为1的二叉树（只有根节点）
TreeNode* buildTestTree2() {
    /*
        构建的二叉树结构：
              1
        最大深度应为1
    */
    return new TreeNode(1);
}

// 构建测试用例3：空树
TreeNode* buildTestTree3() {
    /*
        构建的二叉树结构：空树
        最大深度应为0
    */
    return nullptr;
}

// 构建测试用例4：深度为4的二叉树
TreeNode* buildTestTree4() {
    /*
        构建的二叉树结构：
              1
               \
                2
                 \
                  3
                   \
                    4
        最大深度应为4
    */
    TreeNode* node4 = new TreeNode(4);
    TreeNode* node3 = new TreeNode(3, nullptr, node4);
    TreeNode* node2 = new TreeNode(2, nullptr, node3);
    TreeNode* root = new TreeNode(1, nullptr, node2);
    return root;
}

// 释放二叉树内存，避免内存泄漏
void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Solution solution;

    // 测试用例1
    TreeNode* root1 = buildTestTree1();
    cout << "测试用例1 最大深度: " << solution.maxDepth(root1) << endl;  // 预期输出: 3

    // 测试用例2
    TreeNode* root2 = buildTestTree2();
    cout << "测试用例2 最大深度: " << solution.maxDepth(root2) << endl;  // 预期输出: 1

    // 测试用例3
    TreeNode* root3 = buildTestTree3();
    cout << "测试用例3 最大深度: " << solution.maxDepth(root3) << endl;  // 预期输出: 0

    // 测试用例4
    TreeNode* root4 = buildTestTree4();
    cout << "测试用例4 最大深度: " << solution.maxDepth(root4) << endl;  // 预期输出: 4

    // 释放内存
    deleteTree(root1);
    deleteTree(root2);
    deleteTree(root4);  // root3是空指针，无需释放

    return 0;
}