#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<queue>

using namespace std;

int n, m, k;

priority_queue<int> heap;

int main() {
	cin >> n >> m >> k;

	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		heap.push(x);
		if (heap.size() > k)heap.pop();
	}

	while (m--) {
		int op; cin >> op;
		if (op == 1) {
			int x;
			cin >> x;
			heap.push(x);
			if (heap.size() > k) heap.pop();
		}
		else if (op == 2) {
			if (heap.size() == k) cout << heap..top() << endl;
			else cout << -1 << endl;
		}
	}
	return 0;
}