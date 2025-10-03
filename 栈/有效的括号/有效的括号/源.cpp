#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stack>
#include<string>
#include<unordered_map>

using namespace std;

    bool isValid(string s) {
        int n = s.size();
        if (n % 2 == 1)
            return false;

        unordered_map<char, char>pairs = {
            {')','('},
             {']','['},
              {'}','{'}
        };

            stack<char> stk;
        for (char ch : s) {
            if (pairs.count(ch)) {
                if (stk.empty() || stk.top() != pairs[ch]) {
                    return false;
                }
                stk.pop();
            }
            else stk.push(ch);
        }
        return stk.empty();
    }

	int main() {    
        string s;
        getline(cin, s);
		bool result = isValid(s);
        cout << result;
        return 0;
}