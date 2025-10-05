#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream> 
#include <vector>   
#include <unordered_map>  
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hash_map;
        for (int i = 0; i < nums.size(); ++i) {
            if (hash_map.count(target - nums[i])) {
                return { hash_map[target - nums[i]], i };
            }
            hash_map[nums[i]] = i;
        }
        return {};
    }
};

int main() {
    Solution s;
    vector<int> a = { 3,2,4 };
    int b = 6;
    vector<int> c = s.twoSum(a, b);
    for (int i = 0; i < c.size(); i++) {
        cout << c[i] << " ";
    }
    return 0;
}