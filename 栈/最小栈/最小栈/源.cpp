#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stack>

using namespace std;

class MinStack {
private:
    stack<int> mainStack;  // 主栈：存储所有元素
    stack<int> minStack;   // 辅助栈：存储当前最小值

public:
    // 构造函数：初始化栈
    MinStack() {}

    // 入栈操作
    void push(int val) {
        mainStack.push(val);
        // 辅助栈为空或当前值小于等于辅助栈顶（确保最小值始终在栈顶）
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val);
        }
    }

    // 出栈操作
    void pop() {
        // 如果弹出的是当前最小值，辅助栈也需要弹出
        if (mainStack.top() == minStack.top()) {
            minStack.pop();
        }
        mainStack.pop();
    }

    // 获取栈顶元素
    int top() {
        return mainStack.top();
    }

    // 获取当前最小值（O(1)时间复杂度）
    int getMin() {
        return minStack.top();
    }
};

int main() {
    MinStack* obj = new MinStack();
    obj->push(-2);
    obj->push(0);
    obj->push(-3);
    cout << obj->getMin() << endl;  // 输出 -3
    obj->pop();
    cout << obj->top() << endl;     // 输出 0
    cout << obj->getMin() << endl;  // 输出 -2
}