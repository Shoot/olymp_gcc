//#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace std;
//using namespace __gnu_pbds;
//template <typename T> using ordered_set =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define int long long
//#define double long double
#define YES(x) cout << (x?"YES\n":"NO\n")
#define ALICE(x) cout << (x?"Alice\n":"Bob\n")
#define BOB(x) cout << (x?"Bob\n":"Alice\n")
#define NO(x) cout << (x?"NO\n":"YES\n")
#ifdef LO
#pragma GCC optimize("trapv")
#endif
#ifndef LO
#pragma GCC optimize("Ofast,unroll-loops")
#endif
//constexpr int MOD = (119<<23)+1;
//constexpr int MOD = 967276608647009887ll;
//constexpr int MOD = 1e9+7;
constexpr int INF = 1e18;
signed main() {
#ifndef LO
    clog << "FIO\n";
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
#ifdef LO
    cout << unitbuf;
#endif
    int T;
    cin >> T;
    for (int tt = 0; tt < T; tt += 1) {
        int n, MOD;
        cin >> n >> MOD;
//        vector<int> cnt_free(n+1, 1);
//        vector<int> ans(n+1);
//        for (int i = 1; i <= n; i += 1) {
//            vector<int> nw(n+1, 0);
//            for (int use_here = 0; use_here <= i; use_here += 1) {
////                if (i == 1) {
////                    if (use_here) {
////                        continue;
////                    }
////                }
////                if (i == 2 && use_here > 1) {
////                    continue;
////                }
////                cout << i << ": " << use_here << ": " << cnt_free[use_here]*(use_here==0?1:(use_here))%MOD << "\n";
////                if (use_here) {
//                    (ans[i] += cnt_free[use_here]*(use_here==0?1:(use_here))%MOD) %= MOD;
////                }
//                for (int j = 0; j <= n; j += 1) {
//                    if (j > use_here || j == 0) {
//                        (nw[j] += cnt_free[use_here]*(use_here==0?1:(use_here))%MOD) %= MOD;
//                    }
//                }
//            }
//            cnt_free = nw;
//        }
//        cout << ans[n] << "\n";
        vector<vector<int>> dp(n+1, vector<int>(n+1));
        dp[n][0] = 1;
        int ans = 0;
        // m_i — matching
        // number of arrays is    П_{m_i != 0} m_i     =     a(m)
        // we simply want \Sigma_{every possible m} a(m)
        for (int cand = n; cand >= 1; cand -= 1) {
            for (int occ = 0; occ <= n-cand; occ += 1) {
                (dp[cand-1][occ] += dp[cand][occ]) %= MOD;
                (dp[cand-1][occ+1] += dp[cand][occ]*(n+1-cand-occ)*cand) %= MOD;
            }
        }
        for (int occ = 0; occ <= n; occ += 1) {
            (ans += dp[/*cand=*/0][occ]) %= MOD;
        }
        cout << ans << "\n";
    }
}