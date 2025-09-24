#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<unordered_map>

using namespace std;

typedef long long LL;
const int N = 2e5 + 10;

LL n, c;
LL a[N];
unordered_map<int, int>mp;
int main() {
	cin >> n >> c;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		mp[a[i]]++;
	}

	LL ret = 0;
	for (int i = 1; i <= n; i++) {
		ret += mp[c + a[i]];
	}
	cout << ret << endl;
	return 0;
}