#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
		int m = matrix.size();// number of rows
		int n = matrix[0].size();// number of columns
        vector<int> row(m), col(n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!matrix[i][j]) {
                    row[i] = col[j] = true;
                }
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (row[i] || col[j]) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};

int main() {
	Solution s;
	vector<vector<int>> matrix = { {1,1,1},{1,0,1},{1,1,1} };
	s.setZeroes(matrix);
	for (auto row : matrix) {
		for (auto col : row) {
			cout << col << " ";
		}
		cout << endl;
	}
	return 0;
}	