#include<iostream>
#include<set>
using namespace std;

struct ListNode{
    int val;
    ListNode* next;
    ListNode() :val(0), next(nullptr) {};
    ListNode(int x) :val(x), next(nullptr) {};
    ListNode(int x, ListNode* next) : val(x), next(next) {}

};

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        multiset<int> ms;
        ListNode* curr = head;
        if (head == nullptr)return head;
        while (curr) {
            ms.insert(curr->val);
            curr = curr->next;
        }
        int length = ms.size();
        auto it = ms.begin();
        ListNode* newHead = new ListNode(*it);
        it++;
        ListNode* curr2 = newHead;
        for (int i = 0; i < length-1; i++) {
            ListNode* newNode = new ListNode(*it);
            curr2->next = newNode;
            curr2 = curr2->next;
            it++;
        }
        return newHead;
    }

    void printList(ListNode* head) {
        if (head == nullptr)return;
        ListNode* curr = head;
        while (curr) {
            cout << curr->val;
            if (curr->next)cout << "->";
            curr = curr->next;
        }
        return;
    }
};

int main() {
    Solution s;
    ListNode* newNode1 = new ListNode(3);
    ListNode* newNode2 = new ListNode(6);
    ListNode* newNode3 = new ListNode(4);
    ListNode* newNode4 = new ListNode(5);
    ListNode* newNode5 = new ListNode(1);
    ListNode* newNode6 = new ListNode(5);
    newNode1->next = newNode2;
    newNode2->next = newNode3;
    newNode3->next = newNode4;
    newNode4->next = newNode5;
    newNode5->next = newNode6;
    s.sortList(newNode1);
    s.printList(s.sortList(newNode1));
    return 0;
}