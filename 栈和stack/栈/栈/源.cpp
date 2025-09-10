#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

using namespace std;

typedef unsigned long long LL;
const int N = 1e6 + 10;

int top;
LL stk[N];

int main() {
	int T; cin >> T;
	while (T--) {
		top = 0;
		int n;
		cin >> n;
		while (n--) {
			string op;
			cin >> op;
			if (op == "push") {
				LL x;
				cin >> x;
				stk[++top] = x;
			}
			else if (op == "pop"){
				if (top == 0) cout << "Empty" << endl;
			}
			else if (op == "query") {
				if (top == 0) cout << "Auguei!" << endl;
				else cout << stk[top] << endl;
			}
			else {
				cout << top << endl;
			}
		}
	}
	return 0;
}