#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_set>
using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        unordered_set<int> numSet;

        for (int num : nums) {
            if (num > 0) {  
                numSet.insert(num);
            }
        }
        // 从1开始检查每个正整数是否存在
        int target = 1;
        while (true) {
            if (numSet.find(target) == numSet.end()) {
                // 找到第一个不存在的正整数
                return target;
            }
            target++;
        }
    }
};

int main() {
	vector<int>nums = { 1,2,0 };
	Solution s;
	cout << s.firstMissingPositive(nums) << endl;
	return 0;
}