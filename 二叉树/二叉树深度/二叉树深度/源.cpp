#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

const int N = 1e6 + 10;

int n;
int l[N], r[N];
int dfs(int root) {
	if (!root) return 0;
	return max(dfs(l[root]), dfs(r[root])) + 1;
}

int main() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		cin >> l[i] >> r[i];
	} 
	cout << dfs(1) << endl;
	return 0;
}
