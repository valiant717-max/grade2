#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream> 
#include <vector>   
#include <map>  
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> b(2, -1);
        for (int i = 0; i < nums.size(); i++) {
                auto it = find(nums.begin()+i+1, nums.end(), target - nums[i]);
				if (it == nums.end() ) continue;
                b[0] = i;
                b[1] = it - nums.begin();
                break;
           
        }
        return b;
    }
};
int main() {
    Solution s;
    vector<int> a = { 3,2,4};
    int b = 6;
    vector<int> c = s.twoSum(a, b);
    for (int i = 0; i < c.size(); i++) {
        cout << c[i] << " ";
    }
    return 0;
}