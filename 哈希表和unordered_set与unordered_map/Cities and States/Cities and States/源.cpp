#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<unordered_map>

using namespace std;

int n;

int main() {
	cin >> n;
	unordered_map<string, int>mp;
	int ret = 0;
	while (n--) {
		string a, b; cin >> a >> b;
		a = a.substr(0, 2);
		if (a == b)continue;
		ret += mp[b + a];
		mp[a + b]++;
	}
	cout << ret << endl;
	return 0;
}