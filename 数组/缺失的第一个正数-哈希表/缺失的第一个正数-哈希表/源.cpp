#include<iostream>
#include<vector>
using namespace std;

//就地哈希
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
		for (int& num : nums) {//将不在范围内的数置为n+1，直接修改原数组
            if (num <= 0) {
                num = n + 1;
            }
        } 
        for (int i = 0; i < n; ++i) {
            int num = abs(nums[i]);
            if (num <= n) {
                nums[num - 1] = -abs(nums[num - 1]);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (nums[i] > 0) {
                return i + 1;
            }
        }
        return n + 1;
    }
};

int main() {
	Solution sol;
	vector<int> nums = { 3, 4, -1, 1 };
	cout << sol.firstMissingPositive(nums) << endl; // Output: 2
	return 0;
}
