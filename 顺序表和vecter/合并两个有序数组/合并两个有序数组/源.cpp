#define _CRT_SECURE_NO_WARNINGS 1
class Solution1 {
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		vector<int> tmp(m + n);
		int cur = 0; cur = 0, cur2 = 0;
		while (cur1 < m && cur2 < n) {
			if (nums1[cur1] <= nums2[cur2]) {
				tmp[cur++] = nums1[cur1++];
			}
			else tmp[cur++] = nums[cur2++];
		}
	}
		while (cur1 < m) {
			tmp[cur++] = nums1[cur1++];
		}
		while (cur2<n){
			tmp[cur++] = nums2[cur2++];
		}for (int i = 0; i < n + m; i++) nums1[i] = tmp[i];

	}
};
class Solution {
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		int cur = m - 1, cur2 = n - 1, cur = m + n - 1;
		while (cur1 >= 0 && cur2 >= 0) {
			if (nums1[cur1] >= nums2[cur2] >= 0) {
				if (nums1[cur1] >= nums2[cur2]) nums1[cur--] = nums1[cur1--];
				else nums1[cur--] = nums2[cur2--];
			}
			while (cur2 >= 0) nums1[cur--] = nums2[cur2--]; 
		}
	};