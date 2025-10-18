#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

using namespace std;
int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x, t, v, t2;
		double x2 = 0;
		cin >> x >> t >> v >> t2;
		x2 = (t2 - t) * v;
		if (x2 >= x) cout << "Nice!" << endl;
		else cout << "No!!!" << endl;
	}
	return 0;
}