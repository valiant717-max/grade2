#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include<unordered_set>

using namespace std;

int main() {
	int T;
	cin >> T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		unordered_set<int>mp;
		for (int i = 1; i <= n; i++) {
			int x;
			scanf("%d", &x);
			if (!mp.count(x)) {
				printf("%d", x);
				mp.insert(x);

			}
		}
		puts("");
	}
	return 0;
}