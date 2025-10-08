#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        multiset<int> window;  // 存储当前窗口元素（自动排序）
        vector<int> ans;
        int n = nums.size();

        // 处理边界情况：数组为空或窗口大小为0
        if (n == 0 || k == 0) return ans;

        // 初始化第一个窗口
        for (int i = 0; i < k; ++i) {
            window.insert(nums[i]);
        }
        ans.push_back(*window.rbegin());  // 第一个窗口的最大值

        // 滑动窗口
        for (int i = k; i < n; ++i) {
            // 移除上一个窗口的左边界元素
            auto it = window.find(nums[i - k]);
            if (it != window.end()) {
                window.erase(it);
            }
            // 插入当前元素（新窗口的右边界）
            window.insert(nums[i]);
            // 记录当前窗口最大值
            ans.push_back(*window.rbegin());
        }

        return ans;
    }
};

int main() {
    // 测试用例1
    vector<int> nums1 = { 1, 3, -1, -3, 5, 3, 6, 7 };
    int k1 = 3;
    Solution sol;
    vector<int> result1 = sol.maxSlidingWindow(nums1, k1);

    cout << "测试用例1: nums = [1,3,-1,-3,5,3,6,7], k = 3" << endl;
    cout << "滑动窗口最大值: ";
    for (int val : result1) {
        cout << val << " ";
    }
    cout << endl;  // 预期输出: 3 3 5 5 6 7

    // 测试用例2（含重复元素）
    vector<int> nums2 = { 1, 1, 1, 1, 1 };
    int k2 = 2;
    vector<int> result2 = sol.maxSlidingWindow(nums2, k2);

    cout << "测试用例2: nums = [1,1,1,1,1], k = 2" << endl;
    cout << "滑动窗口最大值: ";
    for (int val : result2) {
        cout << val << " ";
    }
    cout << endl;  // 预期输出: 1 1 1 1

    // 测试用例3（窗口大小等于数组长度）
    vector<int> nums3 = { 5, 4, 3, 2, 1 };
    int k3 = 5;
    vector<int> result3 = sol.maxSlidingWindow(nums3, k3);

    cout << "测试用例3: nums = [5,4,3,2,1], k = 5" << endl;
    cout << "滑动窗口最大值: ";
    for (int val : result3) {
        cout << val << " ";
    }
    cout << endl;  // 预期输出: 5

    return 0;
}
