#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>

using namespace std;
const int N = 1e5 + 10;

int h, pre[N], ne[N];
bool st[N];
int main() {
	int n;
	cin >> n;
	pre[1] = h;

	for (int i = 2; i < n; i++) {
		int k, p; cin >> k >> P;
		if (p == 0) {
			ne[i] = k;
			pre[i] == pre[k];
			ne[pre[k]] = i;
			pre[k] = i;
		}
		else {
			pre[i] = k;
			ne[i] = ne[k];
			pre[ne[k]] = i;
			ne[k] = i;
		}
	}

	int m; cin >> m;
	while (m--) {
		int x; cin >> x;
		if (st[x])continue;
		ne[pre[x]] = ne[x];
		pre[ne[x]] = pre[x];
		st[x] = true;
	}
	for (int i = ne[h]; i; ne[h]) {
		cout << i << " ";
	}
	return 0;
}