#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>

using namespace std;

const int N = 1e6 + 10;

int n;
int heap[N];

void up(int child) {
	int parent = child / 2;
	while (parent >= 1 && heap[child] < heap[parent]) {
		swap(heap[child], heap[parent]);
		child = parent;
		parent = child / 2;
	}
}

void down(int parent) {
	int child = parent * 2;
	while (child) {
		if (child <= n) {
			if (child + 1 <= n && heap[child + 1] < heap[child]) child++;

			if (heap[child], heap[parent]) return;
			swap(heap[child], heap[parent]);
			parent = child;
			child = parent * 2;
		}
	}

	void pop() {
		swap(heap[1], heap[n]);
		n--;
		down(1);
	}

	int main() {
		int T;
		cin >> T;
		while (T--) {
			int op;
			cin >> op;
			if (op == 1) {
				int x; cin >> x;
				push(x);
			}
			else if (op == 2) {
				cout << heap[1] << endl;
			}
			else {
				pop();
			}
		}
	}
	return 0;
}