#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm> 
using namespace std;

class Solution {
private:
    // 将gcd改为类的私有成员函数
    int gcd(int a, int b) {
        return b ? gcd(b, a % b) : a;
    }

public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        if (n <= 2) {
            return n;
        }
        int ret = 0;
        for (int i = 0; i < n; i++) {
            if (ret >= n - i || ret > n / 2) {
                break;
            }
            unordered_map<int, int> mp;
            for (int j = i + 1; j < n; j++) {
                int x = points[i][0] - points[j][0];
                int y = points[i][1] - points[j][1];

                if (x == 0) {
                    y = 1;
                }
                else if (y == 0) {
                    x = 1;
                }
                else {
                    if (y < 0) {
                        x = -x;
                        y = -y;
                    }
                    int gcdXY = gcd(abs(x), abs(y));
                    x /= gcdXY;
                    y /= gcdXY;
                }
                mp[y + x * 20001]++;
            }

            int maxn = 0;
            // 改用迭代器遍历，避免结构化绑定
            for (unordered_map<int, int>::iterator it = mp.begin(); it != mp.end(); ++it) {
                maxn = max(maxn, it->second + 1);
            }
            ret = max(ret, maxn);
        }
        return ret;
    }
};

int main() {
    Solution solution;

    vector<vector<int>> points1 = { {1,1}, {2,2}, {3,3} };
    cout << "测试用例1最大共线点数: " << solution.maxPoints(points1) << endl;

    vector<vector<int>> points2 = { {1,1}, {2,2}, {3,3}, {4,5} };
    cout << "测试用例2最大共线点数: " << solution.maxPoints(points2) << endl;

    vector<vector<int>> points3 = { {0,0}, {1,1}, {2,2}, {3,3}, {4,4} };
    cout << "测试用例3最大共线点数: " << solution.maxPoints(points3) << endl;

    vector<vector<int>> points4 = { {0,0}, {1,2}, {3,4}, {5,6}, {7,9} };
    cout << "测试用例4最大共线点数: " << solution.maxPoints(points4) << endl;

    vector<vector<int>> points5 = { {1,1}, {1,1}, {2,3} };
    cout << "测试用例5最大共线点数: " << solution.maxPoints(points5) << endl;

    return 0;
}
