#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(NULL), right(NULL) {}
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

bool dfs(TreeNode* left, TreeNode* right) {
	// 终止条件：都为空则对称；一个为空一个不为空则不对称
	if (left == nullptr && right == nullptr) return true;
	if (left == nullptr || right == nullptr) return false;
	// 当前节点值相等，且左子树的左与右子树的右对称，左子树的右与右子树的左对称
	return (left->val == right->val)&& dfs(left->left, right->right)
		&& dfs(left->right, right->left);
}

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
		if (root == NULL) return true;
		return dfs(root->left, root->right);	
    }
};

int main()
{
	TreeNode* n1 = new TreeNode(1);	
	TreeNode* n2 = new TreeNode(2);
	TreeNode* n3 = new TreeNode(2);
	TreeNode* n4 = new TreeNode(3);
	TreeNode* n5 = new TreeNode(4);
	TreeNode* n6 = new TreeNode(4);
	TreeNode* n7 = new TreeNode(3);
	n1->left = n2;
	n1->right = n3;
	n2->left = n4;
	n2->right = n5;
	n3->left = n6;
	n3->right = n7;
	Solution s;
	cout << s.isSymmetric(n1) << endl;

	return 0;
}