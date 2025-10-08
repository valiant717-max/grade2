#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {  // 枚举起始位置i
            int temp = 0;
            for (int right = i; right < n; right++) {  // 枚举结束位置right（从i开始）
                temp += nums[right];  // 累加当前子数组和
                if (temp == k) {  // 找到和为k的子数组
                    ans++;
                }
                // 注意：即使temp超过k也不break，因为可能存在负数使后续总和再次等于k
            }
        }
        return ans;
    }
};

int main() {
    vector<int> nums = { 1, 1, 1 };
    Solution s;
    cout << s.subarraySum(nums, 2) << endl;  // 正确输出：2
    return 0;
}
