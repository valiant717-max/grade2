#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

#define MaxSize 50
typedef int ElemType;
typedef int Status;

// 顺序表结构定义
typedef struct {
    ElemType data[MaxSize]; // 顺序表元素
    int length;             // 顺序表当前长度
} SqList;

// 初始化顺序表函数，构造一个空的顺序表
Status InitList(SqList& L) {
    memset(L.data, 0, sizeof(L.data)); // 初始化数据为0
    L.length = 0;                      // 初始化长度为0
    return 0;
}

// 打印顺序表
void PrintList(SqList L) {
    cout << "[";
    for (int i = 0; i < L.length; i++) {
        cout << L.data[i];
        if (i < L.length - 1) cout << ", ";
    }
    cout << "]";
}

Status ListInsert(SqList& L, int i, ElemType e) {
    // 如果i不在合理范围或顺序表已满，应打印错误信息到终端并返回错误码-1
    if (i<1 || i>L.length + 1 || i > MaxSize) {
        cout << "插入位置不合法" << endl;
        return -1;
    }
    L.length++;
    // 在第i个位置插入元素e（注意：i从1开始计数）
    for (int j = L.length; j >= i; j--)
        L.data[j] = L.data[j - 1];
    L.data[i - 1] = e;
    // 你的代码在这里

    // 实际的实现应该覆盖这个返回值
    return 0;
}
// 简单的测试主函数，方便你调试
int main() {
    SqList L1, L2, L3, L4;
    InitList(L1);
    InitList(L2);
    InitList(L3);
    InitList(L4);

    // 测试用例1：中间插入
    cout << "=== 测试用例1：中间插入 ===" << endl;
    L1.data[0] = 1; L1.data[1] = 3; L1.data[2] = 5;
    L1.length = 3;

    cout << "原始顺序表: ";
    PrintList(L1);
    cout << "，长度: " << L1.length << endl;
    cout << "插入元素2到位置2（第2个位置）" << endl;

    Status s1 = ListInsert(L1, 2, 2);
    cout << "插入状态码: " << s1 << endl;
    cout << "插入后顺序表: ";
    PrintList(L1);
    cout << "，长度: " << L1.length << endl << endl;

    // 测试用例2：末尾插入
    cout << "=== 测试用例2：末尾插入 ===" << endl;
    L2.data[0] = 1; L2.data[1] = 2;
    L2.length = 2;

    cout << "原始顺序表: ";
    PrintList(L2);
    cout << "，长度: " << L2.length << endl;
    cout << "插入元素3到位置3（末尾位置）" << endl;

    Status s2 = ListInsert(L2, 3, 3);
    cout << "插入状态码: " << s2 << endl;
    cout << "插入后顺序表: ";
    PrintList(L2);
    cout << "，长度: " << L2.length << endl << endl;

    // 测试用例3：无效位置处理
    cout << "=== 测试用例3：无效位置处理 ===" << endl;
    L3.data[0] = 1; L3.data[1] = 2;
    L3.length = 2;

    cout << "原始顺序表: ";
    PrintList(L3);
    cout << "，长度: " << L3.length << endl;
    cout << "尝试插入元素5到位置10" << endl;

    Status s3 = ListInsert(L3, 10, 5);
    cout << "插入状态码: " << s3 << endl;
    cout << "结果顺序表: ";
    PrintList(L3);
    cout << "，长度: " << L3.length << endl;

    return 0;
}