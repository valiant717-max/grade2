#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

const int N = 1e5 + 10;
using namespace std;
int n;
int a[N];
void insert_sort() {
	for (int i = 2; i <= n; i++) {
		int key = a[i];
		int j = i - 1;
		while (j >= 1 && a[j] > key) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}
	int main() {
		cin >> n;
		for (int i = 1; i <= n; i++)cin >> a[i];
		insert_sort();
		for (int i = 1; i <= n; i++) cout << a[i] << " ";
		return 0;
	} 

