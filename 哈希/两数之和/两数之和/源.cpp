#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>   
using namespace std;

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		for (int i = 0; i < nums.size(); i++) {
			for (int j = i + 1; j < nums.size(); j++) {
				if (nums[i] + nums[j] == target) {
					return { i, j };
				}
			}
		}
		// 添加默认返回值，处理没有找到解决方案的情况
		return {};
	}
};

int main() {
	vector<int> nums = { 2,7,11,15 };
	Solution s;
	vector<int> result = s.twoSum(nums, 9);

	for (auto i : result) {
		cout << i << " ";  // 输出: 0 1
	}
	return 0;
}
