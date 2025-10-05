#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>   
#include <algorithm>    
#include <unordered_set>    
using namespace std;    

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
		unordered_set<int> num_set;
		for (int num : nums) {
			num_set.insert(num);
		}

		int longest_streak = 0;

		for (int num : num_set) {
			if (!num_set.count(num - 1)) { // only check for the start of a sequence
				int current_num = num;
				int current_streak = 1;

				while (num_set.count(current_num + 1)) {
					current_num += 1;
					current_streak += 1;
				}

				longest_streak = max(longest_streak, current_streak);
			}
		}

		return longest_streak;
    }
};

int main() {
    vector<int> nums = { 100,4,200,1,3,2 };
	Solution s;
	cout << s.longestConsecutive(nums) << endl;
	return 0;
}