#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stack>
#include<vector>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        heights.insert(heights.begin(), 0);
		heights.push_back(0);
        stack<int>st;
        st.push(0);
        int ans = 0;
        for (int i = 1; i <heights.size(); i++) {
            while (!st.empty() && heights[i] < heights[st.top()]) {
                int t = st.top();
                st.pop();
				ans = max(ans,heights[t] * (i - st.top()-1));
           
            } 
            st.push(i);
        }
        return ans;
    }
};

int main() {
	vector<int>heights = { 2,1,5,6,2,3 };
    vector<int>heights2 = { 2,1,2 };
    cout << Solution().largestRectangleArea(heights) << endl;
	cout << Solution().largestRectangleArea(heights2);
    return 0;
}