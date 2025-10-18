#include<iostream>
using namespace std;

int main() {
	char ch;
	cin >> ch;
	int sum = 0;
	int num = 0;
 	int j = 0;
	while (ch != '#') {
			cin >> num;
			if (ch == '+')sum += num;
			else if (ch == '-')sum -= num;
			else if (ch == '*')sum *= num;
			else if (ch == '/') {
				if (num == 0) {
					cout << "divided by zero" << endl;
					cin >> ch;
					continue;
				}
				sum /= num;
			}
			else {
				cout << "invalid input" << endl;
				cin >> ch;
				continue;
			}

			if (j != 2) {
				cout << sum << endl;
				j++;
			}

			else if (j == 2) {
				if (sum == 0)cout << sum << endl;

				if (sum > 0) {
					int temp = sum;
					int sum2 = 0;
					while (temp) {
						sum2 = sum2 * 10 + temp % 10;
						temp /= 10;
					}
					sum = sum2;
					cout << sum << endl;
				}

				if (sum < 0) {
					sum = abs(sum);
					int temp = sum;
					int sum2 = 0;
					while (temp) {
						sum2 = sum2 * 10 + temp % 10;
						temp /= 10;
					}
					sum = -sum2;
					cout << sum << endl;
				}

				j = 0;
			}
			cin >> ch;
		}	
	return 0;
}