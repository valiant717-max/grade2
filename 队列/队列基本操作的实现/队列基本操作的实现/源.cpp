#include<iostream>
using namespace std;
//QueueNode<string> 在“作用”上相当于非模板代码中专门为 string 类型写的 ListNode 结构体
template <typename T>

struct QueueNode {
	T data;
	QueueNode<T>* next;
};

template<typename T>
class Queue {
private:
	QueueNode<T>* front;
	QueueNode<T>* rear;
	int size;

public:
	Queue() {
		front = nullptr;
		rear = nullptr;
		size = 0;
	}
	~Queue() {
		clear();
	}

	void enqueue(T value) {
		QueueNode<T>* newNode = new QueueNode<T>;
		newNode->data = value;
		newNode->next = nullptr;
		// 如果队列为空，新节点既是队头也是队尾
		if (isEmpty()) {
			front = newNode;
			rear = newNode;
		}
		// 否则将新节点添加到队尾
		else {
			rear->next = newNode;
			rear = newNode;
		}
		size++;
	}

	bool dequeue() {
		if (isEmpty()) {
			cout << "队列已空，无法出队!" << endl;
			return false;
		}
		QueueNode<T>* temp = front;
		front = front->next;

		if (front == nullptr) {
			rear = nullptr;
		}
		delete temp;
		size--;
		return true;

	}


T getFront() {
	if (isEmpty()) {
		cout << "队列为空，无元素可获取!" << endl;
		// 返回一个默认值，实际应用中可以考虑抛出异常
		return T();
	}
	return front->data;
	}

bool isEmpty() {
	return front == nullptr;
	}

int getSize() {
	return size;
}

void printQueue() {
	if (isEmpty()) {
		cout << "队列为空!" << endl;
		return;
	}
	QueueNode<T>* current = front;
	cout << "队列元素: ";
	while (current != nullptr) {
		cout << current->data << " ";
		current = current->next;
	}
	cout << endl;
}
};

// 测试队列操作
int main() {
	Queue<int> q;

	// 测试入队操作
	q.enqueue(10);
	q.enqueue(20);
	q.enqueue(30);
	q.printQueue();  // 应输出: 队列元素: 10 20 30
	cout << "队列大小: " << q.getSize() << endl;  // 应输出: 队列大小: 3

	// 测试获取队头元素
	cout << "队头元素: " << q.getFront() << endl;  // 应输出: 队头元素: 10

	// 测试出队操作
	q.dequeue();
	q.printQueue();  // 应输出: 队列元素: 20 30
	cout << "队列大小: " << q.getSize() << endl;  // 应输出: 队列大小: 2

	// 继续出队
	q.dequeue();
	q.dequeue();
	q.printQueue();  // 应输出: 队列为空!
	cout << "队列是否为空: " << (q.isEmpty() ? "是" : "否") << endl;  // 应输出: 队列是否为空: 是

	// 测试对空队列执行出队操作
	q.dequeue();  // 应输出: 队列已空，无法出队!

	return 0;
}