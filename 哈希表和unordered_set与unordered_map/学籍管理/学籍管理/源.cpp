#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<unordered_map>

using namespace std;
int main() {
	unordered_map<string, int>mp;
	int T; cin >> T;
	while (T--) {
		int op;
		string name;
		cin >> op;
		if (op == 1) {
			cin >> name;
			int x; cin >> x;
			mp[name] = x;
			cout << "OK" << endl;
		}
		else if (op == 2) {
			cin >> name;
			if (mp.count(name)) cout << mp[name] << endl;
			else cout << "Not found" << endl;
		}
		else if (op == 3) {
			cin >> name;
			if (mp.count(name)) {
				mp.erase(name);
				cout << "Deleted successfully" << endl;
			}
			else {
				cout << mp.size() << endl;
			}
		}
	}
	return 0;
 }