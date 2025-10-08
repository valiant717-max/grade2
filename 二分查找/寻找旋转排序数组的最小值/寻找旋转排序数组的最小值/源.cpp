#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;

        // 数组为空（按题意可能不会出现，但增加鲁棒性）
        if (nums.empty()) return -1;

        // 若数组未旋转（升序），直接返回第一个元素
        if (nums[left] < nums[right]) {
            return nums[left];
        }

        // 二分查找旋转点（最小元素）
        while (left < right) {
            int mid = left + (right - left) / 2;

            // 若mid处元素大于右侧元素，说明最小元素在右侧
            if (nums[mid] > nums[right]) {
                left = mid + 1;
            }
            // 否则最小元素在左侧（包括mid）
            else {
                right = mid;
            }
        }

        // 循环结束时left == right，即为最小元素位置
        return nums[left];
    }
};


int main() {
	Solution s;
	vector<int> v = { 3,4,5,1,2 };
	cout << s.findMin(v) << endl;
	return 0;
}