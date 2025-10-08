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

        reverse(nums.begin(), nums.end()); // 整体反转
        reverse(nums.begin(), nums.begin() + k); // 反转前k个元素
        reverse(nums.begin() + k, nums.end()); // 反转剩余元素
		for (int m : nums) cout << m << " "; // 输出结果
    }
};

int main() {
    vector<int> nums = { 1,2,3,4,5,6,7 };
    int k = 3;
    Solution s;
    s.rotate(nums, k);
    return 0;
}
