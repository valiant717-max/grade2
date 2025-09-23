#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include<set>
using namespace std;
const int INF = 1e7 + 10;
int n;
set<int> mp;

int main() {
	cin >> n;
	int ret;
	cin >> ret;
	mp.insert(ret);
	mp.insert(-INF); mp.insert(INF);
	for (int i = 2; i <= n; i++) {
		int x; cin >> x;
		auto it = mp.lower_bound(x);
		auto tmp = it;
		tmp--;
		if (*it == x)continue;
		ret += min(abs(*tmp - x), abs(*it - x));
		mp.insert(x);
	}
	cout << ret << endl;
	return 0;
}
