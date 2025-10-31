#include<iostream>
#include<string>

using namespace std;

int main() {
    int k;
    cin >> k;
    while (k--) {  // 简化循环写法
        string s;
        cin >> s;
        int len = s.length();
        int i = 0;
        int segmentCount = 0;  // IP段的数量（需为4）
        bool isValid = true;   // 标记是否有效
         
        while (i < len && isValid) {
            int num = 0;
            int start = i;  // 记录当前段的起始位置

            // 提取当前段的数字（遇到.或结束时停止）
            while (i < len && s[i] != '.') {
                if (s[i] < '0' || s[i] > '9') {  // 非数字字符无效
                    isValid = false;
                    break;
                }
                num = num * 10 + (s[i] - '0');
                i++;
                // 检查数字是否超过255（提前终止，避免溢出）
                if (num > 255) {
                    isValid = false;
                    break;
                }
            }

            if (!isValid) break;  // 若已无效，退出循环

            // 检查前导零：段长度>1时，不能以0开头（如"01"无效）
            int segmentLen = i - start;
            if (segmentLen > 1 && s[start] == '0') {
                isValid = false;
                break;
            }

            segmentCount++;  // 当前段有效，计数+1

            // 若不是最后一个字符，必须是.（否则格式错误）
            if (i < len) {
                if (s[i] != '.') {
                    isValid = false;
                    break;
                }
                i++;  // 跳过.，处理下一段
                if (i == len) {
                    isValid = false;
                    break;
                }
            }
        }

        // 最终校验：必须有4个段，且最后一个字符不能是.（避免末尾有.）
        if (segmentCount != 4 || i != len) {
            isValid = false;
        }

        cout << (isValid ? "yes" : "no") << endl;
    }
    return 0;
}