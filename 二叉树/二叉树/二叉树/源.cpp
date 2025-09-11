#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>

using namespace std;

const int N = 300;

int n;
char root;
char l[N], r[N];

void dfs(char root) {
	if (root == '.') return;
	cout << root;
	dfs(l[root]);
	dfs(r[root]);
}

int main() {
	cin >> root;
	cin >> l[root] >> r[root];
	for (int i = 2; i <= n; i++) {
		char t; cin >> t;
		cin >> l[t] >> r[t];
	}
	dfs(root);
	return 0;
}