#include <iostream>
#include<vector>
#include<unordered_set>
using namespace std;

int main() {
    int L, R; cin >> L >> R;

    int maxD = 7; 
    vector<int> pow10(maxD + 1, 1);
    for (int i = 1; i <= maxD; ++i) pow10[i] = pow10[i - 1] * 10;

    long long total = 0;

    for (int d = 2; d <= maxD; ++d) {
        int low = max(L, pow10[d - 1]);
        int high = min(R, pow10[d] - 1);
        if (low > high) continue;
        for (int a = low; a <= high; ++a) {
            unordered_set<int> seen;
            int pow10_k = 1;
            for (int k = 1; k < d; ++k) {
                pow10_k *= 10; 
                int left = a / pow10_k;
                int right = a % pow10_k;
                int b = right * (pow10[d] / pow10_k) + left;
				if (b < pow10[d - 1]) continue;//处理前导0情况

                if (b > a && b <= R && b >= low && b <= high) {
                    if (seen.insert(b).second) total++;
                }
            }
        }
    }

    cout << total << '\n';
    return 0;
}