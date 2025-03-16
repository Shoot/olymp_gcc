#include <bits/stdc++.h>
using namespace std;
signed main() {
    string s;
    cin >> s;
    vector<string> check = {"ONE","TWO","THREE","FOUR","FIVE","SIX","SEVEN","EIGHT","NINE"};
    for (const auto &x : check) {
        int it = 0;
        for (int i = 0; i < s.size(); i += 1) {
            if (it < x.size() && s[i] == x[it]) {
                it += 1;
            }
        }
        if (it == x.size()) {
            cout << x << "\n";
            return 0;
        }
    }
    cout << "NO\n";
}