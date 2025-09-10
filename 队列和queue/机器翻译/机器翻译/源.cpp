#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<queue>

using namespace std;

const int N = 1010;

int m, n;
queue<int>q;
bool st[N];

int main() {
	cin >> m >> n;
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		if (st[x]) continue;

		cnt++;
		q.push(x);
		st[x] = true;
		if (q.size() > m) {
			st[q.front()] = false;
			q.pop();
		}
	}
	cout << cnt << endl;
}
