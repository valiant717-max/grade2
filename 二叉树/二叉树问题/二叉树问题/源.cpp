#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>		
#include<queue>

using namespace std;

const int N = 110;
 
int n;
vector<int> edges[N];

int fa[N];
int dist[N];

int dfs(int u) {
	int ret = 0;
	for (auto v : edges[u]) {
		ret = max(ret,dfs(v));
	}
	return ret + 1;

}

int bfs() {
	queue<int> q;
	q.push(1);
	int ret = 0;
	while (q.size()) {
		int sz = q.size();	
		ret = max(ret, sz);	
		while (sz--)
		{
			int u = q.front(); q.pop();
			for (auto v : edges[u]) {
				q.push(v);
			}
		}
	}
	return ret;
}	
int main() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v; cin >> u >> v;
		edges[u].push_back(v);	
		fa[v] = u;
	}

	cout << dfs(1) << endl;	
	cout << bfs() << endl;	
	int x, y;
	cin >> x >> y;
	while (x != 1) {
		dist[fa[x]] = dist[x] + 1;	
		x = fa[x];	
	}
	int len = 0;
	while (y != 1 && dist[y] == 0) {
		len++;
		y = fa[y];
	}
	cout << len + dist[y] *2<< endl;	
	return 0;
}