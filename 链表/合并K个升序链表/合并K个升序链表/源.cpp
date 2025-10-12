#include<iostream>
#include<vector>
#include<set>
using namespace std;

// 链表节点定义（原代码已有）
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {};
    ListNode(int x) : val(x), next(nullptr) {};
    ListNode(int x, ListNode* next) : val(x), next(next) {};
};

// 辅助函数1：根据vector创建链表（方便快速构造测试用链表）
ListNode* createLinkedList(const vector<int>& nums) {
    if (nums.empty()) return nullptr; // 空vector返回空链表
    ListNode* head = new ListNode(nums[0]); // 头节点
    ListNode* curr = head;
    for (int i = 1; i < nums.size(); i++) {
        curr->next = new ListNode(nums[i]); // 逐个创建节点
        curr = curr->next;
    }
    return head;
}

// 辅助函数2：打印链表（验证合并结果）
void printLinkedList(ListNode* head) {
    if (head == nullptr) { // 空链表
        cout << "[]" << endl;
        return;
    }
    ListNode* curr = head;
    cout << "[";
    while (curr != nullptr) {
        cout << curr->val;
        if (curr->next != nullptr) cout << ", "; // 非最后一个节点加逗号
        curr = curr->next;
    }
    cout << "]" << endl;
}

// 辅助函数3：释放链表内存（避免内存泄漏）
void freeLinkedList(ListNode* head) {
    ListNode* curr = head;
    while (curr != nullptr) {
        ListNode* temp = curr; // 暂存当前节点
        curr = curr->next;     // 移动到下一个节点
        delete temp;           // 释放当前节点内存
    }
}

// 原解决方案（mergeKLists函数）
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int length = lists.size();
        multiset<int> ms;

        // 1. 遍历所有链表，将所有节点值存入multiset（自动排序）
        for (int i = 0; i < length; i++) {
            ListNode* curr = lists[i];
            // 遍历当前链表的每个节点
            while (curr != nullptr) { // 原代码漏了curr = curr->next，此处修复！
                ms.insert(curr->val);
                curr = curr->next; // 关键：移动到下一个节点，否则会无限循环
            }
        }

        // 2. 若multiset为空（所有链表都空），返回空
        if (ms.empty()) return nullptr;

        // 3. 从multiset中取排序后的元素，构造新链表
        int length2 = ms.size();
        auto it = ms.begin();
        ListNode* head = new ListNode(*it); // 头节点
        it++;
        ListNode* curr = head;

        // 循环构造剩余节点（原代码循环次数多1次，修复为i从1开始）
        for (int i = 1; i < length2; i++) { // 已创建头节点，剩余length2-1个节点
            curr->next = new ListNode(*it);
            it++;
            curr = curr->next;
        }

        return head;
    }
};

// 主函数：测试入口
int main() {
    Solution sol;

    // -------------------------- 测试用例1：空链表集合 --------------------------
    cout << "=== 测试用例1：空链表集合 ===" << endl;
    vector<ListNode*> lists1; // 空vector（无任何链表）
    ListNode* res1 = sol.mergeKLists(lists1);
    cout << "合并结果：";
    printLinkedList(res1);
    freeLinkedList(res1); // 释放内存


    // -------------------------- 测试用例2：含空链表的集合 --------------------------
    cout << "\n=== 测试用例2：含空链表的集合 ===" << endl;
    ListNode* list2_1 = createLinkedList({ 1, 4, 5 });  // 链表1：1->4->5
    ListNode* list2_2 = nullptr;                      // 链表2：空
    ListNode* list2_3 = createLinkedList({ 2, 3, 6 });  // 链表3：2->3->6
    vector<ListNode*> lists2 = { list2_1, list2_2, list2_3 };

    ListNode* res2 = sol.mergeKLists(lists2);
    cout << "合并前链表1："; printLinkedList(list2_1);
    cout << "合并前链表2："; printLinkedList(list2_2);
    cout << "合并前链表3："; printLinkedList(list2_3);
    cout << "合并结果："; printLinkedList(res2);

    // 释放所有链表内存
    freeLinkedList(list2_1);
    freeLinkedList(list2_2); // 空链表释放无影响
    freeLinkedList(list2_3);
    freeLinkedList(res2);


    // -------------------------- 测试用例3：多个链表含重复值 --------------------------
    cout << "\n=== 测试用例3：多个链表含重复值 ===" << endl;
    ListNode* list3_1 = createLinkedList({ 2, 2, 3 });  // 链表1：2->2->3
    ListNode* list3_2 = createLinkedList({ 1, 2, 4 });  // 链表2：1->2->4
    vector<ListNode*> lists3 = { list3_1, list3_2 };

    ListNode* res3 = sol.mergeKLists(lists3);
    cout << "合并前链表1："; printLinkedList(list3_1);
    cout << "合并前链表2："; printLinkedList(list3_2);
    cout << "合并结果："; printLinkedList(res3);

    freeLinkedList(list3_1);
    freeLinkedList(list3_2);
    freeLinkedList(res3);


    // -------------------------- 测试用例4：只有一个链表 --------------------------
    cout << "\n=== 测试用例4：只有一个链表 ===" << endl;
    ListNode* list4_1 = createLinkedList({ 5, 3, 1 });  // 链表：5->3->1（原链表无序，合并后应排序）
    vector<ListNode*> lists4 = { list4_1 };

    ListNode* res4 = sol.mergeKLists(lists4);
    cout << "合并前链表："; printLinkedList(list4_1);
    cout << "合并结果："; printLinkedList(res4);

    freeLinkedList(list4_1);
    freeLinkedList(res4);


    // -------------------------- 测试用例5：所有链表都空 --------------------------
    cout << "\n=== 测试用例5：所有链表都空 ===" << endl;
    ListNode* list5_1 = nullptr;
    ListNode* list5_2 = nullptr;
    vector<ListNode*> lists5 = { list5_1, list5_2 };

    ListNode* res5 = sol.mergeKLists(lists5);
    cout << "合并结果：";
    printLinkedList(res5);
    freeLinkedList(res5);

    return 0;
}