#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include<vector>
#include<queue>
#include<cmath>

using namespace std;

const int N = 2e5 + 10;

int n;
int s[N];

int e[N];
int pre[N], ne[N];

struct node {
	int d;
	int l, r;
	bool operator<(const node& x)const {
		if (d != x.d) return d > x.x.l;
		else if (l != x.l) return l > x.l;
		else return r > x.r;	
	}
};

priority_queue<node> heap;
bool st[N];
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		char ch; cin >> ch;
		if (ch == 'B') s[i] = 1;
	}

	for (int i = 1; i <= n; i++) {
		cin >> e[i];
		pre[i] = i - 1;
		ne[i] = i + 1;

	}
	pre[1] = ne[n] = 0;

	for (int i = 2; i <= n; i++) {
		if (s[i] != s[i - 1])
			heap.push({ abs(e[i] - e[i - 1]),i - 1,i });
	}

	//提取结果
	vector<node> ret;//暂存结果

	while (heap.size()) {
		node t = heap.top();
		heap.pop();
		int d = t.d, l = t.l, r = t.r;

		if (st[l] || st[r]) continue;

		ret.push_back(t);
		st[l] = st[r] = true;
		ne[pre[l]] = ne[r];
		pre[ne[r]] = pre[l];

		int left = pre[l], right = ne[r];
		if (left && right && s[left] != s[right]) {
			heap.push({ abs(e[left] - e[right]),left,right });
		}
	}
	cout << ret.size() << endl;
	for (auto& x : ret) cout << x.l << " " << x.r << endl;

	return 0;
}