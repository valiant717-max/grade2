#include<iostream>
#include<string>

using namespace std;
//节点类型枚举
enum NodeType{ATOM,LIST};
 
struct GNode {
	NodeType type;
	union {
		char atom;
		GNode* sublist;
	};
	GNode* next;
};

using GList = GNode*;

void skipSpace(const string& s, int& i) {
	while (i < s.size() && s[i] == ' ')i++;
}

//创建广义表
GList createGList(const string& s, int& i) {
	skipSpace(s, i);
	if (i >= s.size()||s[i]!='(') return nullptr;
	i++;// 跳过 '('
	GList head = nullptr, tail = nullptr;

	while (i < s.size() && s[i] != ')') {
		skipSpace(s, i);
		if (s[i] == '(') {
			GNode* p = new GNode;
			p->type = LIST;
			p->sublist = createGList(s, i);
			p->next = nullptr;
			if (!head)head = p;
			else tail->next = p;
			tail = p;
		}
		else if (isalpha(s[i])) {
			GNode* p = new GNode;
			p->type = ATOM;
			p->atom = s[i];
			p->next = nullptr;
			i++;
			if (!head) head = p;
			else tail->next = p;
			tail = p;
		}
		else if (s[i] == ',') {
			i++;
		}
		else {
			break;
		}
	}
	if (i < s.size() && s[i] == ')')i++;
	return head;
}

GList initGList(const string& s) {
	int i = 0;
	return createGList(s, i);
}

//求广义表的深度(嵌套层数)
int getDepth(GList gl) {
	if (!gl) return 1;
	int maxDepth = 0;
	GNode* p = gl;
	while (p) {
		if (p->type == LIST) {
			int d = getDepth(p->sublist);
			if (d > maxDepth)maxDepth = d;
		}
		p = p->next;
	}
	return maxDepth + 1;
}

//计算广义表的长度(顶层元素个数)
int getLength(GList gl) {
	int len = 0;
	GNode* p = gl;
	while (p) {
		len++;
		p = p->next;
	}
	return len;
}

//取表头和表尾元素
GNode* getHead(GList gl) {
	if (!gl) {
		return nullptr;
	}
	return gl;
}
GNode* getTail(GList gl) {
	if (!gl) {
		return nullptr;
	}
	return gl->next;
}

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
			printGList(p->sublist);
		}
		if (p->next)cout << ",";
		p = p->next;
	}
	cout << ")";
}

void destroyGList(GList& gl) {
	GNode* p = gl;
	while (p) {
		GNode* q = p->next;
		if (p->type == LIST) {
			destroyGList(p->sublist);
		}
		delete p;
		p = q;
	}
	gl = nullptr;
}

int main() {
	string s = "(a,(b,(c),d),e)";
	GList gl = initGList(s);

	printGList(gl);
	cout << endl;
	
	cout << "长度: " << getLength(gl) << endl;  
	cout << "深度: " << getDepth(gl) << endl;

	cout << "表头: ";
	GNode* head = getHead(gl);
	if (head) {  // 先判断表头是否非空
		if (head->type == ATOM) {
			cout << head->atom;  // 原子节点：直接打印值
		}
		else {
			printGList(head->sublist);  // 表节点：递归打印子表
		}
	}
	cout << endl;

	cout << "表尾: ";
	GList tail = getTail(gl);
	printGList(tail);  // ((b,(c),d),e)
	cout << endl;

	destroyGList(gl);
	return 0;
}