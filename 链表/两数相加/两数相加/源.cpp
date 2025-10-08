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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummyHead = new ListNode(0);
        ListNode* curr = dummyHead;
        ListNode* p = l1, * q = l2;
        int carry = 0;
        int sum = 0;
        while (p != nullptr && q != nullptr) {
            sum = (p->val + q->val + carry) % 10;
            carry = (p->val + q->val + carry) / 10;
            curr->next = new ListNode(sum);
            curr = curr->next;
            p = p->next;
            q = q->next;

        }
        while (p != nullptr) {
            curr->next = new ListNode((p->val + carry) % 10);
            carry = (p->val + carry) / 10;
            p = p->next;
			curr = curr->next;
        }
        while (q != nullptr) {
            curr->next = new ListNode((q->val + carry) % 10);
            carry = (q->val + carry) / 10;
            q = q->next;
			curr = curr->next;
        }
        if (carry > 0) {
            curr->next = new ListNode(carry);
        }
        return dummyHead->next;
    }
};

// 根据数组创建链表（逆序存储数字，如[2,4,3]表示342）
ListNode* createLinkedList(const vector<int>& nums) {
    ListNode* dummy = new ListNode(0);
    ListNode* curr = dummy;
    for (int num : nums) {
        curr->next = new ListNode(num);
        curr = curr->next;
    }
    return dummy->next;
}

// 打印链表
void printLinkedList(ListNode* head) {
    ListNode* curr = head;
    while (curr != nullptr) {
        cout << curr->val;
        if (curr->next != nullptr) {
            cout << " -> ";
        }
        curr = curr->next;
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

    // 测试用例1: 正常情况，长度相同无进位
    ListNode* l1 = createLinkedList({ 2, 4, 3 });  // 表示342
    ListNode* l2 = createLinkedList({ 5, 6, 4 });  // 表示465
    cout << "测试用例1:" << endl;
    cout << "l1: "; printLinkedList(l1);
    cout << "l2: "; printLinkedList(l2);
    ListNode* result1 = solution.addTwoNumbers(l1, l2);
    cout << "结果: "; printLinkedList(result1);  // 预期7 -> 0 -> 8 (807)
    cout << endl;

    // 测试用例2: 长度相同有进位
    ListNode* l3 = createLinkedList({ 9, 9, 9 });  // 表示999
    ListNode* l4 = createLinkedList({ 9, 9, 9 });  // 表示999
    cout << "测试用例2:" << endl;
    cout << "l3: "; printLinkedList(l3);
    cout << "l4: "; printLinkedList(l4);
    ListNode* result2 = solution.addTwoNumbers(l3, l4);
    cout << "结果: "; printLinkedList(result2);  // 预期8 -> 9 -> 9 -> 1 (1998)
    cout << endl;

    // 测试用例3: 长度不同
    ListNode* l5 = createLinkedList({ 2, 4 });     // 表示42
    ListNode* l6 = createLinkedList({ 5, 6, 4 });  // 表示465
    cout << "测试用例3:" << endl;
    cout << "l5: "; printLinkedList(l5);
    cout << "l6: "; printLinkedList(l6);
    ListNode* result3 = solution.addTwoNumbers(l5, l6);
    cout << "结果: "; printLinkedList(result3);  // 预期7 -> 0 -> 5 (507)
    cout << endl;

    // 测试用例4: 其中一个链表为空
    ListNode* l7 = nullptr;
    ListNode* l8 = createLinkedList({ 1, 2, 3 });  // 表示321
    cout << "测试用例4:" << endl;
    cout << "l7: 空链表" << endl;
    cout << "l8: "; printLinkedList(l8);
    ListNode* result4 = solution.addTwoNumbers(l7, l8);
    cout << "结果: "; printLinkedList(result4);  // 预期1 -> 2 -> 3
    cout << endl;

    // 测试用例5: 单个节点相加
    ListNode* l9 = createLinkedList({ 5 });        // 表示5
    ListNode* l10 = createLinkedList({ 5 });       // 表示5
    cout << "测试用例5:" << endl;
    cout << "l9: "; printLinkedList(l9);
    cout << "l10: "; printLinkedList(l10);
    ListNode* result5 = solution.addTwoNumbers(l9, l10);
    cout << "结果: "; printLinkedList(result5);  // 预期0 -> 1 (10)
    cout << endl;

    // 释放内存
    freeLinkedList(l1);
    freeLinkedList(l2);
    freeLinkedList(result1);
    freeLinkedList(l3);
    freeLinkedList(l4);
    freeLinkedList(result2);
    freeLinkedList(l5);
    freeLinkedList(l6);
    freeLinkedList(result3);
    freeLinkedList(l8);
    freeLinkedList(result4);
    freeLinkedList(l9);
    freeLinkedList(l10);
    freeLinkedList(result5);

    return 0;
}
