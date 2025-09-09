#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

using namespace std;
const int N = 1e6 + 10;

int n, h;
int ne[N];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> ne[i];
		cin >> h;
	}
	for (int i = h; i; i = ne[i]) {
		cout << i << " ";
	}
	return 0;
}