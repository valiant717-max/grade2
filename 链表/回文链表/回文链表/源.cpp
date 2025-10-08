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
    bool isPalindrome(ListNode* head) {
        if (head == nullptr) return true;
        vector<int> vals;
        ListNode* cur = head;
        while (cur != nullptr) {
            vals.push_back(cur->val);
            cur = cur->next;
        }
        int left = 0, right = vals.size() - 1;
        while (left < right) {
            if (vals[left] != vals[right]) return false;
            left++;
            right--;
        }
        return true;
    }
};

// 根据数组创建链表
ListNode* createLinkedList(const vector<int>& nums) {
    if (nums.empty()) return nullptr;

    ListNode* head = new ListNode(nums[0]);
    ListNode* current = head;

    for (int i = 1; i < nums.size(); ++i) {
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

    // 测试用例1: 空链表
    ListNode* test1 = nullptr;
    cout << "测试用例1: 空链表" << endl;
    cout << "是否为回文: " << (solution.isPalindrome(test1) ? "是" : "否") << endl << endl;

    // 测试用例2: 单个节点
    ListNode* test2 = createLinkedList({ 1 });
    cout << "测试用例2: 单个节点链表: ";
    printLinkedList(test2);
    cout << "是否为回文: " << (solution.isPalindrome(test2) ? "是" : "否") << endl << endl;

    // 测试用例3: 回文链表(偶数个节点)
    ListNode* test3 = createLinkedList({ 1, 2, 2, 1 });
    cout << "测试用例3: 回文链表(偶数个节点): ";
    printLinkedList(test3);
    cout << "是否为回文: " << (solution.isPalindrome(test3) ? "是" : "否") << endl << endl;

    // 测试用例4: 回文链表(奇数个节点)
    ListNode* test4 = createLinkedList({ 1, 2, 3, 2, 1 });
    cout << "测试用例4: 回文链表(奇数个节点): ";
    printLinkedList(test4);
    cout << "是否为回文: " << (solution.isPalindrome(test4) ? "是" : "否") << endl << endl;

    // 测试用例5: 非回文链表
    ListNode* test5 = createLinkedList({ 1, 2, 3, 4, 5 });
    cout << "测试用例5: 非回文链表: ";
    printLinkedList(test5);
    cout << "是否为回文: " << (solution.isPalindrome(test5) ? "是" : "否") << endl << endl;

    // 释放内存
    freeLinkedList(test2);
    freeLinkedList(test3);
    freeLinkedList(test4);
    freeLinkedList(test5);

    return 0;
}
