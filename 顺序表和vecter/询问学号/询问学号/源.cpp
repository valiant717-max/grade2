#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>

using namespace std;
const int N = 1e5 + 10;

int n, m;
vector<int> a(N);
 
int main()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> a[i];
	while (m--) {
		int x; cin >> x;
		cout << a[x] << endl;
	}
	return 0;
}