#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<ctime>
using namespace std;

const int N = 1e5 + 10;
int n;
int a[N];
int get_random(int left, int right) {
	return a[rand() % (right - left + 1) + left];

}


void quick_sort(int left, int right) {
	if (left > right) return;
	int p = get_random(left, right);
	int l = left - 1, i = left, r = right + 1;
	while (i < r) {
		if (a[i] < p) swap(a[++l], a[i++]);
		else if (a[i] > p) swap(a[--r], a[i]);
		else i++;
	}
	quick_sort(left, l);
	quick_sort(r, right);
}	
int main() {
	srand(time(0));
	cin >> n;
	for (int i = 1; i <= n; i++) {
		quick_sort(1, n);
	}
		for (int i = 1; i <= n; i++) {
			cout << a[i] << "";
		}
		return 0;
}


