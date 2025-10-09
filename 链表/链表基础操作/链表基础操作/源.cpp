#include<iostream>
using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode() :val(0), next(nullptr){}
	ListNode(int x) :val(x),next(nullptr){}

};

class LinkedList {
private:
	ListNode* head;
public:
	LinkedList():head(nullptr){}
    ~LinkedList() {
        ListNode* curr = head;
        while (curr != nullptr) {
            ListNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
        head = nullptr;
    }

    void insertAtHead(int val) {
        ListNode* newNode = new ListNode(val);
        newNode->next = head;
        head = newNode;
    }

    void insertAtTail(int val) {
        ListNode* newNode = new ListNode(val);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        ListNode* curr = head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newNode;
    }

    // 在指定位置插入节点（index从0开始）
    bool insertAtIndex(int index, int val) {
        //特殊情况处理：插入到头部/链表为空
        if (index == 0) {
            insertAtHead(val);
            return true;
        }
        ListNode* curr = head;
        //（链表没有哨兵节点的情况）当curr是头指针且链表索引从0开始时，移动index-1次可以得到当前要插入的位置的前一个节点
        for (int i = 0; i < index-1; i++) {
            if (curr == nullptr) {
                return false;
            }
            curr = curr->next;
        }
        if (curr == nullptr) {
            return false;
        }
        ListNode* newNode=new ListNode(val);
        newNode->next = curr->next;
        curr->next = newNode;
        return true;
    }

    // 删除指定值的第一个节点
    bool deleteByValue(int val) {
        if (head == NULL) return false;
        
        // 特殊情况：删除头节点
        if (head->val == val) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
            return true;
        }
        ListNode* curr = head;
        while (curr->next) {
            if (curr->next->val == val) {
                ListNode* temp = curr->next;
                curr->next = curr->next->next;
                delete temp;
                return true;
            }
        }
        return false;
    }

    // 删除指定索引的节点（index从0开始）
    bool deleteByIndex(int index) {
        if (head == nullptr) {
            return false;  // 链表为空
        }
        if (index==0) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
            return true;
        }
        ListNode* curr = head;
        for (int i = 0; i < index - 1; i++)
        {
            if (curr->next == nullptr)return false;
            //与上面在指定位置插入节点不同的是此时需要保证当前位置的下一个节点也不为空
            curr = curr->next;
        }
        if (curr->next == nullptr)return false;
        ListNode* temp = curr->next;
        curr->next = curr->next->next;
        delete temp;
        return true;
    }

    // 查找指定值的节点，返回其索引（-1表示未找到）
    int findIndex(int val) {
        if (head == nullptr)return false;
        ListNode* curr = head;
        int index = 0;
        while (curr) {
            if (curr->val == val)return index;
            curr = curr->next;
            index++;
        }
        return false;
    }

    void reverse() {
        ListNode* prev = nullptr;    // 前一个节点
        ListNode* curr = head;       // 当前节点
        ListNode* next = nullptr;
        while (curr != nullptr) {
            next = curr->next;  // 保存下一个节点
            curr->next = prev;  // 反转当前节点的指针
            prev = curr;        // 前一个节点后移
            curr = next;        // 当前节点后移
        }
        head = prev;  // 更新头节点为原尾节点
    }

    // 打印链表所有元素
    void printList() {
        if (head == nullptr) {
            cout << "链表为空" << endl;
            return;
        }

        ListNode* curr = head;
        while (curr) {
            cout << curr->val << " -> ";
            curr = curr->next;
        }
        cout << "nullptr" << endl;
    }

    // 获取链表长度
    int getLength() {
        int length = 0;
        ListNode* curr = head;
        while (curr) {
            length++;
            curr = curr->next;
        }
        return length;
    }
};

// 主函数：测试链表操作
int main() {
    LinkedList list;

    // 测试插入操作
    list.insertAtTail(10);
    list.insertAtTail(20);
    list.insertAtHead(5);
    list.insertAtIndex(2, 15);
    cout << "插入操作后：";
    list.printList();  // 预期: 5 -> 10 -> 15 -> 20 -> nullptr
    cout << "链表长度: " << list.getLength() << endl;  // 预期: 4

    // 测试查找操作
    int val = 15;
    int index = list.findIndex(val);
    if (index != -1) {
        cout << "值为 " << val << " 的节点索引为: " << index << endl;  // 预期: 2
    }
    else {
        cout << "未找到值为 " << val << " 的节点" << endl;
    }

    // 测试删除操作
    list.deleteByValue(10);
    cout << "删除值为10的节点后：";
    list.printList();  // 预期: 5 -> 15 -> 20 -> nullptr

    list.deleteByIndex(1);
    cout << "删除索引为1的节点后：";
    list.printList();  // 预期: 5 -> 20 -> nullptr

    // 测试反转操作
    list.reverse();
    cout << "反转链表后：";
    list.printList();  // 预期: 20 -> 5 -> nullptr

    return 0;
}
