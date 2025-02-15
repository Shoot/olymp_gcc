#include <bits/stdc++.h>
using namespace std;
signed main() {
    string l, r;
    cin >> l >> r;
    auto ok = [&] (string s) -> bool {
        long long one = 0;
        for (const auto &x : s) {
            one += x == '1';
        }
        if (one != s.size()-1) {
            return false;
        }
        for (const auto &x : s) {
            if (x == '0' || x == '4' || x == '6' || x == '8' || x == '9') {
                return false;
            }
        }
        return true;
    };
    vector<long long> all(500'001);
    for (long long i = 1; i <= 500000; i += 1) {
        all[i] = all[i-1] + 4*i;
    }
    auto cnt = [&] (const string &s, char x) -> long long {
        long long tot = s.size();
        for (long long i = 0; i < s.size(); i += 1) {
            if (s[i] == '1') {
                tot -= 1;
                continue;
            }
            if (s[i] == '0') {
                tot = 0;
                break;
            }
            bool can = true;
            for (long long j = i+1; j < s.size(); j += 1) {
                if (s[j] > '1') {
                    break;
                }
                can &= s[j] == '1';
            }
            tot -= s[i] < x || s[i] == x && !can;
            break;
        }
        return tot;
    };
    auto fnd = [&] (string s) -> long long {
        return cnt(s, '2')+cnt(s, '3')+cnt(s, '5')+cnt(s, '7')+all[s.size()-1];
    };
    cout << fnd(r)-fnd(l)+ok(l) << "\n";
}