#include<iostream>
using namespace std;
int main() {
	int a, b;
	cin >> a >> b;
	if (a == b)cout << a << endl;
	else if (a == 0 && b == 1 || a == 1 && b == 0)cout << 2 << endl;
	else if (a == 0 && b == 2 || a == 2 && b == 0) cout << 1 << endl;
	else cout << 0 << endl;
	return 0;
}