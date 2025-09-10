#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stack>

using namespace std;
const int N = 110;
bool st[N];

int main() {
	string s;
	cin >> s;
	int n = s.size();
	stack<int> stk;
	string ret;
	for (int i = 0; i < n; i++)
	{
		if (s[i] == '(' || s[i] == '[') {
			stk.push(i);
		}
		else {
			if (stk.empty())
				continue;
			char ch = s[stk.top()];
			if ((ch == '(' && s[i] == ')') || (ch == '[' && s[i] == ']')) {
				st[stk.top()] = true;
				st[i] = true;
				stk.pop();
			}
		}
	}

	for (int i = 0; i < n; i++) {
		char ch = s[i];
		if (st[i]) ret += ch;
		else {
			if (ch == '(') {
				ret += ch;
				ret += ')';
			}
			else if (ch == ')') {
				ret += '(';
				ret += ch;
			}
			else if (ch == '[') {
				ret += ch;
				ret += ']';
			}
			else if (ch == ']') {
				ret += '[';
				ret += ch;
			}
		}
			cout << ret << endl;
			return 0;
		}