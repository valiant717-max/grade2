#include<iostream>
#include<string>

using namespace std;

// 节点类型枚举
enum NodeType { ATOM, LIST };

struct GNode {
	NodeType type;
	union {
		char atom;          // 原子节点的值
		GNode* sublist;     // 子表节点的指针
	};
	GNode* next;           // 指向下一个节点
};

using GList = GNode*;     // 广义表类型（指向头节点的指针）

// 跳过字符串中的空格
void skipSpace(const string& s, int& i) {
	while (i < s.size() && s[i] == ' ') i++;
}

// 创建广义表
GList createGList(const string& s, int& i) {
	skipSpace(s, i);
	if (i >= s.size() || s[i] != '(') return nullptr;
	i++;  // 跳过 '('

	GList head = nullptr, tail = nullptr;

	while (i < s.size() && s[i] != ')') {
		skipSpace(s, i);
		if (s[i] == '(') {  // 遇到子表，递归创建
			GNode* p = new GNode;
			p->type = LIST;
			p->sublist = createGList(s, i);  // 递归创建子表
			p->next = nullptr;
			if (!head) head = p;
			else tail->next = p;
			tail = p;
		}
		else if (isalpha(s[i])) {  // 遇到原子节点
			GNode* p = new GNode;
			p->type = ATOM;
			p->atom = s[i];
			p->next = nullptr;
			i++;
			if (!head) head = p;
			else tail->next = p;
			tail = p;
		}
		else if (s[i] == ',') {  // 跳过逗号
			i++;
		}
		else {  // 遇到非法字符，终止
			break;
		}
	}
	if (i < s.size() && s[i] == ')') i++;  // 跳过 ')'
	return head;
}

// 初始化广义表
GList initGList(const string& s) {
	int i = 0;
	return createGList(s, i);
}

// 深拷贝广义表（核心：递归复制所有节点）
GList copyGList(GList original) {
	if (!original) return nullptr;  // 原表为空，返回空

	GList newHead = nullptr, newTail = nullptr;
	GNode* p = original;

	while (p) {  // 遍历原表的每个节点
		GNode* newNode = new GNode;  // 创建新节点
		newNode->type = p->type;     // 复制节点类型

		if (p->type == ATOM) {       // 原子节点：直接复制值
			newNode->atom = p->atom;
		}
		else {                        // 子表节点：递归复制子表
			newNode->sublist = copyGList(p->sublist);
		}
		newNode->next = nullptr;      // 新节点的next先置空

		// 链接到新表中
		if (!newHead) newHead = newNode;
		else newTail->next = newNode;
		newTail = newNode;

		p = p->next;  // 移动到原表的下一个节点
	}
	return newHead;
}

void destroyGList(GList& gl);

// 广义表赋值操作（先释放目标表，再深拷贝原表）
void assignGList(GList& dest, GList src) {
	// 1. 先销毁目标表原有的内存（避免内存泄漏）
	destroyGList(dest);
	// 2. 深拷贝源表到目标表
	dest = copyGList(src);
}

// 求广义表的深度（嵌套层数）
int getDepth(GList gl) {
	if (!gl) return 1;  // 空表深度为1
	int maxDepth = 0;
	GNode* p = gl;
	while (p) {
		if (p->type == LIST) {  // 子表的深度需要递归计算
			int d = getDepth(p->sublist);
			if (d > maxDepth) maxDepth = d;
		}
		p = p->next;
	}
	return maxDepth + 1;  // 顶层加1层
}

// 求广义表的长度（顶层元素个数）
int getLength(GList gl) {
	int len = 0;
	GNode* p = gl;
	while (p) {
		len++;
		p = p->next;
	}
	return len;
}

// 取表头（第一个元素）
GNode* getHead(GList gl) {
	return gl;  // 表头是第一个节点
}

// 取表尾（除第一个元素外的所有元素）
GNode* getTail(GList gl) {
	if (!gl) return nullptr;
	return gl->next;  // 表尾是第一个节点的next
}

// 打印广义表
void printGList(GList gl) {
	if (!gl) {
		cout << "()";
		return;
	}
	cout << "(";
	GNode* p = gl;
	while (p) {
		if (p->type == ATOM) {
			cout << p->atom;
		}
		else {
			printGList(p->sublist);  // 递归打印子表
		}
		if (p->next) cout << ",";
		p = p->next;
	}
	cout << ")";
}

// 销毁广义表（释放所有节点内存）
void destroyGList(GList& gl) {
	GNode* p = gl;
	while (p) {
		GNode* q = p->next;  // 先保存下一个节点
		if (p->type == LIST) {
			destroyGList(p->sublist);  // 递归销毁子表
		}
		delete p;  // 释放当前节点
		p = q;
	}
	gl = nullptr;  // 置空避免野指针
}

// 测试主函数
int main() {
	// 1. 创建原广义表 A: (a,(b,(c),d),e)
	string s = "(a,(b,(c),d),e)";
	GList A = initGList(s);
	cout << "原广义表 A: ";
	printGList(A);
	cout << "\nA的长度: " << getLength(A) << ", 深度: " << getDepth(A) << endl;

	// 2. 赋值：将 A 赋值给 B
	GList B = nullptr;
	assignGList(B, A);  // 核心赋值操作
	cout << "\n赋值后广义表 B: ";
	printGList(B);
	cout << "\nB的长度: " << getLength(B) << ", 深度: " << getDepth(B) << endl;

	// 3. 验证独立性：修改 A 后，B 应不受影响
	// 示例：修改 A 的第一个原子节点为 'x'
	if (A && A->type == ATOM) {
		A->atom = 'x';
	}
	cout << "\n修改 A 后，A: ";
	printGList(A);  // 输出 (x,(b,(c),d),e)
	cout << "\n修改 A 后，B: ";
	printGList(B);  // 仍输出 (a,(b,(c),d),e)，证明独立

	// 4. 释放内存
	destroyGList(A);
	destroyGList(B);
	return 0;
}