#include<iostream>
#include<vector>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() :val(0), next(nullptr) {};
    ListNode(int x) :val(x), next(nullptr) {};
    ListNode(int x, ListNode* next) :val(x), next(next) {}; 
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
        if ((!a) || (!b)) return a ? a : b;
        ListNode head;
        ListNode* tail = &head;
        ListNode* aPtr = a;
        ListNode* bPtr = b;
        while (aPtr && bPtr) {
            if (aPtr->val < bPtr->val) {
                tail->next = aPtr; aPtr = aPtr->next;
            }
            else {
                tail->next = bPtr; bPtr = bPtr->next;
            }
            tail = tail->next;
        }
        tail->next = (aPtr ? aPtr : bPtr);
        return head.next;
    }
    
    ListNode* merge(vector <ListNode*>& lists, int l, int r) {
        if (l == r) return lists[l];
        if (l > r) return nullptr;
        int mid = (l + r) >> 1;
        return mergeTwoLists(merge(lists, l, mid), merge(lists, mid + 1, r));
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return merge(lists, 0, lists.size() - 1);
    }
};

// 根据数组创建链表
ListNode* createList(const vector<int>& nums) {
    ListNode dummy;
    ListNode* curr = &dummy;
    for (int num : nums) {
        curr->next = new ListNode(num);
        curr = curr->next;
    }
    return dummy.next;
}

// 打印链表
void printList(ListNode* head) {
    ListNode* curr = head;
    while (curr) {
        cout << curr->val;
        if (curr->next) cout << " -> ";
        curr = curr->next;
    }
    cout << endl;
}

// 释放链表内存
void freeList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    // 创建测试用的K个有序链表
    vector<ListNode*> lists;
    lists.push_back(createList({ 1, 4, 5 }));    // 链表1
    lists.push_back(createList({ 1, 3, 4 }));    // 链表2
    lists.push_back(createList({ 2, 6 }));       // 链表3

    // 打印原始链表
    cout << "原始链表：" << endl;
    for (int i = 0; i < lists.size(); ++i) {
        cout << "链表" << i + 1 << "：";
        printList(lists[i]);
    }

    // 合并K个链表
    Solution solution;
    ListNode* mergedHead = solution.mergeKLists(lists);

    // 打印合并后的链表
    cout << "\n合并后的链表：";
    printList(mergedHead);

    // 释放内存
    freeList(mergedHead);
    // 注意：原始链表在合并过程中被复用，不需要单独释放

    return 0;
}
