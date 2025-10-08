#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
	void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0) return; // 处理空数组
        // 关键：处理k >= n的情况，等价于旋转k % n次
        k = k % n;
        if (k == 0) return; 
         //方法1：额外数组（与原思路一致，补充边界处理）
         vector<int> ans;
         // 提取后k个元素
         for (int i = 0; i < k; ++i) {
             ans.push_back(nums[n - k + i]);
         }
         // 提取前n-k个元素
         for (int i = 0; i < n - k; ++i) {
             ans.push_back(nums[i]);
         }
         nums = ans; 
	}
};

int main() {
	vector<int> nums = { 1,2,3,4,5,6,7 };
	int k = 3;
	Solution s;
	s.rotate(nums, k);
	return 0;
}
