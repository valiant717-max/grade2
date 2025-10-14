#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class CircularQueue {
private:
    T* data;         // 存储队列元素的数组
    int front;       // 队头指针，指向队头元素
    int rear;        // 队尾指针，指向队尾元素的下一个位置
    int capacity;    // 队列的容量
    int size;        // 当前队列中的元素个数

public:
    // 构造函数，初始化队列
    CircularQueue(int cap) : capacity(cap), front(0), rear(0), size(0) {
        if (cap <= 0) {
            throw invalid_argument("队列容量必须为正数");
        }
        data = new T[capacity];
    }

    // 析构函数，释放内存
    ~CircularQueue() {
        delete[] data;
    }

    // 入队操作
    void enqueue(T value) {
        if (isFull()) {
            throw runtime_error("队列已满，无法入队");
        }
        data[rear] = value;
        rear = (rear + 1) % capacity;  // 循环移动队尾指针
        size++;
    }

    // 出队操作
    T dequeue() {
        if (isEmpty()) {
            throw runtime_error("队列为空，无法出队");
        }
        T value = data[front];
        front = (front + 1) % capacity;  // 循环移动队头指针
        size--;
        return value;
    }

    // 获取队头元素
    T getFront() const {
        if (isEmpty()) {
            throw runtime_error("队列为空，无队头元素");
        }
        return data[front];
    }

    // 检查队列是否为空
    bool isEmpty() const {
        return size == 0;
    }

    // 检查队列是否已满
    bool isFull() const {
        return size == capacity;
    }

    // 获取队列当前元素个数
    int getSize() const {
        return size;
    }

    // 获取队列容量
    int getCapacity() const {
        return capacity;
    }

    // 打印队列元素
    void printQueue() const {
        if (isEmpty()) {
            cout << "队列为空" << endl;
            return;
        }
        cout << "队列元素: ";
        int index = front;
        for (int i = 0; i < size; i++) {
            cout << data[index] << " ";
            index = (index + 1) % capacity;
        }
        cout << endl;
    }
};

// 测试函数
int main() {
    try {
        // 创建容量为5的循环队列
        CircularQueue<int> queue(5);

        // 入队操作
        queue.enqueue(10);
        queue.enqueue(20);
        queue.enqueue(30);
        queue.printQueue();  // 输出: 队列元素: 10 20 30

        // 查看队头元素
        cout << "队头元素: " << queue.getFront() << endl;  // 输出: 10

        // 出队操作
        cout << "出队元素: " << queue.dequeue() << endl;  // 输出: 10
        queue.printQueue();  // 输出: 队列元素: 20 30

        // 继续入队
        queue.enqueue(40);
        queue.enqueue(50);
        queue.enqueue(60);
        queue.printQueue();  // 输出: 队列元素: 20 30 40 50 60

        // 尝试入队到满队列
        // queue.enqueue(70);  // 会抛出异常

        // 查看队列信息
        cout << "队列大小: " << queue.getSize() << endl;      // 输出: 5
        cout << "队列容量: " << queue.getCapacity() << endl;  // 输出: 5

        // 继续出队
        queue.dequeue();
        queue.dequeue();
        queue.printQueue();  // 输出: 队列元素: 40 50 60

        // 再入队一个元素
        queue.enqueue(70);
        queue.printQueue();  // 输出: 队列元素: 40 50 60 70
    }
    catch (const exception& e) {
        cout << "错误: " << e.what() << endl;
    }

    return 0;
}
