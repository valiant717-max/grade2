#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<set>
using namespace std;

typedef long long LL;
const LL INF = 1e10 + 10;
set<LL>mp;
int main() {
	int q; cin >> q;
	mp.insert(-INF);
	mp.insert(INF);
	while (q--) {
		LL op, len; cin >> op >> len;
		if(op==1){
		if (mp.count(len)) cout << "Already Exist" << endl;
		else mp.insert(len);
	}
	else {
		if (mp.size() == 2) {
			cout << "Empty" << endl;
		}
		
		else {
			auto it = mp.lower_bound(len);
			auto tmp = it;
			tmp--;
			if (abs(*tmp - len) <= abs(*it - len)) {
				cout << *tmp << endl;
				mp.erase(tmp);
			}
			else {
				cout << *it << endl;
				mp.erase(it);
			}
		}
	}
	return 0;
}