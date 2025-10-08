#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>	
#include <vector>
#include <string>	
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        for (const auto& row : matrix) {
            for (int element : row) {
                if (element == target) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
	Solution s;
	vector<vector<int>> matrix = { {1,3,5,7},{10,11,16,20},{23,30,34,60} };
	int target = 3;
	cout << s.searchMatrix(matrix, target) << endl;
	return 0;
}