#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		
		if (nums.size() == 1) {
			if (nums[0] !=1) {
				return 1;
			}
		}
		if (nums[0] > 1)
			return 1;
		for (int i = 1; i < nums.size(); i++) {
			
			if (nums[i] > 1 && nums[i - 1] <= 0) {
				return 1;
			}		
			else if (nums[i] > 0 && nums[i - 1] > 0 && nums[i] - nums[i - 1] >1) {
				return nums[i - 1] + 1;
			}
		}
		return max(nums.back() + 1,1);
	}
};

int main() {
	vector<int> nums = { 0,1,1,2,2 };
	Solution s;
	cout << s.firstMissingPositive(nums) << endl;
	return 0;
}