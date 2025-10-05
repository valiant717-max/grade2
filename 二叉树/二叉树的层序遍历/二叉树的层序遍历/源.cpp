#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (root == nullptr) return result;

        queue<TreeNode*> q;
        q.push(root);  // 根节点入队（第1层）

        while (!q.empty()) {
            int size = q.size();  // 当前层的节点数
            vector<int> level;

            // 遍历当前层的所有节点
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                level.push_back(node->val);  // 访问当前节点

                // 左、右子节点入队
                if (node->left != nullptr) q.push(node->left);
                if (node->right != nullptr) q.push(node->right);
            }
            result.push_back(level);  // 保存当前层结果
        }
        return result;
    }
};

int main()
{
	Solution s;
	TreeNode* root = new TreeNode(3);
	root->left = new TreeNode(9);
	root->right = new TreeNode(20);
	root->right->left = new TreeNode(15);
	root->right->right = new TreeNode(7);

	s.levelOrder(root);

	return 0;
}
