#include <iostream>
#include <vector>
#include<tuple>
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
    pair<ListNode*, ListNode*> myReverse(ListNode* head, ListNode* tail) {
        ListNode* prev = tail->next;  // 初始化prev为尾节点的下一个节点（用于连接）
        ListNode* p = head;           // p指向当前需要翻转的节点
        // 当prev不等于tail时，说明还没完成翻转
        while (prev != tail) {
            ListNode* nex = p->next;  // 保存当前节点的下一个节点
            p->next = prev;           // 当前节点指向prev（完成反转）
            prev = p;                 // prev移动到当前节点
            p = nex;                  // p移动到下一个节点
        }
        return { tail, head };
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k <= 1 || !head) return head;
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* pre = dummy;
        while (true) {
            ListNode* tail = pre;//当前处理子链表的上一个节点
            for (int i = 0; i < k; i++) {
                tail = tail->next;
                if (!tail) {
                    return dummy->next;
                }
            }
            tie(head, tail) = myReverse(head, tail);
            //pair<ListNode*, ListNode*> reversed = myReverse(head, tail);
            //head = reversed.first;   
            //tail = reversed.second;  
            pre->next = head;
            pre = tail;        // 更新pre为当前子链表的尾（下一组的前一个节点）
            head = tail->next;
        }
        return dummy->next;
    }
};

// 将向量转换为链表
ListNode* vectorToList(const std::vector<int>& vec) {
    if (vec.empty()) return nullptr;

    ListNode* head = new ListNode(vec[0]);
    ListNode* curr = head;

    for (size_t i = 1; i < vec.size(); ++i) {
        curr->next = new ListNode(vec[i]);
        curr = curr->next;
    }

    return head;
}

// 将链表转换为向量（用于输出）
std::vector<int> listToVector(ListNode* head) {
    std::vector<int> result;
    ListNode* curr = head;

    while (curr) {
        result.push_back(curr->val);
        curr = curr->next;
    }

    return result;
}

// 辅助函数：打印向量内容
void printVector(const std::vector<int>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

// 主函数：测试reverseKGroup函数
int main() {
    Solution solution;

    // 测试案例1：k=2，偶数个节点
    std::vector<int> vec1 = { 1, 2, 3, 4, 5, 6 };
    ListNode* head1 = vectorToList(vec1);
    std::cout << "测试案例1 - 原始链表: ";
    printVector(vec1);
    ListNode* result1 = solution.reverseKGroup(head1, 2);
    std::cout << "k=2 反转后: ";
    printVector(listToVector(result1));

    // 测试案例2：k=3，刚好整除
    std::vector<int> vec2 = { 1, 2, 3, 4, 5, 6 };
    ListNode* head2 = vectorToList(vec2);
    std::cout << "\n测试案例2 - 原始链表: ";
    printVector(vec2);
    ListNode* result2 = solution.reverseKGroup(head2, 3);
    std::cout << "k=3 反转后: ";
    printVector(listToVector(result2));

    // 测试案例3：k=3，不能整除（剩余节点不反转）
    std::vector<int> vec3 = { 1, 2, 3, 4, 5 };
    ListNode* head3 = vectorToList(vec3);
    std::cout << "\n测试案例3 - 原始链表: ";
    printVector(vec3);
    ListNode* result3 = solution.reverseKGroup(head3, 3);
    std::cout << "k=3 反转后: ";
    printVector(listToVector(result3));

    // 测试案例4：单个节点
    std::vector<int> vec4 = { 1 };
    ListNode* head4 = vectorToList(vec4);
    std::cout << "\n测试案例4 - 原始链表: ";
    printVector(vec4);
    ListNode* result4 = solution.reverseKGroup(head4, 2);
    std::cout << "k=2 反转后: ";
    printVector(listToVector(result4));

    // 测试案例5：空链表
    std::vector<int> vec5 = {};
    ListNode* head5 = vectorToList(vec5);
    std::cout << "\n测试案例5 - 原始链表: ";
    printVector(vec5);
    ListNode* result5 = solution.reverseKGroup(head5, 3);
    std::cout << "k=3 反转后: ";
    printVector(listToVector(result5));

    return 0;
}
