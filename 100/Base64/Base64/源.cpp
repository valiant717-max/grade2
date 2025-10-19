#include <iostream>
#include <string>
using namespace std;

string buildBase64Table() {
    string table;
    for (char c = 'A'; c <= 'Z'; ++c) table += c;
    for (char c = 'a'; c <= 'z'; ++c) table += c;
    for (char c = '0'; c <= '9'; ++c) table += c;
    table += '+';
    table += '/';
    return table;
}

int main() {
    string s;
    getline(cin, s);

    string base64_chars = buildBase64Table();
    string result;

    int val = 0;
    int bits = -6;

    for (char c : s) {
        val = (val << 8) + c;
        bits += 8;
        while (bits >= 0) {
            result.push_back(base64_chars[(val >> bits) & 0x3F]);
            bits -= 6;
        }
    }

    if (bits > -6)
        result.push_back(base64_chars[((val << 8) >> (bits + 8)) & 0x3F]);

    while (result.size() % 4)
        result.push_back('=');

    cout << result << endl;
    return 0;
}