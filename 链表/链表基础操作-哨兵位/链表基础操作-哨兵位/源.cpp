#include <iostream>
using namespace std;

// 链表节点结构
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// 使用哨兵节点的链表操作类
class LinkedList {
private:
    ListNode* sentinel;  // 哨兵节点（伪头），不存储实际数据

public:
    // 构造函数：初始化哨兵节点，链表始终以哨兵为起点
    LinkedList() {
        sentinel = new ListNode(0);  // 哨兵节点的值无意义
    }

    // 析构函数：释放所有节点（包括哨兵）
    ~LinkedList() {
        ListNode* curr = sentinel;
        while (curr != nullptr) {
            ListNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    // 在头部插入节点（无需特殊判断）
    void insertAtHead(int val) {
        ListNode* newNode = new ListNode(val);
        newNode->next = sentinel->next;
        sentinel->next = newNode;
    }

    // 在尾部插入节点（无需特殊判断空链表）
    void insertAtTail(int val) {
        ListNode* newNode = new ListNode(val);
        ListNode* curr = sentinel;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = newNode;
    }

    // 在指定索引插入节点（index从0开始）,插入的情况可以把curr定位到前一个节点，但是不必保证curr->next不为nullptr
    bool insertAtIndex(int index, int val) {
        ListNode* newNode = new ListNode(val);
        ListNode* curr = sentinel;
        for (int i = 0; i < index; i++) {
            if (curr == nullptr) {
                return false;  // 索引超出范围
            }
            curr = curr->next;
        }
        if (curr == nullptr) {
            return false;
        }// 索引超出范围
        newNode->next = curr->next;
        curr->next = newNode;
        return true;
    }

    // 按值删除第一个匹配的节点（无需特殊处理头节点）
    bool deleteByValue(int val) {
        ListNode* curr = sentinel;
        while (curr->next) {
            if (curr->next->val == val) {
                ListNode* temp = curr->next;
                curr->next = curr->next->next;
                delete temp;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    // 按索引删除节点（无需特殊处理头节点）
    bool deleteByIndex(int index) {
        ListNode* curr = sentinel;
        for (int i = 0; i < index; ++i) {
            if (curr->next == nullptr) {//可以写成curr == nullptr
                return false;  // 索引超出范围
            }
            curr = curr->next;
        }

        if (curr->next == nullptr) {
            return false;  // 索引超出范围
        }
        ListNode* temp = curr->next;
        curr->next = curr->next->next;
        delete temp;
        return true;
    }

    // 打印链表（从哨兵的next开始，即实际头节点）
    void printList() {
        ListNode* curr = sentinel->next;  // 跳过哨兵节点
        if (curr == nullptr) {
            cout << "链表为空" << endl;
            return;
        }

        cout << "链表元素: ";
        while (curr != nullptr) {
            cout << curr->val << " -> ";
            curr = curr->next;
        }
        cout << "nullptr" << endl;
    }

    // 获取链表长度（实际节点数，不含哨兵）
    int getLength() {
        int length = 0;
        ListNode* curr = sentinel->next;
        while (curr != nullptr) {
            length++;
            curr = curr->next;
        }
        return length;
    }
    };

    // 测试主函数
    int main() {
        LinkedList list;

        // 测试插入操作
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtHead(5);    // 哨兵让头插逻辑简化
        list.insertAtIndex(2, 15);
        cout << "插入操作后：";
        list.printList();  // 预期: 5 -> 10 -> 15 -> 20 -> nullptr

        // 测试删除操作
        list.deleteByValue(10);  // 无需特殊处理头节点
        cout << "删除值为10的节点后：";
        list.printList();  // 预期: 5 -> 15 -> 20 -> nullptr

        list.deleteByIndex(0);   // 删除原头节点（5），逻辑统一
        cout << "删除索引0的节点后：";
        list.printList();  // 预期: 15 -> 20 -> nullptr

        return 0;
    }
