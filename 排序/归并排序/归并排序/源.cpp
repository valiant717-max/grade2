#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

const int N = 1e5 + 10;

int n;
int a[N];
int tmp[N];

void merge_sort(int left, int right) {
	if (left >= right)return;
	int mid = (left + right) >> 1;
	merge_sort(left, mid);
	merge_sort(mid + 1, right);
	int cur1 = left, cur2 = mid + 1, i = left;
	while (cur1 <= mid && cur2 <= right) {
		if (a[cur1] <= a[cur2]) tmp[i++] = a[cur1++];
		else tmp[i++] = a[cur2++];	
	}
	while (cur1 <= mid)tmp[i++] = a[cur1++];
	while (cur2 <= right)tmp[i++] = a[cur2++];
	for (int j = left; j <= right; j++) {
		a[j] = tmp[j]; 
	}
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	merge_sort(1, n);
	for (int i = 1; i <= n; i++) cout << a[i] << " ";
	return 0;
}
