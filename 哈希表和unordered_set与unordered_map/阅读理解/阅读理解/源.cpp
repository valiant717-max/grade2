#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<set>
#include<unordered_map>

using namespace std;

unordered_map<string, set<int>>mp;

int main() {
	int n; cin >> n;
	for (int i = 1; i <= n; i++) {
		int l; cin >> l;
		while (l--) {
			string s; cin >> s;
			mp[s].insert(i);
		}
	}
	int m; cin >> m;
	while (m--) {
		string s; cin >> s;
		for (auto i : mp[s]) {
			cout << i << "";
		}
		cout << endl;
	}
	return 0;
}