#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<stack>
using namespace std;

class Solution {
public:
	vector<int> dailyTemperatures(vector<int>& temperatures) {
		vector<int> res(temperatures.size(), 0);
		stack<int> s; 
		s.push(0);
		for (int i = 1; i < temperatures.size(); i++) {
			
			while(!s.empty() &&temperatures[i] > temperatures[s.top()]) {
					res[s.top()] = (i - s.top());
					s.pop();
			}
			s.push(i);
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