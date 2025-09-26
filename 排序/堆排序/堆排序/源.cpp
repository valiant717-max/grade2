#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>

using namespace std;

const int N = 1e5 + 10;

int n;
int a[N];

void down(int parent, int len) {
	int child = parent * 2;
	while (child <= len) {
		if (child <= len) {

			if (child + 1 <= len && a[child + 1] > a[child]) child++;
			if (a[parent] >= a[child])return;
			swap(a[parent], a[child]);
			parent = child;
			child = parent * 2;
		}

	}
}
	void heap_sort() {
		for (int i = n / 2; i >= 1; i--) {
			down(i, n);
		}
		for (int i = n; i > 1; i--) {
			swap(a[1], a[i]);
			down(1, i - 1);
		}
	}

	int main() {
		cin >> n;
		for (int i = 1; i <= n; i++)cin >> a[i];
		heap_sort();
		for (int i = 1; i <= n; i++)cout << a[i] << "";
		return 0;
	}