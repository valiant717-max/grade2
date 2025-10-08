#include<vector>
#include<iostream>
#include<string>
#include<set>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.size() == 0)return 0;
        int n = s.size();
        multiset<char> set;
		int ans = 1, right = -1;

        for (int i = 0; i < n; i++) {
            while (right + 1 < n && !set.count(s[right + 1])) {
				set.insert(s[++right]);
            }
			ans = right - i + 1 > ans ? right - i + 1 : ans;
            set.erase(s[i]);
        }
        return ans;
    }
};

int main() {
    Solution s;
    string str = "abcab";
    int ans = s.lengthOfLongestSubstring(str);
    cout << ans << endl;
    return 0;
}