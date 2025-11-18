#include <iostream>
#include <string>
using namespace std;

// 孩子兄弟表示法的节点结构
struct CSNode {
    int data;          // 节点值（可替换为其他类型）
    CSNode* firstChild; // 指向第一个孩子
    CSNode* nextSibling;// 指向右侧兄弟
    CSNode(int d) : data(d), firstChild(nullptr), nextSibling(nullptr) {}
};

// 树的孩子兄弟表示法类
class CSTree {
private:
    CSNode* root;      // 根节点

    // 辅助函数：递归销毁树
    void destroy(CSNode* node) {
        if (node == nullptr) return;
        // 先销毁所有孩子（左子树）
        destroy(node->firstChild);
        // 再销毁所有兄弟（右子树）
        destroy(node->nextSibling);
        delete node;
    }

    // 辅助函数：递归先序遍历（对应树的先根遍历）
    void preOrder(CSNode* node) const {
        if (node == nullptr) return;
        // 1. 访问当前节点
        cout << node->data << " ";
        // 2. 遍历第一个孩子（左子树）
        preOrder(node->firstChild);
        // 3. 遍历右侧兄弟（右子树）
        preOrder(node->nextSibling);
    }

    // 辅助函数：递归后序遍历（对应树的后根遍历）
    void postOrder(CSNode* node) const {
        if (node == nullptr) return;
        // 1. 遍历第一个孩子（左子树）
        postOrder(node->firstChild);
        // 2. 访问当前节点
        cout << node->data << " ";
        // 3. 遍历右侧兄弟（右子树）
        postOrder(node->nextSibling);
    }

public:
    // 构造函数：初始化空树
    CSTree() : root(nullptr) {}

    // 析构函数：销毁树
    ~CSTree() {
        destroy(root);
        root = nullptr;
    }

    // 1. 设置根节点
    void setRoot(int data) {
        if (root != nullptr) {
            cout << "根节点已存在！" << endl;
            return;
        }
        root = new CSNode(data);
    }

    // 2. 为指定节点添加子节点（添加为第一个孩子的右侧兄弟）
    // 注：parent为目标父节点，childData为新子节点的值
    bool addChild(CSNode* parent, int childData) {
        if (parent == nullptr) {
            cout << "父节点为空！" << endl;
            return false;
        }
        CSNode* newNode = new CSNode(childData);
        // 若父节点无第一个孩子，则新节点成为第一个孩子
        if (parent->firstChild == nullptr) {
            parent->firstChild = newNode;
        }
        else {
            // 否则将新节点添加到孩子链的末尾（右侧兄弟）
            CSNode* curr = parent->firstChild;
            while (curr->nextSibling != nullptr) {
                curr = curr->nextSibling;
            }
            curr->nextSibling = newNode;
        }
        return true;
    }

    // 3. 获取根节点
    CSNode* getRoot() const {
        return root;
    }

    // 4. 查找值为data的节点（递归查找）
    CSNode* findNode(CSNode* node, int data) const {
        if (node == nullptr) return nullptr;
        // 找到目标节点
        if (node->data == data) {
            return node;
        }
        // 先在孩子中查找
        CSNode* found = findNode(node->firstChild, data);
        if (found != nullptr) return found;
        // 再在兄弟中查找
        return findNode(node->nextSibling, data);
    }

    // 5. 树的先根遍历（对应二叉树的前序遍历）
    void preOrderTraverse() const {
        if (root == nullptr) {
            cout << "树为空！" << endl;
            return;
        }
        cout << "先根遍历结果：";
        preOrder(root);
        cout << endl;
    }

    // 6. 树的后根遍历（对应二叉树的后序遍历）
    void postOrderTraverse() const {
        if (root == nullptr) {
            cout << "树为空！" << endl;
            return;
        }
        cout << "后根遍历结果：";
        postOrder(root);
        cout << endl;
    }

    // 7. 层次遍历（广度优先）
    void levelOrderTraverse() const {
        if (root == nullptr) {
            cout << "树为空！" << endl;
            return;
        }
        cout << "层次遍历结果：";
        // 用队列存储当前层节点
        CSNode* queue[100];  // 简化实现，实际可用queue容器
        int front = 0, rear = 0;
        queue[rear++] = root;

        while (front < rear) {
            CSNode* curr = queue[front++];
            cout << curr->data << " ";

            // 将当前节点的所有孩子入队（通过兄弟链遍历）
            CSNode* child = curr->firstChild;
            while (child != nullptr) {
                queue[rear++] = child;
                child = child->nextSibling;  // 遍历兄弟节点
            }
        }
        cout << endl;
    }
};

// 测试函数
int main() {
    CSTree tree;

    // 构建示例树：
    //        1（根）
    //      / | \
    //     2  3  4
    //    /
    //   5
    tree.setRoot(1);
    CSNode* root = tree.getRoot();

    // 为根节点添加子节点2、3、4
    tree.addChild(root, 2);
    tree.addChild(root, 3);
    tree.addChild(root, 4);

    // 查找节点2，为其添加子节点5
    CSNode* node2 = tree.findNode(root, 2);
    tree.addChild(node2, 5);

    // 遍历测试
    tree.preOrderTraverse();   // 先根：1 2 5 3 4（先访问根，再依次访问各子树）
    tree.postOrderTraverse();  // 后根：5 2 3 4 1（先访问子树，最后访问根）
    tree.levelOrderTraverse(); // 层次：1 2 3 4 5（按层次从左到右）

    return 0;
}