#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>	
#include<stack>
#include<string>	
using namespace std;
class Solution {
public:
	bool isValid(string s) {
		stack<int>st;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
				st.push(s[i]);
			}
			else {
				if (st.empty()) return false;
				if (s[i] == ')' && st.top() != '(') return false;
				if (s[i] == '}' && st.top() != '{') return false;
				if (s[i] == ']' && st.top() != '[') return false;
				st.pop();
			}
		}
			return st.empty();
		}
		};
int main() {
	string s;
	getline(cin, s);
	Solution solver;
	bool result = solver.isValid(s);
	cout << result;
	return 0;
}