#include<iostream>
using namespace std;

struct ArrayStack {
	int* data;
	int top;
	int maxSize;
};
 
void InitArrayStack(ArrayStack& stack,int capacity) {
	stack.maxSize = capacity;
	stack.data = new int[stack.maxSize];
	stack.top = -1;
}

bool IsEmpty(ArrayStack& stack) {
	return stack.top = -1;
}

bool IsFull(ArrayStack& stack) {
	return stack.top == stack.maxSize - 1;
}

bool Push(ArrayStack& stack, int value) {
	if (IsFull(stack)) {
		cout << "栈满！入栈失败（元素：" << value << "）\n";
		return false;
	}
	stack.top++;
	stack.data[stack.top] = value;
	return true;
}

bool Pop(ArrayStack& stack) {
	if (IsEmpty(stack)) {
		cout << "栈空！出栈失败\n";
		return false;
	}
	stack.top--;
	return true;
}
bool GetTop(ArrayStack& stack, int& topVal) {
	if (IsEmpty(stack)) {
		cout << "栈空！无栈顶元素\n";
		return false;
	}
	topVal = stack.data[stack.top];  // 直接读取栈顶位置的元素
	return true;
}

void DestroyStack(ArrayStack& stack) {
	delete[]stack.data;
	stack.data = nullptr;
	stack.top = -1;
	stack.maxSize = 0;
}

int main() {
	ArrayStack stack;
	InitArrayStack(stack, 5);  // 初始化容量为5的栈
	int topVal;
	
		// 测试入栈
		Push(stack, 10);
		Push(stack, 20);
		Push(stack, 30);
		cout << "入栈3个元素后：\n";
		GetTop(stack, topVal);
		cout << "当前栈顶：" << topVal << "\n";  // 输出30

		// 测试出栈
		Pop(stack);
		cout << "出栈1次后：\n";
		GetTop(stack, topVal);
		cout << "当前栈顶：" << topVal << "\n";  // 输出20

		// 测试栈满
		Push(stack, 40);
		Push(stack, 50);
		Push(stack, 60);  // 容量5，第6个元素入栈失败
		cout << "栈是否满：" << (IsFull(stack) ? "是" : "否") << "\n";  // 输出是

		// 销毁栈
		DestroyStack(stack);
		return 0;
}




