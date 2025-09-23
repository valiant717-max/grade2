#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include<map>
using namespace std;
typedef long long LL;

int n, p;
map<string, int>mp;

bool check(char ch) {
	if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
		return true;
	}
		return false;
}
	int main() {
		cin >> n >> p;
		for (int i = 1; i <= n; i++) {
			string s;
			int x;
			cin >> s >> x;
			mp[s] = x;
		}
		LL ret = 0;
		char ch;
		string t = "";
		while (scanf("%c", &ch) != EOF) {
			if (check(ch))
				t += ch;
			else {
				ret = (ret + mp[t]) % p;
				t = "";
			}
		}
		cout << ret << endl;
		return 0;
	}
