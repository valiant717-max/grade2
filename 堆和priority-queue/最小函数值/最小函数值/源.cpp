#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<queue>

using namespace std;

typedef long long LL;
const int N = 1e4 + 10;

int n, m;
LL a[N], b[N], C[N];

struct node {
	LL f;
	LL num;
	LL x;

	bool operator < (const node& x)const {
		return f > x.f;
	}
};

priority_queue<node> heap;

LL calc(LL i,LL x) {
	return a[i] * x * x + b[i] * x + C[i];	
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i] >> C[i];
	}	

	for (int i = 1; i <= n; i++) {
		heap.push({ calc(i,1),i,1 });
	}	

	while (m--) {
		auto t = heap.top(); heap.pop();
		LL f = t.f, num = t.num, x = t.x;

		cout << f << " ";
		heap.push({ calc(num,x + 1),num,x + 1 });
		}
		return 0;

}