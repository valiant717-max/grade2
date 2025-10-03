#define _CRT_SECURE_NO_WARNINGS 1
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

// 初始顺序表函数，构造一个空的顺序表
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
SqList MergeSortedList(SqList LA, SqList LB) {
    // 将两个有序顺序表LA和LB合并成一个新的有序顺序表LC
    // 要求：LA和LB都是非递减有序的，合并后的LC也应该是非递减有序的
    // 返回合并后的结果顺序表

    // 你的代码在这里
    SqList LC;
    InitList(LC);

    int i = 0, j = 0;
	while (i < LA.length && j < LB.length) {
		if (LA.data[i] <= LB.data[j]) {
			LC.data[LC.length++] = LA.data[i++];
		}
		else {
			LC.data[LC.length++] = LB.data[j++];
		}
	}   
    while (i < LA.length) {

        LC.data[LC.length++] = LA.data[i++];
    }
    while(j<LB.length) {
        LC.data[LC.length++] = LB.data[j++];
    }
    return LC;
}

// 简单的测试主函数，方便你调试
int main() {
    SqList LA, LB, LC;
    InitList(LA);
    InitList(LB);

    // 测试用例1：正常合并
    cout << "=== 测试用例1：正常合并 ===" << endl;
    LA.data[0] = 1; LA.data[1] = 3; LA.data[2] = 5;
    LA.length = 3;
    LB.data[0] = 2; LB.data[1] = 4; LB.data[2] = 6;
    LB.length = 3;

    cout << "顺序表A: ";
    PrintList(LA);
    cout << "，长度: " << LA.length << endl;
    cout << "顺序表B: ";
    PrintList(LB);
    cout << "，长度: " << LB.length << endl;

    LC = MergeSortedList(LA, LB);
    cout << "合并结果: ";
    PrintList(LC);
    cout << "，长度: " << LC.length << endl << endl;

    // 测试用例2：一个为空
    cout << "=== 测试用例2：一个为空 ===" << endl;
    SqList LA2, LB2, LC2;
    InitList(LA2);
    InitList(LB2);

    LA2.data[0] = 1; LA2.data[1] = 3;
    LA2.length = 2;
    LB2.length = 0; // 空顺序表

    cout << "顺序表A: ";
    PrintList(LA2);
    cout << "，长度: " << LA2.length << endl;
    cout << "顺序表B: ";
    PrintList(LB2);
    cout << "，长度: " << LB2.length << endl;

    LC2 = MergeSortedList(LA2, LB2);
    cout << "合并结果: ";
    PrintList(LC2);
    cout << "，长度: " << LC2.length << endl;

    return 0;
}