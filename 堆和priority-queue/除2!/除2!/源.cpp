#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<queue>

using namespace std;

typedef long long LL;

int n, k;

priority_queue<int> heap;

int main() {
	cin >> n >> k;
	LL sum = 0;
	for (int i = 0; i <= n; i++) {
		int x;
		cin >> x;
		sum += x;
		if (x % 2 == 0) heap.push(x);
	}

	while (heap.size() && k--) {
		int t = heap.top();

		sum -= t;
		if (t % 2 == 0) heap.push(t / 2);
		heap.pop();
		sum -= t;
		if (t % 2 == 0) heap.push(t);
	}

	cout << sum << endl;

	return 0;
}