#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	int maxArea(vector<int>& height) {
		int left = 0;
		int rigth = height.size() - 1;
		int maxArea = 0;
		while (left < rigth) {
			int currentArea = (min(height[left], height[rigth]) * (rigth - left));
			maxArea = max(maxArea, currentArea);
			if (height[left] < height[rigth]) {
				left++;
			}
			else {
				rigth--;
			}
		}
		return maxArea;
	}
};

int main()
{
	Solution s;
	vector<int> height = { 1,8,6,2,5,4,8,3,7 };
	cout << s.maxArea(height) << endl;
	return 0;
}