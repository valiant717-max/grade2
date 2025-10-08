#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
		vector<int> temp;
		for (int i = 0; i < nums.size(); i++) {
			int ans = 1;
			
			for (int j = 0; j < i; j++) {
				ans *= nums[j];
			}
			for (int j = i + 1; j < nums.size(); j++) {
				ans *= nums[j];
			}
			temp.push_back(ans);
		}
		return temp;
    }
};

int main() {
	vector<int> nums = { 1,2,3,4 };
	Solution s;
	vector<int> ans = s.productExceptSelf(nums);
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i] << " ";
	}
    return 0;
}