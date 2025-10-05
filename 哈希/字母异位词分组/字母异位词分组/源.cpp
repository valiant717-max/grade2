#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream> 
#include <vector>   
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;    

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
		unordered_map<string, vector<string>> mp;
		for (string& s : strs) {
			string t = s;
			sort(t.begin(), t.end());//排序后相同字母异位词会变成相同字符串
			mp[t].push_back(s);//将原字符串放入对应的组中
		}
		vector<vector<string>> res;
		for (auto& p : mp) {
			res.push_back(move(p.second));
		}
		return res;
    }
};

int main() {
	vector<string> strs = { "eat","tea","tan","ate","nat","bat" };
	for (auto& v : Solution().groupAnagrams(strs)) {
		cout << "[ ";	
		for (auto& s : v) {
			cout << s << " ";
		}	
		cout << "]\n";
	}
    return 0;
}