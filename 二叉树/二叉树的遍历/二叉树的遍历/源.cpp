#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
const int N = 1e6 + 10;
using namespace std;
int n;
int l[N], r[N];

void dfs(int root) {
	if (!root) return;
	cout << root << " ";
	dfs(l[root]);
	dfs(r[root]);	
}

void dfs2(int root) {
	if (!root) return;
	dfs(l[root]);
	cout << root << " ";
}

void dfs3(int root) {
	if (!root) return;
	dfs(l[root]);
	dfs(r[root]);
	cout << root << " ";
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> l[i] >> r[i];
	}
	dfs(1);
	cout << endl;

	dfs2(1);
	cout << endl;

	dfs3(1);
	return 0;
}	