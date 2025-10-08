#include <iostream>
#include <vector>

using namespace std;

// 链表节点定义
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // 处理空链表
        if (!head) return nullptr;

        // 计算链表长度
        ListNode* curr = head;
        int len = 0;
        while (curr) {
            len++;
            curr = curr->next;
        }

        // 处理n大于链表长度的情况
        if (n > len) return head;

        // 创建哨兵节点，简化头节点删除
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        curr = dummy;

        // 定位到待删除节点的前驱节点
        for (int i = 0; i < len - n; i++) {
            curr = curr->next;
        }

        // 删除目标节点
        ListNode* temp = curr->next;
        curr->next = curr->next->next;
        delete temp;

        // 保存新的头节点并释放哨兵节点
        ListNode* newHead = dummy->next;
        delete dummy;

        return newHead;
    }
};

// 根据数组创建链表
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

// 打印链表
void printLinkedList(ListNode* head) {
    ListNode* current = head;
    while (current != nullptr) {
        cout << current->val;
        if (current->next != nullptr) {
            cout << " -> ";
        }
        current = current->next;
    }
    cout << endl;
}

// 释放链表内存
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

    // 测试用例1: 普通情况，删除中间节点
    ListNode* test1 = createLinkedList({ 1, 2, 3, 4, 5 });
    cout << "测试用例1: 原链表: ";
    printLinkedList(test1);
    int n1 = 2;
    ListNode* result1 = solution.removeNthFromEnd(test1, n1);
    cout << "删除倒数第" << n1 << "个节点后: ";
    printLinkedList(result1);
    cout << endl;

    // 测试用例2: 删除头节点
    ListNode* test2 = createLinkedList({ 1, 2, 3 });
    cout << "测试用例2: 原链表: ";
    printLinkedList(test2);
    int n2 = 3;
    ListNode* result2 = solution.removeNthFromEnd(test2, n2);
    cout << "删除倒数第" << n2 << "个节点后: ";
    printLinkedList(result2);
    cout << endl;

    // 测试用例3: 删除尾节点
    ListNode* test3 = createLinkedList({ 10, 20, 30, 40 });
    cout << "测试用例3: 原链表: ";
    printLinkedList(test3);
    int n3 = 1;
    ListNode* result3 = solution.removeNthFromEnd(test3, n3);
    cout << "删除倒数第" << n3 << "个节点后: ";
    printLinkedList(result3);
    cout << endl;

    // 测试用例4: 链表只有一个节点
    ListNode* test4 = createLinkedList({ 5 });
    cout << "测试用例4: 原链表: ";
    printLinkedList(test4);
    int n4 = 1;
    ListNode* result4 = solution.removeNthFromEnd(test4, n4);
    cout << "删除倒数第" << n4 << "个节点后: ";
    printLinkedList(result4); // 应输出空
    cout << endl;

    // 测试用例5: n等于链表长度
    ListNode* test5 = createLinkedList({ 1, 2 });
    cout << "测试用例5: 原链表: ";
    printLinkedList(test5);
    int n5 = 2;
    ListNode* result5 = solution.removeNthFromEnd(test5, n5);
    cout << "删除倒数第" << n5 << "个节点后: ";
    printLinkedList(result5);
    cout << endl;

    // 释放内存
    freeLinkedList(result1);
    freeLinkedList(result2);
    freeLinkedList(result3);
    freeLinkedList(result4);
    freeLinkedList(result5);

    return 0;
}
