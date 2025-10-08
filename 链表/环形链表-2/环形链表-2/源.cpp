#include <iostream>
#include <unordered_set>
#include <vector>
#include<string>

using namespace std;

// 链表节点定义
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        // 使用哈希集合存储已访问过的节点
        unordered_set<ListNode*> visited;
        ListNode* current = head;
        while (current != nullptr) {
            // 如果当前节点已在集合中，说明找到环的起始节点
            if (visited.find(current) != visited.end()) {
                return current;
            }
            // 将当前节点加入集合
            visited.insert(current);
            // 移动到下一个节点
            current = current->next;
        }
        // 遍历结束未发现环，返回nullptr
        return nullptr;
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

// 打印链表（处理有环情况，避免无限循环）
void printLinkedList(ListNode* head, int maxNodes = 20) {
    ListNode* current = head;
    int count = 0;
    while (current != nullptr && count < maxNodes) {
        cout << current->val;
        if (current->next != nullptr) {
            cout << " -> ";
        }
        current = current->next;
        count++;
    }
    if (count >= maxNodes) {
        cout << " -> ... (可能存在环)";
    }
    cout << endl;
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
    ListNode* result1 = solution.detectCycle(test1);
    cout << "环的起始节点: " << (result1 ? to_string(result1->val) : "不存在环") << endl << endl;

    // 测试用例2: 单个节点无环
    ListNode* test2 = createLinkedList({ 1 });
    cout << "测试用例2: 单个节点无环" << endl;
    printLinkedList(test2);
    ListNode* result2 = solution.detectCycle(test2);
    cout << "环的起始节点: " << (result2 ? to_string(result2->val) : "不存在环") << endl << endl;

    // 测试用例3: 多个节点无环
    ListNode* test3 = createLinkedList({ 1, 2, 3, 4, 5 });
    cout << "测试用例3: 多个节点无环" << endl;
    printLinkedList(test3);
    ListNode* result3 = solution.detectCycle(test3);
    cout << "环的起始节点: " << (result3 ? to_string(result3->val) : "不存在环") << endl << endl;

    // 测试用例4: 有环链表（环在中间）
    ListNode* test4 = createCycledLinkedList({ 1, 2, 3, 4, 5 }, 2); // 最后一个节点指向值为3的节点
    cout << "测试用例4: 有环链表（环在中间）" << endl;
    printLinkedList(test4);
    ListNode* result4 = solution.detectCycle(test4);
    cout << "环的起始节点: " << (result4 ? to_string(result4->val) : "不存在环") << endl << endl;

    // 测试用例5: 有环链表（环在头部）
    ListNode* test5 = createCycledLinkedList({ 10, 20, 30 }, 0); // 最后一个节点指向头节点
    cout << "测试用例5: 有环链表（环在头部）" << endl;
    printLinkedList(test5);
    ListNode* result5 = solution.detectCycle(test5);
    cout << "环的起始节点: " << (result5 ? to_string(result5->val) : "不存在环") << endl << endl;

    // 释放无环链表内存
    freeLinkedList(test2);
    freeLinkedList(test3);

    return 0;
}

