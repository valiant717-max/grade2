#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>;
#include <vector>;
class Solution {
public:
	void moveZeroes(vector<int>& nums) {
		for (int i = 0, cur = -1; i < nums.size(); i++) {
			if (nums[i]) {
				swap(nums[++cur], nums[i]);

			}
		}
	}
};