#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

// 判断运算符优先级：op1优先级 <= op2 则返回true
//与左括号相关的比较返回true，从而触发入栈操作,op1不可能是）
bool priority(char op1, char op2) {
    if ((op1 == '+' || op1 == '-') && (op2 == '*' || op2 == '/')) return true;
    if (op2 == ')') return false;
    if (op1 == '(' || op2 == '(') return true; // 左括号优先级最低
  
    return false;
}

// 执行运算：a op b
double calculate(double a, char op, double b) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
// 0在计算机存储和运算过程中可能会是一个非常接近 0 但不等于 0 的极小值，所以不能简单地用b == 0 来判断除数是否为 0
// 使用fabs(b) < 1e-6（0.000001）这样的条件判断检查除数b的绝对值是否足够小，当它小于一个极小值时，就认为除数近似为 0
        if (fabs(b) < 1e-6) {
            cerr << "错误：除数不能为0" << endl;
            exit(1);
        }
        return a / b;
    default: return 0;
    }
}

// 中缀表达式求值
double evaluateInfix(const string& expr) {
    stack<char> optr;    // 操作符栈
    stack<double> opnd;  // 操作数栈
    optr.push('=');      // 栈底压入'='作为结束标志
    int i = 0;
    int n = expr.size();

    while (!optr.empty()) {
        char ch = (i < n) ? expr[i] : '='; // 到达末尾时用'='填充
//允许 “小数点开头且后续有数字” 的合法小数（如 .123）
// 同时拒绝 “小数点后无数字” 的非法格式（如 . 或 3.）
        if (isdigit(ch) || (ch == '.' && i + 1 < n && isdigit(expr[i + 1]))) {
            // 读取数字（支持小数）
            double num = 0.0;
            int decimal = 0;
            while (i < n && (isdigit(expr[i]) || expr[i] == '.')) {
                if (expr[i] == '.') {
                    decimal = 1;
                }
                else {
                    if (decimal == 0) {
                        num = num * 10 + (expr[i] - '0');
                    }
                    else {
                        num += (expr[i] - '0') * pow(10, -decimal);
                        decimal++;
                    }
                }
                i++;
            }
            opnd.push(num);
        }

        else {
            // 处理运算符
            char topOp = optr.top();
            if (priority(topOp, ch)) {
                // topOp优先级低，压入新运算符
                optr.push(ch);
                i++;
            }
            else if (topOp == '(' && ch == ')') {
                // 括号匹配，弹出左括号
                optr.pop();
                i++;
            }
            else {
                // 计算topOp对应的运算
                if (opnd.size() < 2) {
                    cerr << "错误：表达式格式非法" << endl;
                    exit(1);
                }
                double b = opnd.top(); opnd.pop();
                double a = opnd.top(); opnd.pop();
                double res = calculate(a, topOp, b);
                opnd.push(res);
                optr.pop();
            }

            // 结束条件：栈顶是'='且当前字符是'='
            if (optr.top() == '=' && ch == '=') break;
        }
    }

    return opnd.top();
}

int main() {
    string expr;
    cout << "请输入中缀表达式（支持+、-、*、/和括号，以回车结束）：" << endl;
    getline(cin, expr);
    try {
        double result = evaluateInfix(expr);
        cout << "计算结果：" << result << endl;
    }
    catch (...) {
        cout << "表达式求值失败" << endl;
    }
    return 0;
}