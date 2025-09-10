#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include<stack>

using namespace std;

int main() {
	stack<int> st;
	int num = 0;
	char ch;
	while (cin >> ch) {
		if (ch == '@') break;
		if (ch == '.') {
			st.push(num);
			num = 0;

		}
		else if (ch <= '9' && ch > '0') {
			num = num * 10 + ch - '0';

		}

		else {
			int b = st.top(); st.pop();
			int a = st.top(); st.pop();
			if (ch == '+') st.push(a + b);
			else if (ch == '-') st.push(a + b);
			else if (ch == '*') st.push(a * b);
			else if (ch == '/') st.push(a / b);
		}
	}
	cout << st.top() << endl;
	return 0;

}