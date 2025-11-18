#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// 二叉树节点结构
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    // 存储中序遍历中「值→索引」的映射，加速根节点查找
    unordered_map<int, int> inorderMap;

public:
    // 重构入口函数：preorder为前序遍历，inorder为中序遍历
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.empty() || inorder.empty()) return nullptr;

        // 初始化中序映射（值唯一时有效，若有重复值需额外处理）
        for (int i = 0; i < inorder.size(); ++i) {
            inorderMap[inorder[i]] = i;
        }

        // 递归重构：参数为前序起始索引、前序结束索引、中序起始索引、中序结束索引
        return build(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }

private:
    // 递归构建函数
    TreeNode* build(vector<int>& preorder, int preStart, int preEnd,
        vector<int>& inorder, int inStart, int inEnd) {
        // 递归终止条件：起始索引 > 结束索引
        if (preStart > preEnd || inStart > inEnd) return nullptr;

        // 1. 前序遍历的第一个元素是当前子树的根节点
        int rootVal = preorder[preStart];
        TreeNode* root = new TreeNode(rootVal);

        // 2. 在中序遍历中找到根节点的位置
        int rootIdxInInorder = inorderMap[rootVal];

        // 3. 计算左子树的节点数量（中序中根左侧的元素个数）
        int leftSize = rootIdxInInorder - inStart;

        // 4. 递归构建左子树
        // 前序左子树范围：[preStart+1, preStart+leftSize]
        // 中序左子树范围：[inStart, rootIdxInInorder-1]
        root->left = build(preorder, preStart + 1, preStart + leftSize,
            inorder, inStart, rootIdxInInorder - 1);

        // 5. 递归构建右子树
        // 前序右子树范围：[preStart+leftSize+1, preEnd]
        // 中序右子树范围：[rootIdxInInorder+1, inEnd]
        root->right = build(preorder, preStart + leftSize + 1, preEnd,
            inorder, rootIdxInInorder + 1, inEnd);

        return root;
    }
};

// 工具函数：后序遍历打印树（验证重构结果）
void postorderPrint(TreeNode* root) {
    if (!root) return;
    postorderPrint(root->left);
    postorderPrint(root->right);
    cout << root->val << " ";
}

int main() {
    // 测试用例：前序和中序遍历序列
    vector<int> preorder = { 3, 9, 20, 15, 7 };  // 前序：根(3) → 左(9) → 右(20,15,7)
    vector<int> inorder = { 9, 3, 15, 20, 7 };   // 中序：左(9) → 根(3) → 右(15,20,7)

    Solution sol;
    TreeNode* root = sol.buildTree(preorder, inorder);

    // 打印后序遍历验证（预期结果：9 15 7 20 3）
    cout << "重构后二叉树的后序遍历：";
    postorderPrint(root);
    cout << endl;

    return 0;
}