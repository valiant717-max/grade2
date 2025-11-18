#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// 二叉树节点结构：存储运算符或数字
struct Node {
    string val;   // 节点值：运算符（+/-/*/）或数字
    Node* left;   // 左子树
    Node* right;  // 右子树
    Node(string v) : val(v), left(nullptr), right(nullptr) {}
};

// 判断是否为运算符
bool isOp(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// 获取运算符优先级（*//高于+/-）
int getPri(char op) {
    return (op == '*' || op == '/') ? 2 : 1;
}

// 计算两个数的运算结果
double calc(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0) throw "Division by zero!";  // 避免除零错误
        return a / b;
    default: return 0;
    }
}

// 核心函数1：解析表达式，构建运算二叉树（递归处理括号）
Node* buildTree(string& expr, int& pos) {
    Node* root = nullptr;
    Node* curr = nullptr;
    int n = expr.size();

    while (pos < n && expr[pos] != ')') {  // 遇到右括号结束当前子树
        if (isdigit(expr[pos]) || expr[pos] == '.') {  // 解析数字（支持小数）
            string num;
            while (pos < n && (isdigit(expr[pos]) || expr[pos] == '.')) {
                num += expr[pos++];
            }
            Node* numNode = new Node(num);
            if (!curr) {  // 第一个数字作为当前节点（初始左子树）
                curr = numNode;
                root = curr;
            }
            else {  // 后续数字作为右子树
                curr->right = numNode;
                curr = curr->right;
            }
        }
        else if (expr[pos] == '(') {  // 遇到左括号，递归构建子树
            pos++;  // 跳过'('
            Node* subTree = buildTree(expr, pos);
            pos++;  // 跳过')'
            if (!curr) {  // 子树作为初始节点
                curr = subTree;
                root = curr;
            }
            else {  // 子树作为右子树
                curr->right = subTree;
                curr = curr->right;
            }
        }
        else if (isOp(expr[pos])) {  // 遇到运算符，构建父节点
            char op = expr[pos++];
            Node* opNode = new Node(string(1, op));
            opNode->left = curr;  // 之前的结果作为左子树
            curr = opNode;
            root = curr;  // 运算符节点成为新根（保证最后执行的运算符是根）
        }
        else {
            pos++;  // 跳过空格等无效字符
        }
    }
    return root;
}

// 核心函数2：递归遍历二叉树，计算表达式结果
double evaluate(Node* root) {
    if (!root) return 0;
    // 叶子节点：直接转换为数字
    if (!root->left && !root->right) {
        return stod(root->val);
    }
    // 非叶子节点：递归计算左右子树，再执行当前运算符
    double leftVal = evaluate(root->left);
    double rightVal = evaluate(root->right);
    return calc(leftVal, rightVal, root->val[0]);
}

// 工具函数4：释放二叉树内存（避免内存泄漏）
void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// 主函数：测试含括号的表达式计算
int main() {
    string expr;
    cout << "请输入含括号的表达式（例：(2+3)*(4-1)/2）：";
    getline(cin, expr);

    int pos = 0;
    Node* tree = buildTree(expr, pos);  // 构建二叉树
    try {
        double result = evaluate(tree);  // 计算结果
        cout << "表达式结果：" << result << endl;
    }
    catch (const char* msg) {
        cerr << "错误：" << msg << endl;
    }

    freeTree(tree);  // 释放内存
    return 0;
}