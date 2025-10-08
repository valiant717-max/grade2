#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
		if (nums.empty()) return vector<int>(2, -1);
		int left = 0, right = nums.size() - 1;
		vector<int> res(2, -1);
		int temp = 0;
		// Find the first position
		while (left <= right) {
			int mid = left + (right - left) / 2;
			if (nums[mid] < target) {
				left = mid + 1;
			}
			else if (nums[mid]>target) {
				right = mid - 1;
			}
			else {
				temp = mid;
				break;
			}
		}
		for (int j = temp; j >= 0; j--) {
			if (nums[j] == target) {
				res[0] = j;
			}
			else {
				break;
			}
		}
		for (int j = temp; j < nums.size(); j++) {
			if (nums[j] == target) {
				res[1] = j;
			}
			else {
				break;
			}
		}
		return res;
    }
};

int main() {
	Solution s;
	vector<int> nums = { 5,7,7,8,8,10 };
	int target = 8;
	vector<int> res = s.searchRange(nums, target);
	cout << res[0] << " " << res[1] << endl;
	return 0;
}