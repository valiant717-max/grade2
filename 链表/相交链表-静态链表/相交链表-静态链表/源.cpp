#include <iostream>
#include <cstring>
using namespace std;

const int MAX_SIZE = 1000; 

int val[MAX_SIZE];          // 存储节点的值
int next_[MAX_SIZE];        // 存储下一个节点的下标，-1表示空
int idx = 0;                // 当前可用的节点下标

// 初始化静态链表
void initStaticList() {
    idx = 0;
    memset(val, 0, sizeof(val));
    memset(next_, -1, sizeof(next_));
}

// 创建新节点
int createNode(int x) {
    val[idx] = x;
    next_[idx] = -1;  // 初始指向空
    return idx++;     // 返回当前下标并自增
}

// 辅助函数：根据数组创建静态链表，返回头节点下标
int createList(int arr[], int n) {
    if (n == 0) return -1;  // -1表示空链表

    int head = createNode(arr[0]);
    int cur = head;

    for (int i = 1; i < n; i++) {
        int newNode = createNode(arr[i]);
        next_[cur] = newNode;  // 当前节点指向新节点
        cur = newNode;         // 移动到新节点
    }
    return head;
}

// 辅助函数：设置两个静态链表的相交节点
void setIntersection(int headA, int headB, int skipA, int skipB) {
    // 找到链表A的相交起始位置
    int curA = headA;
    for (int i = 0; i < skipA; i++) {
        curA = next_[curA];
    }

    // 找到链表B的相交起始位置的前一个节点
    int curB = headB;
    for (int i = 0; i < skipB - 1; i++) {
        curB = next_[curB];
    }

    // 设置相交
    next_[curB] = curA;
}

// 辅助函数：打印静态链表
void printList(int head) {
    int cur = head;
    while (cur != -1) {
        cout << val[cur] << "->";
        cur = next_[cur];
    }
    cout << "nullptr" << endl;
}

// 寻找相交节点的类
class Solution {
public:
    // 参数为两个链表的头节点下标，返回相交节点下标（-1表示不相交）
    int getIntersectionNode(int headA, int headB) {
        int p = headA;
        int q = headB;

        while (p != q) {
            // 指针p移动：不为空（-1）则后移，否则切换到链表B
            p = (p != -1) ? next_[p] : headB;
            // 指针q移动：不为空（-1）则后移，否则切换到链表A
            q = (q != -1) ? next_[q] : headA;
        }

        return p;
    }
};

int main() {
    initStaticList();  // 初始化静态链表

    // 测试用例：两链表相交
    int arrA[] = { 4, 1 };
    int arrB[] = { 5, 0, 1 };
    int arrCommon[] = { 8, 4, 5 };  // 相交部分

    int headA = createList(arrA, 2);
    int headB = createList(arrB, 3);
    int common = createList(arrCommon, 3);

    // 连接链表A与相交部分
    int cur = headA;
    while (next_[cur] != -1) {  // 找到A的最后一个节点
        cur = next_[cur];
    }
    next_[cur] = common;

    // 连接链表B与相交部分
    cur = headB;
    for (int i = 0; i < 2; i++) {
        cur = next_[cur];
    }
    next_[cur] = common;

    cout << "链表A: ";
    printList(headA);  // 4->1->8->4->5->nullptr
    cout << "链表B: ";
    printList(headB);  // 5->0->1->8->4->5->nullptr

    Solution solution;
    int intersection = solution.getIntersectionNode(headA, headB);
    if (intersection != -1) {
        cout << "相交节点值为: " << val[intersection] << endl;  // 应输出8
    }
    else {
        cout << "两链表不相交" << endl;
    }

    return 0;
}
