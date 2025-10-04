#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stack>
#include<string>
#include<algorithm>

using namespace std;

class Solution {
public:
    string decodeString(string s) {
        stack<int> numStack;       // 存储数字
        stack<string> strStack;    // 存储字符串
        string currentStr;         // 当前处理的字符串
        int currentNum = 0;        // 当前处理的数字

        for (char c : s) {
            if (isdigit(c)) {
                // 处理多位数（如"123"）
                currentNum = currentNum * 10 + (c - '0');
            }
            else if (c == '[') {
                // 遇到左括号，将当前数字和字符串入栈
                numStack.push(currentNum);
                strStack.push(currentStr);
                // 重置当前数字和字符串
                currentNum = 0;
                currentStr.clear();
            }
            else if (c == ']') {
                // 遇到右括号，开始解码
                int repeatTimes = numStack.top();
                numStack.pop();
                string prevStr = strStack.top();
                strStack.pop();

                // 将当前字符串重复指定次数，并与之前的字符串拼接
                string temp;
                for (int i = 0; i < repeatTimes; i++) {
                    temp += currentStr;
                }
                currentStr = prevStr + temp;
            }
            else {
                // 普通字符直接添加到当前字符串
                currentStr += c;
            }
        }
        return currentStr;
    }
};

int main() {
    Solution solution;
    cout << solution.decodeString("3[a]2[bc]") << endl;      // 输出: aaabcbc
    cout << solution.decodeString("3[a2[c]]") << endl;       // 输出: accaccacc
    cout << solution.decodeString("2[abc]3[cd]ef") << endl;  // 输出: abcabccdcdcdef
    return 0;
}
