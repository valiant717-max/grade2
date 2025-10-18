#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

void solve() {
    int n;
    cin >> n;

    // 设置输出精度为一位小数
    cout << fixed << setprecision(1);

    // 循环处理每一场比赛
    for (int k = 0; k < n; ++k) {

        vector<int> A(4);
        vector<int> B(4);
        int S; // 对手实力值总和

        // 读取队友1的实力值 
        for (int i = 0; i < 4; ++i) {
            if (!(cin >> A[i])) return;
        }

        // 读取队友2的实力值
        for (int i = 0; i < 4; ++i) {
            if (!(cin >> B[i])) return;
        }

        // 读取对手实力值总和 S
        if (!(cin >> S)) return;

        // 小坤的实力值范围 [30, 160]
        const int MIN_XK_STRENGTH = 30;
        const int MAX_XK_STRENGTH = 160;

        // 1. 找到队友能提供的最大实力值 R_max
        // 使用 max_element 找到队友1和队友2各自的最大实力值
        int max_A = *max_element(A.begin(), A.end());
        int max_B = *max_element(B.begin(), B.end());

        // 最大的队友实力值总和
        int max_R = max_A + max_B;

        // 2. 计算小坤理论上所需的最小实力值 Xk_needed
        // Xk_needed = S - max_R
        int xk_needed = S - max_R;

        // 3. 确定小坤实际所需的最小实力值 Xk_final（必须满足 >= 30）
        int xk_final = max(MIN_XK_STRENGTH, xk_needed);

        // 4. 判断是否能获胜 (即 Xk_final 是否 <= 160)
        if (xk_final > MAX_XK_STRENGTH) {
            // 即使队友实力最大化，小坤也需要超过 160 才能赢
            cout << "Sad" << "\n";
        }
        else {
            // 输出最小实力值对应的评分 (实力值 * 0.1)
            double min_score = (double)xk_final * 0.1;
            cout << min_score << "\n";
        }
    }
}

int main() {
    // 优化输入输出速度
 /*   ios_base::sync_with_stdio(false);
    cin.tie(NULL);*/
    solve();
    return 0;
}