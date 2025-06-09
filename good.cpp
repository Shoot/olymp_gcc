#include <bits/stdc++.h>
using namespace std;
#define int long long
#define YES(x) cout << (x?"YES\n":"NO\n")
#define NO(x) cout << (x?"NO\n":"YES\n")
#ifdef LO
#pragma GCC optimize("trapv")
#endif
#ifndef LO
#pragma GCC optimize("Ofast,unroll-loops")
#endif
constexpr int MOD = (119<<23)+1;
//constexpr int MOD = 967276608647009887ll;
//constexpr int MOD = 1e9+7;
signed main() {
#ifndef LO
    clog << "FIO\n";
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
    int T = 1;
//    cin >> T;
    for (int tt = 0; tt < T; tt += 1) {
        int n, q;
        cin >> n >> q;
        vector<int> a(n);
        for (auto &x : a) {
            cin >> x;
        }
        sort(a.begin(), a.end());
        for (int i = 0; i < q; i += 1) {
            int targ, each;
            cin >> targ >> each;
            int su = 0;
            for (const auto &x : a) {
                su += x - x%each;
            }
            int first_not_targ = -1;
            while (first_not_targ+1 < n && a[first_not_targ+1] < targ) {
                first_not_targ += 1;
            }
            int done = n-first_not_targ-1;
            int can = min(n, su / targ);
            int need = 0;
            for (int j = first_not_targ; j >= 0 && done != can; j -= 1) {
                need += (targ - a[j] + each - 1) / each;
                done += 1;
            }
            cout << can << " " << need << "\n";
            // x-a[i]%x <= c
            // x-a[i] <= c
        }
    }
}