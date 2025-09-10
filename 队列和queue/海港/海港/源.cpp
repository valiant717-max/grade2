#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include< queue>

using namespace std;
const int N = 1e5 + 10;

typedef pair<int, int>PII;
const int N = 1e5 + 10;

int n;
queue<PII>q;
int cnt[N];
int kinds;

int main() {
	cin >> n;
	while (n--) {
		int t, k;
		cin >> t >> k;
		for (int i = 0; i < k; i++) {
			int x; cin >> x;
			q.push({ t,x });
			if (cnt[x]++ == 0)kinds++;
		}
		while (q.size() && q.back().first - q.front().first >= 86400) {
			PII tmp = q.front(); q.pop();
			int x = tmp.second;
			if (cnt[x]-- == 1) kinds--;
		}
		cout << kinds << endl;
	}
	return 0;
}