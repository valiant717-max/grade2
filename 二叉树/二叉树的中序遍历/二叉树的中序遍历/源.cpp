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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        if (root == nullptr) return res;
        // 递归遍历左子树
        vector<int> left = inorderTraversal(root->left);//root->left：通过根节点的左指针，访问左子树的根节点,也是一个 TreeNode* 指针
        // 将左子树遍历结果插入到结果集
        res.insert(res.end(), left.begin(), left.end());
        // 插入当前节点值
        res.push_back(root->val);
        // 递归遍历右子树
        vector<int> right = inorderTraversal(root->right);
        // 将右子树遍历结果插入到结果集
        res.insert(res.end(), right.begin(), right.end());

        return res;
    }
};

// 构建示例二叉树
TreeNode* buildExampleTree() {
    // 构建如下二叉树:
    //       1
    //        \
    //         2
    //        /
    //       3
    TreeNode* node3 = new TreeNode(3);
    TreeNode* node2 = new TreeNode(2, node3, nullptr);
    TreeNode* node1 = new TreeNode(1, nullptr, node2);
    return node1;
}

// 构建另一个更复杂的二叉树用于测试
TreeNode* buildAnotherTree() {
    // 构建如下二叉树:
    //       4
    //      / \
    //     2   5
    //    / \
    //   1   3
    TreeNode* node1 = new TreeNode(1);
    TreeNode* node3 = new TreeNode(3);
    TreeNode* node2 = new TreeNode(2, node1, node3);
    TreeNode* node5 = new TreeNode(5);
    TreeNode* node4 = new TreeNode(4, node2, node5);
    return node4;
}

// 打印遍历结果
void printResult(const vector<int>& result) {
    cout << "中序遍历结果: ";
    for (size_t i = 0; i < result.size(); ++i) {
        if (i > 0) cout << " -> ";
        cout << result[i];
    }
    cout << endl;
}

// 释放二叉树内存
void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    // 创建解决方案实例
    Solution solution;

    // 测试第一个示例树
    TreeNode* root1 = buildExampleTree();
    vector<int> result1 = solution.inorderTraversal(root1);
    printResult(result1);  // 预期输出: 1 -> 3 -> 2

    // 测试第二个示例树
    TreeNode* root2 = buildAnotherTree();
    vector<int> result2 = solution.inorderTraversal(root2);
    printResult(result2);  // 预期输出: 1 -> 2 -> 3 -> 4 -> 5

    // 测试空树
    TreeNode* nullTree = nullptr;
    vector<int> result3 = solution.inorderTraversal(nullTree);
    printResult(result3);  // 预期输出: 空

    // 释放内存
    deleteTree(root1);
    deleteTree(root2);

    return 0;
}
