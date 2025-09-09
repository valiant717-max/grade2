#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e5 + 10;
int n, q;
vector<int> a[N];
int main() {
	cin >> n >> q;
	while (q--) {
		int op, i, j, k;
		if (op == 1) {
			cin >> k;
			if (a[i].size() <= j) {
				a[i].resize(j+1);

			}
			a[i][j] = k;
		}
		else {
			cout << a[i][j] << endl;
		}
	}
	return 0;
}
