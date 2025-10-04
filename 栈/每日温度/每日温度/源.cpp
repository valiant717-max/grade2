#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>    
#include<stack>

using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
		vector<int> res(temperatures.size(), 0);
        for (int i = 0; i < temperatures.size(); i++) {
            for (int j = i + 1; j < temperatures.size(); j++) {
				if (temperatures[j] > temperatures[i]) {
					res[i] = j - i;
					break;
				}
				res[i] = 0;
            }
 
        }
        return res;
	}	
};

int main() {
    Solution s;
	vector<int> temperatures = { 73,74,75,71,69,72,76,73 };
	for (int i : s.dailyTemperatures(temperatures))
		cout << i << " ";	
    return 0;
}