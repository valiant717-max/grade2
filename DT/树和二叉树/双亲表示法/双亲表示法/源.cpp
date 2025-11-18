#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 双亲表示法的节点结构
struct ParentNode {
    int data;       // 节点值（这里用int举例，可替换为其他类型）
    int parent;     // 父节点的索引（根节点为-1）
    ParentNode(int d = 0, int p = -1) : data(d), parent(p) {}
};

// 树的双亲表示法类
class ParentTree {
private:
    vector<ParentNode> nodes;  // 存储所有节点的数组
    int root;                  // 根节点的索引（默认为-1，表示空树）

public:
    // 构造函数：初始化空树
    ParentTree() : root(-1) {}

    // 1. 添加根节点（树为空时才能添加）
    bool addRoot(int data) {
        if (root != -1) {
            cout << "树已存在根节点，无法重复添加！" << endl;
            return false;
        }
        nodes.emplace_back(data, -1);
        root = 0;  // 根节点在数组中的索引为0
        return true;
    }

    // 2. 为指定父节点添加子节点（父节点索引需有效）
    bool addChild(int parentIdx, int data) {
        // 检查父节点索引是否有效
        if (parentIdx < 0 || parentIdx >= nodes.size()) {
            cout << "父节点索引无效！" << endl;
            return false;
        }
        // 新节点的父索引为parentIdx，添加到数组末尾
        nodes.emplace_back(data, parentIdx);
        return true;
    }

    // 3. 查找指定值的节点索引（返回第一个匹配的节点）
    int findNode(int data) const {
        for (int i = 0; i < nodes.size(); ++i) {
            if (nodes[i].data == data) {
                return i;
            }
        }
        return -1;  // 未找到
    }

    // 4. 获取指定节点的所有子节点索引
    vector<int> getChildren(int nodeIdx) const {
        vector<int> children;
        if (nodeIdx < 0 || nodeIdx >= nodes.size()) {
            return children;  // 无效索引返回空
        }
        // 遍历数组，找出父索引为nodeIdx的节点
        for (int i = 0; i < nodes.size(); ++i) {
            if (nodes[i].parent == nodeIdx) {
                children.push_back(i);
            }
        }
        return children;
    }

    // 5. 从指定节点追溯到根节点（打印路径）
    void traceToRoot(int nodeIdx) const {
        if (nodeIdx < 0 || nodeIdx >= nodes.size()) {
            cout << "节点索引无效！" << endl;
            return;
        }
        cout << "从节点 " << nodes[nodeIdx].data << " 到根的路径：";
        int curr = nodeIdx;
        while (curr != -1) {
            cout << nodes[curr].data;
            curr = nodes[curr].parent;
            if (curr != -1) cout << " -> ";
        }
        cout << endl;
    }

    // 6. 层次遍历（广度优先遍历）
    void levelOrder() const {
        if (root == -1) {
            cout << "树为空！" << endl;
            return;
        }
        cout << "层次遍历结果：";
        // 用队列存储当前层的节点索引
        vector<int> queue = { root };
        while (!queue.empty()) {
            int currIdx = queue.front();
            queue.erase(queue.begin());  // 出队
            cout << nodes[currIdx].data << " ";
            // 入队所有子节点
            vector<int> children = getChildren(currIdx);
            queue.insert(queue.end(), children.begin(), children.end());
        }
        cout << endl;
    }

    // 7. 递归实现深度优先遍历（先序）
    void preOrder(int nodeIdx) const {
        if (nodeIdx < 0 || nodeIdx >= nodes.size()) return;
        // 先访问当前节点
        cout << nodes[nodeIdx].data << " ";
        // 再递归访问所有子节点
        vector<int> children = getChildren(nodeIdx);
        for (int child : children) {
            preOrder(child);
        }
    }

    // 深度优先遍历入口（从根开始）
    void preOrder() const {
        if (root == -1) {
            cout << "树为空！" << endl;
            return;
        }
        cout << "先序遍历结果：";
        preOrder(root);
        cout << endl;
    }

    // 获取树的节点数量
    int size() const {
        return nodes.size();
    }
};

// 测试函数
int main() {
    ParentTree tree;

    // 构建示例树：
    //       1（根）
    //     / | \
    //    2  3  4
    //   /
    //  5
    tree.addRoot(1);                  // 根节点1（索引0）
    tree.addChild(0, 2);              // 为1添加子节点2（索引1）
    tree.addChild(0, 3);              // 为1添加子节点3（索引2）
    tree.addChild(0, 4);              // 为1添加子节点4（索引3）
    tree.addChild(1, 5);              // 为2添加子节点5（索引4）

    cout << "树的节点数量：" << tree.size() << endl;  // 输出5

    // 查找节点5的索引（预期4）
    int node5Idx = tree.findNode(5);
    cout << "节点5的索引：" << node5Idx << endl;

    // 追溯节点5到根的路径（5 -> 2 -> 1）
    tree.traceToRoot(node5Idx);

    // 遍历测试
    tree.levelOrder();  // 预期：1 2 3 4 5
    tree.preOrder();    // 预期：1 2 5 3 4

    return 0;
}