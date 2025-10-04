#include <iostream>
using namespace std;

// 链表节点
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
    //ListNode(int x) {
    //    val = x;         
    //    next = nullptr;   
    //}
};

class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        ListNode* p = headA;
        ListNode* q = headB;
        while (p != q) {
            // 指针p移动：不为空则后移，为空则切换到链表B
            p = p ? p->next : headB;
            // 指针q移动：不为空则后移，为空则切换到链表A
            q = q ? q->next : headA;
        }
        return p;
    }
};

// 辅助函数：创建链表
ListNode* createList(int arr[], int n) {
    if (n == 0) return nullptr;
    ListNode* head = new ListNode(arr[0]);
	ListNode* cur = head;//head指向第一个节点，head-> next指向第二个节点
    for (int i = 1; i < n; i++) {
        cur->next = new ListNode(arr[i]);
        cur = cur->next;
    }
    return head;
}

// 辅助函数：设置两个链表的相交节点
void setIntersection(ListNode* headA, ListNode* headB, int skipA, int skipB) {
    // 移动到链表A的相交起始位置
    ListNode* curA = headA;
    for (int i = 0; i < skipA; i++) {
        curA = curA->next;
    }
    // 移动到链表B的相交起始位置前一个节点
    ListNode* curB = headB;
    for (int i = 0; i < skipB - 1; i++) {
        curB = curB->next;
    }
    // 将B的该节点指向A的相交起始节点，形成相交
    curB->next = curA;
}

// 打印链表
void printList(ListNode* head) {
    ListNode* cur = head;
    while (cur) {
        cout << cur->val << " -> ";
        cur = cur->next;
    }
    //遍历到链表的末尾（最终 cur 会指向 nullptr）
    cout << "nullptr" << endl;
}

int main() {
    // 测试用例1：两链表相交
    int arrA[] = { 4, 1 };
    int arrB[] = { 5, 0, 1 };
    int arrCommon[] = { 8, 4, 5 };  // 相交部分

    ListNode* headA = createList(arrA, 2);
    ListNode* headB = createList(arrB, 3);
    ListNode* common = createList(arrCommon, 3);

    // 连接链表A与相交部分
    ListNode* cur = headA;
    while (cur->next) cur = cur->next;
    cur->next = common;
    //找到链表的倒数第二个节点,适用于需要在最后一个节点前插入新节点，或修改最后一个节点的指向
    // 
    // 连接链表B与相交部分（在索引2的位置开始相交）
    cur = headB;
    for (int i = 0; i < 2; i++) cur = cur->next;
    cur->next = common;

    cout << "链表A: ";
    printList(headA);  // 4 -> 1 -> 8 -> 4 -> 5 -> nullptr
    cout << "链表B: ";
    printList(headB);  // 5 -> 0 -> 1 -> 8 -> 4 -> 5 -> nullptr

    Solution solution;
    ListNode* intersection = solution.getIntersectionNode(headA, headB);
    if (intersection) {
        cout << "相交节点值为: " << intersection->val << endl;  // 应输出8
    }
    else {
        cout << "两链表不相交" << endl;
    }

    // 测试用例2：两链表不相交
    int arrC[] = { 2, 6, 4 };
    int arrD[] = { 1, 5 };
    ListNode* headC = createList(arrC, 3);
    ListNode* headD = createList(arrD, 2);

    cout << "\n链表C: ";
    printList(headC);  // 2 -> 6 -> 4 -> nullptr
    cout << "链表D: ";
    printList(headD);  // 1 -> 5 -> nullptr

    ListNode* noIntersection = solution.getIntersectionNode(headC, headD);
    if (noIntersection) {
        cout << "相交节点值为: " << noIntersection->val << endl;
    }
    else {
        cout << "两链表不相交" << endl;  // 应输出此结果
    }

    return 0;
}
