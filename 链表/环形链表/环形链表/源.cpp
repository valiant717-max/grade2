#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

// 链表节点定义
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    bool hasCycle(ListNode* head) {
        unordered_set<ListNode*> nodes;
        ListNode* current = head;
        if (current == NULL) return false;
        while (current != NULL) {
            nodes.insert(current);
            current = current->next;
            if (nodes.find(current) != nodes.end()) return true;
        }
        return false;
    }
};

// 根据数组创建无环链表
ListNode* createLinkedList(const vector<int>& nums) {
    if (nums.empty()) return nullptr;

    ListNode* head = new ListNode(nums[0]);
    ListNode* current = head;

    for (size_t i = 1; i < nums.size(); ++i) {
        current->next = new ListNode(nums[i]);
        current = current->next;
    }

    return head;
}

// 创建有环链表（让最后一个节点指向第pos个节点，pos从0开始）
ListNode* createCycledLinkedList(const vector<int>& nums, int pos) {
    if (nums.empty()) return nullptr;

    ListNode* head = new ListNode(nums[0]);
    ListNode* current = head;
    ListNode* cycleNode = nullptr;

    // 记录要形成环的节点
    if (pos == 0) {
        cycleNode = head;
    }

    for (size_t i = 1; i < nums.size(); ++i) {
        current->next = new ListNode(nums[i]);
        current = current->next;
        if (i == pos) {
            cycleNode = current;
        }
    }

    // 让最后一个节点指向cycleNode形成环
    current->next = cycleNode;

    return head;
}

// 释放无环链表内存
void freeLinkedList(ListNode* head) {
    ListNode* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Solution solution;

    // 测试用例1: 空链表
    ListNode* test1 = nullptr;
    cout << "测试用例1: 空链表" << endl;
    cout << "是否有环: " << (solution.hasCycle(test1) ? "是" : "否") << endl << endl;

    // 测试用例2: 单个节点无环
    ListNode* test2 = createLinkedList({ 1 });
    cout << "测试用例2: 单个节点无环" << endl;
    cout << "是否有环: " << (solution.hasCycle(test2) ? "是" : "否") << endl << endl;

    // 测试用例3: 多个节点无环
    ListNode* test3 = createLinkedList({ 1, 2, 3, 4, 5 });
    cout << "测试用例3: 多个节点无环" << endl;
    cout << "是否有环: " << (solution.hasCycle(test3) ? "是" : "否") << endl << endl;

    // 测试用例4: 有环链表（环在中间）
    ListNode* test4 = createCycledLinkedList({ 1, 2, 3, 4, 5 }, 2); // 最后一个节点指向索引2的节点（值为3）
    cout << "测试用例4: 有环链表（环在中间）" << endl;
    cout << "是否有环: " << (solution.hasCycle(test4) ? "是" : "否") << endl << endl;

    // 测试用例5: 有环链表（环在头部）
    ListNode* test5 = createCycledLinkedList({ 1, 2, 3 }, 0); // 最后一个节点指向头节点
    cout << "测试用例5: 有环链表（环在头部）" << endl;
    cout << "是否有环: " << (solution.hasCycle(test5) ? "是" : "否") << endl << endl;

    // 释放无环链表内存（有环链表无法直接释放，会导致无限循环，实际使用中需特殊处理）
    freeLinkedList(test2);
    freeLinkedList(test3);

    return 0;
}
