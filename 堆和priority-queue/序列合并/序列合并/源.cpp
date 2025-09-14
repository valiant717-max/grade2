#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<queue>

using namespace std;

const int N = 1e5 + 10;

int n;
int a[N], b[N];
 
struct node {
	int sum;
	int i, j;

	bool operator<(const node& x) const {
		return sum > x.sum;
	}
};

priority_queue<node> heap;

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	// 将 a[i] + b[1] (1 <= i <= n) 放入小根堆	
	for (int i = 1; i <= n; i++) {
		heap.push({ a[i] + b[1], i, 1 });
	}

	for (int k = 1; k <= n; k++) {
		node t = heap.top();
		int sum = t.sum, i = t.i, j = t.j;

		cout << sum << " ";
		if (j + 1 <= n) heap.push({ a[i] + b[j + 1],i,j + 1 });
	}
	return 0;
}

