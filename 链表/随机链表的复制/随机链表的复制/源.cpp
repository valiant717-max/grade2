#include <iostream>
#include <unordered_map>

using namespace std;

// 定义链表节点结构
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

class Solution {
public:
    unordered_map<Node*, Node*>cachedNode;
    Node* copyRandomList(Node* head) {
        if (head == nullptr) return nullptr;

        // 如果当前节点未被复制，则创建新节点并递归处理
        if (!cachedNode.count(head)) {
            Node* headNew = new Node(head->val);
            cachedNode[head] = headNew;
            // 递归复制next指针
            headNew->next = copyRandomList(head->next);
            // 递归复制random指针
            headNew->random = copyRandomList(head->random);
        }

        // 返回当前节点对应的复制节点
        return cachedNode[head];
    }
};

// 辅助函数：打印链表信息（值和random指向的索引）
void printList(Node* head) {
    if (head == nullptr) {
        cout << "链表为空" << endl;
        return;
    }

    // 先创建节点到索引的映射，方便打印random指向
    unordered_map<Node*, int> nodeToIndex;
    Node* curr = head;
    int index = 0;
    while (curr != nullptr) {
        nodeToIndex[curr] = index++;
        curr = curr->next;
    }

    // 打印每个节点的信息
    curr = head;
    while (curr != nullptr) {
        cout << "节点值: " << curr->val;
        if (curr->random != nullptr) {
            cout << ", random指向索引: " << nodeToIndex[curr->random];
        }
        else {
            cout << ", random指向: null";
        }
        cout << endl;
        curr = curr->next;
    }
}

// 主函数：创建测试链表并验证拷贝结果
int main() {
    // 创建原链表节点
    Node* node0 = new Node(10);
    Node* node1 = new Node(20);
    Node* node2 = new Node(30);

    // 设置next指针关系
    node0->next = node1;
    node1->next = node2;
    node2->next = nullptr;

    // 设置random指针关系
    node0->random = node2;  // 节点0的random指向节点2
    node1->random = nullptr; // 节点1的random指向null
    node2->random = node0;  // 节点2的random指向节点0

    cout << "原链表信息:" << endl;
    printList(node0);

    // 执行深拷贝
    Solution solution;
    Node* copiedHead = solution.copyRandomList(node0);

    cout << "\n复制链表信息:" << endl;
    printList(copiedHead);

    // 验证是否为深拷贝（检查指针是否完全独立）
    bool isDeepCopy = (node0 != copiedHead) &&
        (node0->next != copiedHead->next) &&
        (node0->random != copiedHead->random);
    cout << "\n是否为深拷贝: " << (isDeepCopy ? "是" : "否") << endl;

    // 释放内存（实际应用中需要完整的释放逻辑）
    delete node0;
    delete node1;
    delete node2;

    // 释放复制链表
    Node* curr = copiedHead;
    while (curr != nullptr) {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }

    return 0;
}
