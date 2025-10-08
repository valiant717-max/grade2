#include <vector>
#include <deque>
#include<iostream>
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        deque<int> dq; // 存储索引，对应元素值单调递减

        for (int i = 0; i < nums.size(); i++) {
            // 1. 维护单调性：从队尾移除比当前元素小的元素索引（需先判断队列非空）
            while (!dq.empty() && nums[dq.back()] < nums[i]) {
                dq.pop_back();
            }
            // 2. 将当前索引入队
            dq.push_back(i);
            // 3. 移除超出窗口范围的队首元素
            if (dq.front() <= i - k) {
                dq.pop_front();
            }
            // 4. 当窗口形成后，记录当前窗口最大值
            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }
        return result;
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