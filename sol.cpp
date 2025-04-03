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
    int TT = 1;
    cin >> TT;
    for (int tt = 0; tt < TT; tt += 1) {
        int l, r, g;
        cin >> l >> r >> g;
        l = (l+g-1)/g;
        r = r/g;
        int maxi = -1, ansl = -1, ansr = -1;
        for (int L = l; L - l < 30; L += 1) {
            for (int R = r; L <= R && r-R < 30; R -= 1) {
                if (__gcd(L, R) == 1) {
                    if (maxi < R-L) {
                        maxi = R-L;
                        ansl = L*g;
                        ansr = R*g;
                    }
                }
            }
        }
        cout << ansl << " " << ansr << "\n";
    }
}
