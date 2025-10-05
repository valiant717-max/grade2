#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size(), left = 0, right = 0;
        while (right < n) {
            if (nums[right]) {
                swap(nums[left], nums[right]);
				left++;// left only moves when a non-zero is found
            }
			right++;// right always moves forward
        }
    }
};

int main() {
	vector<int> nums = { 0,1,0,3,12 };
	return 0;
}