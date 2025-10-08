#include<vector>
#include<iostream>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int i = matrix.size() - 1, j = 0;
        while (i >= 0 && j < matrix[0].size())
        {
            if (matrix[i][j] > target) i--;
            else if (matrix[i][j] < target) j++;
            else return true;
        }
        return false;
    }
};

int main() {
	vector<vector<int>> matrix = { {1,3,5,7},{10,11,16,20},{23,30,34,60} };
	Solution s;
	cout << s.searchMatrix(matrix, 3) << endl;
    return 0;
}