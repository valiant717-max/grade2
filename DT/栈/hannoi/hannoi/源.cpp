#include <iostream>
#include <stack>
#include <tuple>
using namespace std;

// 打印移动步骤（直接使用字符表示塔）
void printMove(int disk, char from, char to) {
    cout << "移动圆盘 " << disk << " 从 " << from << " 到 " << to << endl;
}

// 使用栈和字符类型解决汉诺塔问题
void hanoi(int n) {
    // 栈中存储的元组: (圆盘数量, 源塔, 目标塔, 辅助塔, 是否已处理)
    // 这里直接用char类型表示塔（'A'、'B'、'C'）
    stack<tuple<int, char, char, char, bool>> stk;

    // 初始状态：将n个圆盘从'A'移到'C'，'B'作为辅助
    stk.push({ n, 'A', 'C', 'B', false });

    while (!stk.empty()) {
        auto [num, from, to, aux, processed] = stk.top();
        stk.pop();

        if (!processed) {
            if (num == 1) {
                // 只有一个圆盘时直接移动
                printMove(num, from, to);
            }
            else {
                // 将当前任务标记为已处理后重新入栈
                stk.push({ num, from, to, aux, true });

                // 入栈子任务：将n-1个圆盘从源塔移到辅助塔
                stk.push({ num - 1, from, aux, to, false });

                // 入栈子任务：将第n个圆盘从源塔移到目标塔
                stk.push({ 1, from, to, aux, false });

                // 入栈子任务：将n-1个圆盘从辅助塔移到目标塔
                stk.push({ num - 1, aux, to, from, false });
            }
        }
        // 已处理的任务不需要额外操作
    }
}

int main() {
    int n;
    cout << "请输入汉诺塔的圆盘数量: ";
    cin >> n;

    if (n <= 0) {
        cout << "请输入正整数" << endl;
        return 1;
    }

    cout << "汉诺塔的移动步骤如下:" << endl;
    hanoi(n);

    return 0;
}
