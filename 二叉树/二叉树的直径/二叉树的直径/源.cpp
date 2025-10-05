#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
using namespace std;
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	int maxDiameter = 0;
    int depth(TreeNode* root) {
		if (root==nullptr) return 0;
		int leftDepth = depth(root->left);
		int rightDepth = depth(root->right);
		int depth = max(leftDepth, rightDepth) + 1;
		maxDiameter = max(maxDiameter, leftDepth + rightDepth);

		return depth;
    }
	int diameterOfBinaryTree(TreeNode* root) {
		depth(root);
		return maxDiameter;
	}
};

int main() {
	Solution s;
	TreeNode* root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->right = new TreeNode(3);
	root->left->left = new TreeNode(4);
	root->left->right = new TreeNode(5);
	cout << s.diameterOfBinaryTree(root) << endl;

	return 0;
}
