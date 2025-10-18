#include <iostream>
#include <string>
#include <map>

using namespace std;

void solve() {
    map<string, int> scores;
    scores["tourist"] = 3858;
    scores["ksun48"] = 3679;
    scores["Benq"] = 3658;
    scores["Um_nik"] = 3648;
    scores["apiad"] = 3638;
    scores["Stonefeang"] = 3630;
    scores["ecnerwala"] = 3613;
    scores["mnbvmar"] = 3555;
    scores["newbiedmy"] = 3516;
    scores["semiexp"] = 3481;

    string S;cin >> S;
    cout << scores[S] << endl;
}

int main() {
    solve();
    return 0;
}