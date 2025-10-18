#include<iostream>
#include<set>
using namespace std;
int main() {
	int t; cin >> t;
	for (int i = 0; i < t; i++) {
		int n; cin >> n;
		multiset<int>mp;
		for (int j = 0; j < n; j++) {
			int temp;
			cin >> temp;
			mp.insert(temp);
		}
		int sum1 = 0, sum2 = 0;
		auto it = mp.begin();
		for(int j = 0; j < n; j++) {
			if (*it % 2 == 0)sum1 += *it;
			else sum2 += *it;
			it++;
		}
		if (sum1 > sum2)cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}