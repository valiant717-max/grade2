#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

using namespace std;

const int N = 1e5 + 10;

int q[N], h, t;

int main() {
	int n;
	cin >> n;
	while (n--) {
		int op, x;
		cin >> op;
		if (op == 1) {
			cin >> x;
			q[t--] = x;
		}
		else if (op == 2) {
			if (h == t) cout << "ERR_CANNOT_POP" << endl;
			else cout << q[h] << endl;
		}
		else {
			cout << t - h << endl;
		}
		
	}
	return 0;
}