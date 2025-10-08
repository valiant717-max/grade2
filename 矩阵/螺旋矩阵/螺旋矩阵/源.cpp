#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include<vector>
using namespace std;
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ans;
        int m = matrix.size(), n = matrix[0].size();
        int up = 0, down = m - 1, left = 0, right = n - 1;
        while (ans.size() < m * n) {
            // ср
            for (int i = left; i <= right; i++) {
                if (ans.size() >= m * n)
                    return ans;
                ans.push_back(matrix[up][i]);
            }
            up++;

            // об
            for (int i = up; i <= down; i++) {
                if (ans.size() >= m * n)
                    return ans;
                ans.push_back(matrix[i][right]);
            }
            right--;

            // вС
            for (int i = right; i >= left; i--) {
                if (ans.size() >= m * n)
                    return ans;
                ans.push_back(matrix[down][i]);
            }
            down--;

            // ио
            for (int i = down; i >= up; i--) {
                if (ans.size() >= m * n)
                    return ans;
                ans.push_back(matrix[i][left]);
            }
            left++;
        }
        return ans;
    }
};

int main() {
	vector<vector<int>> matrix = { {1,2,3},{4,5,6},{7,8,9} };
	Solution s;
	s.spiralOrder(matrix);
	for (int i : s.spiralOrder(matrix))
		cout << i << " ";
	return 0;
}