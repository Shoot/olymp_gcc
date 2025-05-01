#include <bits/stdc++.h>
using namespace std;
#define int long long
#ifdef LO
#pragma GCC optimize("trapv")
#endif
constexpr int MOD = (119<<23)+1;
signed main() {
#ifndef LO
    clog << "FIO\n";
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
    int TT = 1;
    cin >> TT;
    for (int tt = 0; tt < TT; tt += 1) {
        int n, k;
        cin >> n >> k;
        int mini = 0;
        int maxi = n;
        while (n) {
            mini += n % 3;
            n /= 3;
        }
        if (mini <= k && k <= maxi && (k-mini)%2==0) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}