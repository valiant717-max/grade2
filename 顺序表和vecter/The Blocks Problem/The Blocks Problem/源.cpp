#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>

using namespace std;
const int N = 30;
typedef pair<int, int>PII;

int n;
vector<int> p[N];//创建n个放木块的槽

//找到木块x所在的位置
PII find(int x) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < p[i].size(); j++) {
			if (p[i][j] == x) return { i,j };
		}
	} 
}

//把[x,y]以上的木块归位
void clear(int x,int y) {
	for (int j = y + 1; j < p[x].size(); j++) {
		int t = p[x][j];
		p[t].push_back(t);
	}
	p[x].resize(y + 1);	
}

void move(int x1, int y1, int x2) {
	//把[x1,y1]及其以上的木块移动到x2上
	for (int j = y1; j < p[x1].size(); j++) {
		int t = p[x1][j];
		p[x2].push_back(t);
	}
	p[x1].resize(y1);
}
	int main() {
		cin >> n;
		for (int i = 0; i < n; i++) {
			p[i].push_back(i);
		}
	
		string op1, op2;
		int a, b;
		while(cin>>op1>>a>>op2>>b){
			PII pa = find(a);
			int x1 = pa.first, y1 = pa.second;
			PII pb = find(b);
			int x2 = pb.first, y2 = pb.second;

			if (x1 == x2) continue;
			if (op1 == "move") clear(x1, y1);
			if (op2 == "onto") clear(x2, y2);
		}
		move(x1, y1, x2);
	}

	for (int i = 0; i < n; i++) {
		cout << i << ":";
		for (int j = 0; j < p[i].size(); j++) {
			cout << " " << p[i][j];
		}
		cout << endl;
	}

	return 0;
}


