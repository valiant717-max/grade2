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

// TODO: 实现这个函数
int deleteMin(SqList& L) {
    // 如果顺序表为空，应打印错误信息到终端并返回错误码-1
    if (L.length == 0) {
        cout << "顺序表为空，无法删除最小值" << endl;
        return -1;
    }
    // 删除最小值元素，用最后一个元素填补空位
    // 返回被删除的最小值
    int min = 0;
    for (int i = 1; i < L.length; i++) {
        if (L.data[i] < L.data[min]) {
            min = i;
        }
    }
    int minValue = L.data[min];
    L.data[min] = L.data[L.length - 1];
    L.length--;
    return minValue;
    // 你的代码在这里

   // 实际的实现应该覆盖这个返回值
   //return 0; 
}

// 简单的测试主函数，方便你调试
int main() {
    SqList L1, L2, L3;
    InitList(L1);
    InitList(L2);
    InitList(L3);

    // 测试用例1：正常删除最小值
    cout << "=== 测试用例1：正常删除最小值 ===" << endl;
    L1.data[0] = 3; L1.data[1] = 1; L1.data[2] = 4; L1.data[3] = 2; L1.data[4] = 5;
    L1.length = 5;

    cout << "原始顺序表: ";
    PrintList(L1);
    cout << "，长度: " << L1.length << endl;

    int min_val1 = deleteMin(L1);
    cout << "删除的最小值: " << min_val1 << endl;
    cout << "结果顺序表: ";
    PrintList(L1);
    cout << "，长度: " << L1.length << endl << endl;

    // 测试用例2：单元素顺序表
    cout << "=== 测试用例2：单元素顺序表 ===" << endl;
    L2.data[0] = 7;
    L2.length = 1;

    cout << "原始顺序表: ";
    PrintList(L2);
    cout << "，长度: " << L2.length << endl;

    int min_val2 = deleteMin(L2);
    cout << "删除的最小值: " << min_val2 << endl;
    cout << "结果顺序表: ";
    PrintList(L2);
    cout << "，长度: " << L2.length << endl << endl;

    // 测试用例3：空顺序表处理
    cout << "=== 测试用例3：空顺序表处理 ===" << endl;
    L3.length = 0; // 空顺序表

    cout << "原始顺序表: ";
    PrintList(L3);
    cout << "，长度: " << L3.length << endl;

    int min_val3 = deleteMin(L3);
    cout << "尝试删除最小值，返回码: " << min_val3 << endl;
    cout << "结果顺序表: ";
    PrintList(L3);
    cout << "，长度: " << L3.length << endl;

    return 0;
}