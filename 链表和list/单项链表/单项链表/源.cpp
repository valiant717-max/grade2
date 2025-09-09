 #define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

using namespace std;

const int N = 1e5 + 10, M = 1e6 + 10;

int h, id, e[N], ne[N];
int mp[N];

int main() {
	int q;
	cin >> q;
	id++;
	e[id] = -1;
	 
	while (q--) {
		int op, x, y;
		cin >> op >> x;
		int p = mp[x];
		if (op == 1) {
			cin >> y;
			id++;
			e[id] = y;
			ne[id] = ne[p];

			mp[y] = id;
		}
		else if (op == 2) {
			cout << e[ne[p]] << end;;

		}
		else {
			ne[p] = ne[ne[p]];
		}
	}
	return 0;
}