#include <bits/stdc++.h>
using namespace std;
#define int long long
#ifdef LO
#pragma GCC optimize("trapv")
#endif
signed main() {
#ifndef LO
    clog << "FIO\n";
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
    int T;
    cin >> T;
    for (int tt = 0; tt < T; tt += 1) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto &x : a) {
            cin >> x;
        }
        vector<int> b(n);
        for (auto &y : b) {
            cin >> y;
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        for (const auto &x : a) {
            cout << x << " ";
        }cout << "\n";
        for (const auto &x : b) {
            cout << x << " ";
        }cout << "\n";
    }
}
