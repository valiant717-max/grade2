#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
		if (intervals.size() == 0) return {};
		vector<vector<int>> res;
		sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });
		res.push_back(intervals[0]);
		for (int i = 1; i < intervals.size(); i++) {
			if (res.back()[1] >= intervals[i][0]) {
				res.back()[1] = max(res.back()[1], intervals[i][1]);
			}
			else {
				res.push_back(intervals[i]);
			}
		}
		return res;
    }
};
 
int main() {
	vector<vector<int>> intervals = { {1,3},{2,6},{8,10},{15,18} };
	Solution s;
	for (auto v : s.merge(intervals)) {
		for (auto i : v) {
			cout << i << " ";
		}
		cout << endl;
	}
    return 0;
}