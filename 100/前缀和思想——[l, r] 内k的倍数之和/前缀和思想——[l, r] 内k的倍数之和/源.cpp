#include<iostream>
using namespace std;
 
int gcd(int a, int b) {
	if (a % b == 0)return b;
	else return gcd(b, a % b);
}

int lcm(int a,int b) {
	return a * b / gcd(a, b);	
}



int sum(int r, int k) {
	int ans = 0;
	int n = r / k;
	ans = k * n * (n + 1) / 2;
	return ans;
}


int f(int l, int r, int k) {
	return sum(r, k)- sum(l - 1, k);
}



int main() {
	int n, x, y, l, r;
	cin >> n >> x >> y >> l >> r;
	int lcm_xy = lcm(x, y);

	cout << f(l, r, lcm_xy) << " " << f(l, r, x) + f(l, r, y) - f(l, r, lcm_xy);
	return 0;
}

