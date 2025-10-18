#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

bool is_leap(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

int get_days_in_year(int year) {
    // 闰年 366 天，平年 365 天
    return 365 + (is_leap(year) ? 1 : 0);
}

int get_days_in_month(int year, int month) {
    // 默认平年月天数
    const int days_per_month[] = {
        0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

    if (month == 2) {
        // 如果是闰年，2月是 29 天，否则是 28 天
        return days_per_month[month] + (is_leap(year) ? 1 : 0);
    }
    else {
        return days_per_month[month];
    }
}

void solve() {
    int z; cin >> z;

    int current_year = 1970;

    // 1. 确定年份：循环减去该年总天数
    while (true) {
        int days_in_year = get_days_in_year(current_year);

        // 如果 z 大于等于当前年份的总天数，说明日期落在下一年
        if (z >= days_in_year) {
            z -= days_in_year;
            current_year++;
        }
        else {
            // 找到正确的年份
            break;
        }
    }

    int current_month = 1;

    // 2. 确定月份：循环减去该月天数
    while (true) {
        int days_in_month = get_days_in_month(current_year, current_month);

        // 如果 z 大于等于当前月份的天数，说明日期落在下一月
        if (z >= days_in_month) {
            z -= days_in_month;
            current_month++;
        }
        else {
            // 找到正确的月份
            break;
        }
    }

    // 3. 确定日期
    // z 是从该月 1 日之后的第 z 天，所以日期是 z + 1
    int current_day = z + 1;

    // 4. 格式化输出 (年-月-日, 月和日保留两位，不足补 0)
    // setw(2) 设置宽度为 2，setfill('0') 填充 0
    cout << current_year << "-"<< setfill('0') << setw(2) << current_month << "-"<< setfill('0') << setw(2) << current_day << "\n";
}

int main() {
    solve();
    return 0;
}