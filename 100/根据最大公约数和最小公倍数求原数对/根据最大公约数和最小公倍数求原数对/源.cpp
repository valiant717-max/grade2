#include<iostream>
#include<cmath>
using namespace std;
int gcd(int a, int b) {
	if (a % b == 0) return b;
	return gcd(b, a % b);
}
int main() {
	int t; cin >> t;
	for (int i = 0; i < t; i++) {
		int n, m;
		cin >> n >> m;
		int k = m / n;
		for (int x = 1; x <= sqrt(k); x++) {
			if (k % x == 0) {
				int y =k/x;
				if (gcd(x, y) == 1) {
					cout << n * min(x, y) << " " << (max(x, y)) * n << endl;
				}
			}
		}
	}
	return 0;
}