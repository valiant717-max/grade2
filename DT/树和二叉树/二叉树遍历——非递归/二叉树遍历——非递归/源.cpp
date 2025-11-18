#include <iostream>
#include <stack>
#include <queue>
#include <utility>
using namespace std;

// 二叉树节点结构
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 二叉树类
class BinaryTree {
private:
    TreeNode* root;

    // 递归创建二叉树（先序输入，-1表示空节点）
    TreeNode* createTree() {
        int val;
        cin >> val;
        if (val == -1) return nullptr;
        TreeNode* node = new TreeNode(val);
        node->left = createTree();
        node->right = createTree();
        return node;
    }

    // 销毁二叉树
    void destroyTree(TreeNode* node) {
        if (node == nullptr) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    BinaryTree() : root(nullptr) {}

    // 创建二叉树
    void create() {
        root = createTree();
    }

    // 非递归前序遍历（根->左->右）
    void preOrderNonRecursive() {
        if (root == nullptr) return;
        stack<TreeNode*> st;
        TreeNode* cur = root;

        while (cur != nullptr || !st.empty()) {
            // 左路节点全部入栈，并访问根节点
            while (cur != nullptr) {
                cout << cur->val << " ";  // 先访问根节点
                st.push(cur);
                cur = cur->left;          // 移向左子树
            }
            // 左子树访问完，处理右子树
            cur = st.top();
            st.pop();
            cur = cur->right;  // 转向右子树
        }
        cout << endl;
    }

    // 非递归中序遍历（左->根->右）
    void inOrderNonRecursive() {
        if (root == nullptr) return;
        stack<TreeNode*> st;
        TreeNode* cur = root;
        while (cur != nullptr || !st.empty()) {
            // 左路节点全部入栈
            while (cur != nullptr) {
                st.push(cur);
                cur = cur->left;  // 移向左子树
            }
            // 弹出栈顶节点（左子树为空，访问根节点）
            cur = st.top();
            st.pop();
            cout << cur->val << " ";  // 访问根节点
            cur = cur->right;          // 转向右子树
        }
        cout << endl;
    }

    // 非递归后序遍历（左->右->根）
    // 方法：使用栈+标记位（记录节点是否被访问过）
    void postOrderNonRecursive() {
        if (root == nullptr) return;
        stack<pair<TreeNode*, bool>> st;  // 第二个元素标记是否已访问
        st.push({ root, false });
        while (!st.empty()) {
            pair<TreeNode*, bool>cur= st.top();//取栈顶
            TreeNode* node = cur.first;
            st.pop();
            if (cur.second) {
                // 已访问过，直接输出
                cout << node->val << " ";
            }
            else {
                // 未访问过，按 根->右->左 入栈（出栈时即为左->右->根）
                st.push({ node, true });  // 标记为已访问，下次弹出时输出
                if (node->right != nullptr) {
                    st.push({ node->right, false });
                }
                if (node->left != nullptr) {
                    st.push({ node->left, false });
                }
            }
        }
        cout << endl;
    }

    // 非递归层序遍历（按层次从左到右）
    void levelOrderNonRecursive() {
        if (root == nullptr) return;
        queue<TreeNode*> q;
        q.push(root);  // 根节点入队

        while (!q.empty()) {
            int size = q.size();  // 当前层的节点数
            // 遍历当前层所有节点
            for (int i = 0; i < size; ++i) {
                TreeNode* cur = q.front();
                q.pop();
                cout << cur->val << " ";  // 访问当前节点

                // 左右子节点入队（下一层）
                if (cur->left != nullptr) {
                    q.push(cur->left);
                }
                if (cur->right != nullptr) {
                    q.push(cur->right);
                }
            }
        }
        cout << endl;
    }

    ~BinaryTree() {
        destroyTree(root);
        root = nullptr;
    }
};

// 测试代码
int main() {
    BinaryTree tree;
    // 输入示例（先序遍历序列，-1表示空节点）：
    // 1 2 4 -1 -1 5 -1 -1 3 -1 6 -1 -1
    // 对应的树结构：
    //       1
    //      / \
    //     2   3
    //    / \   \
    //   4   5   6
    cout << "请输入二叉树节点值（-1表示空节点，先序遍历顺序）：" << endl;
    tree.create();

    cout << "非递归前序遍历：";
    tree.preOrderNonRecursive();  // 输出：1 2 4 5 3 6

    cout << "非递归中序遍历：";
    tree.inOrderNonRecursive();   // 输出：4 2 5 1 3 6

    cout << "非递归后序遍历：";
    tree.postOrderNonRecursive(); // 输出：4 5 2 6 3 1

    cout << "非递归层序遍历：";
    tree.levelOrderNonRecursive();// 输出：1 2 3 4 5 6

    return 0;
}