#include <iostream>
#include <queue>
using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class BinaryTree {
private:
	TreeNode* root;
	TreeNode* createTree() {
		int val;
		cin >> val;
		if (val == -1) return NULL;
		TreeNode* node = new TreeNode(val);
		node->left = createTree();
		node->right = createTree();
		return node;
	}

    // 递归前序遍历（根->左->右）
    void preOrder(TreeNode* node) {
		if (node == nullptr) return;
		cout << node->val << " ";
		preOrder(node->left);
		preOrder(node->right);
    }

    // 递归中序遍历（左->根->右）
    void inOrder(TreeNode* node) {
		if (node == nullptr) return;
		inOrder(node->left);
		cout << node->val << " ";
		inOrder(node->right);
    }

    // 递归后序遍历（左->右->根）
    void postOrder(TreeNode* node) {
		if (node == nullptr) return;
		postOrder(node->left);
		postOrder(node->right);
		cout << node->val << " ";
    }

    // 递归查找值为x的节点
    TreeNode* findNode(TreeNode* node, int x) {
		if (node == nullptr) return nullptr;
		if (node->val == x) return node;
		// 先在左子树查找
		TreeNode* leftResult = findNode(node->left, x);
		if (leftResult != nullptr) return leftResult;
		// 左子树没找到，再在右子树查找
		return findNode(node->right, x);
    }

    // 递归计算二叉树高度（空树高度为0，非空树高度=max(左子树高度, 右子树高度)+1）
    int getHeight(TreeNode* node) {
		if (node == nullptr) return 0;
		int leftHeight = getHeight(node->left);
		int rightHeight = getHeight(node->right);
		return max(leftHeight, rightHeight) + 1;
    }

    // 递归统计节点总数
    int getNodeCount(TreeNode* node) {
        if (node == nullptr) return 0;
        // 总节点数=左子树节点数+右子树节点数+1（当前节点）
        return getNodeCount(node->left) + getNodeCount(node->right) + 1;
    }

    // 递归统计叶子节点数（叶子节点：左右子树都为空）
    int getLeafCount(TreeNode* node) {
        if (node == nullptr) return 0;
        // 左右子树都为空，说明是叶子节点
        if (node->left == nullptr && node->right == nullptr) {
            return 1;
        }
        // 否则递归统计左右子树的叶子节点
        return getLeafCount(node->left) + getLeafCount(node->right);
    }

    // 递归销毁二叉树（后序遍历方式，避免内存泄漏）
    void destroyTree(TreeNode* node) {
		if (node == nullptr) return;
		destroyTree(node->left);
		destroyTree(node->right);
		delete node;
    }

public:
    // 构造函数：初始化根节点为空
    BinaryTree() : root(nullptr) {}

    // 外部接口：创建二叉树（调用辅助函数）
	void create() {
		root = createTree();
    }

    // 外部接口：前序遍历
    void preOrderTraversal() {
		preOrder(root);
		cout << endl;
    }

    // 外部接口：中序遍历
    void inOrderTraversal() {
		inOrder(root);
		cout << endl;
    }

    // 外部接口：后序遍历
    void postOrderTraversal() {
		postOrder(root);
		cout << endl;
          
    }

    // 外部接口：层序遍历（非递归，使用队列实现）
    void levelOrderTraversal() {
		if (root == nullptr) return;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()) {
			TreeNode* node = q.front();
			q.pop();
			cout << node->val << " ";
			if (node->left != nullptr) q.push(node->left);
			if (node->right != nullptr) q.push(node->right);
		}
        cout << endl;
    }

    // 外部接口：查找值为x的节点
    TreeNode* find(int x) {
        return findNode(root, x);
    }

    // 外部接口：获取二叉树高度
    int height() {
        return getHeight(root);
    }

    // 外部接口：获取节点总数
    int nodeCount() {
        return getNodeCount(root);
    }

    // 外部接口：获取叶子节点数
    int leafCount() {
        return getLeafCount(root);
    }

    // 析构函数：销毁二叉树，释放内存
    ~BinaryTree() {
        destroyTree(root);
        root = nullptr;  // 避免野指针
    }
};

int main() {
    BinaryTree tree;

    // 创建二叉树（示例输入：1 2 4 -1 -1 5 -1 -1 3 -1 6 -1 -1，对应如下结构）
    //       1
    //      / \
    //     2   3
    //    / \   \
    //   4   5   6
    tree.create();

    // 遍历测试
    tree.preOrderTraversal();    // 1 2 4 5 3 6
    tree.inOrderTraversal();     // 4 2 5 1 3 6
    tree.postOrderTraversal();   // 4 5 2 6 3 1
    tree.levelOrderTraversal();  // 1 2 3 4 5 6

    // 查找节点测试
    int x = 5;
    TreeNode* found = tree.find(x);
    if (found != nullptr) {
        cout << "找到值为 " << x << " 的节点" << endl;
    }
    else {
        cout << "未找到值为 " << x << " 的节点" << endl;
    }

    // 统计测试
    cout << "二叉树高度：" << tree.height() << endl;         // 3
    cout << "总节点数：" << tree.nodeCount() << endl;        // 6
    cout << "叶子节点数：" << tree.leafCount() << endl;      // 3（4、5、6）

    return 0;
}