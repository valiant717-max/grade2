#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	int maxSubArray(vector<int>& nums) {
		int maxAns = nums[0]; int pre = 0;
		for (int i = 0; i < nums.size(); i++) {
			pre = max(pre + nums[i], nums[i]);
			maxAns = max(maxAns, pre);
		}
		return maxAns;
	}
};

int main() {
	vector<int> nums = { -2,1,-3,4,-1,2,1,-5,4 };
	Solution s;
	cout << s.maxSubArray(nums);
	return 0;
}