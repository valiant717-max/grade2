#include<iostream>
#include<algorithm>
using namespace std;
int main() {
	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		int a[4];
		for (int j = 0; j < 4; j++) {
			cin >> a[j];
		}
		sort(a, a + 4);
		int b[4];
		for (int j = 0; j < 4; j++) {
			cin >> b[j];
		}
		sort(b, b + 4);
		int s;
		cin >> s;
		int c = s - a[3] - b[3];
		if (30 <= c && c <= 160) {
			printf("%.1f\n", c/10.0);
		}
		if (c > 160)cout << "Sad"<<endl;
	//这样写的话3.0可能被输出为3：if (c < 30)cout << 3.0 << endl;
		if(c<30)	printf("3.0\n");
	}
	return 0;
}