#include<iostream>
using namespace std;

struct ListNode {
	int data;
	ListNode* next;
};

struct ListStack {
	ListNode* top;
};

void InitListStack(ListStack& stack) {
	stack.top == nullptr;
}

bool IsListEmpty(ListStack& stack) {
	return stack.top == nullptr;
}
//important
bool ListPush(ListStack& stack, int value) {
	ListNode* newNode = new ListNode;
	newNode->data = value;
	newNode->next = stack.top;
	stack.top = newNode;
	return true;
}

bool ListPop(ListStack& stack) {
	if (IsListEmpty(stack)) {
		cout << "栈空！出栈失败\n";
		return false;
	}
	ListNode* temp = stack.top;
	stack.top = stack.top->next;
	delete temp;
	temp = nullptr;
	return true;
}

bool ListGetTop(ListStack& stack, int& topVal) {
	if (IsListEmpty(stack)) {
		cout << "栈空！无栈顶元素\n";
		return false;
	}
	topVal = stack.top->data;  // 栈顶节点的data即栈顶元素
	return true;
}

void DestroyListStack(ListStack& stack) {
	ListNode* temp = nullptr;
	while (stack.top ) {
		temp = stack.top;
		stack.top = stack.top->next;
		delete temp;
	}
	temp = nullptr;
}

int main() {
	ListStack stack;
	InitListStack(stack);
	int topVal;

	ListPush(stack, 100);
	ListPush(stack, 200);
	ListPush(stack, 300);
	cout << "链栈入栈3个元素后：\n";
	ListGetTop(stack, topVal);
	cout << "当前栈顶：" << topVal << "\n";  // 输出300
	// 测试出栈
	ListPop(stack);
	cout << "链栈出栈1次后：\n";
	ListGetTop(stack, topVal);
	cout << "当前栈顶：" << topVal << "\n";  // 输出200

	// 销毁链栈
	DestroyListStack(stack);
	cout << "销毁后栈是否空：" << (IsListEmpty(stack) ? "是" : "否") << "\n";  // 输出是
	return 0;
}