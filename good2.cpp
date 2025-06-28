//#include "testlib.h"
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
template <typename T> using ordered_set =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define int long long
#define YES(x) cout << (x?"YES\n":"NO\n")
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
    ofstream cout("hh.txt");
#ifndef LO
    clog << "FIO\n";
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
#ifdef LO
    cout << unitbuf;
#endif
    auto fenw_ops = [&] (const int x) -> int {
        if (x <= 1) {
            assert(false);
        }
        return __lg(x-1)+2;
    };
    int N = 5e5;
    vector<int> dp(N+1);
    vector<pair<int,int>> ch(N+1);
    vector<int> palka(N+1);
    dp[1] = 1;
    for (int i = 2; i <= N; i += 1) {
        for (int use = 1; use <= i; use += 1) {
            if ((use&(use-1)) && fenw_ops(use+1) < (1<<__lg(use))) {
                continue;
            }
            for (int one = 0; i-use-one >= one; one += 1) {
                int another = i-use-one;
                if (!one) {
                    int x = dp[another];
                    if (dp[i] < x) {
                        ch[i] = {one, another};
                        palka[i] = use;
                    }
                    dp[i] = max(dp[i], x);
                } else {
                    int x = min({max(dp[one]+1, dp[another]+1),
                                 max(dp[one]+min(use, fenw_ops(use+1)), dp[another]+0),
                                 max(dp[one]+0, dp[another]+min(use, fenw_ops(use+1)))});
                    if (dp[i] < x) {
                        ch[i] = {one, another};
                        palka[i] = use;
                    }
                    dp[i] = max(dp[i], x);
                }
            }
        }
//        cout << "(" << i << ", " << dp[i] << ")\n";
        cout << "(" << i << ", " << dp[i] << " " << ch[i].first << "|" << dp[ch[i].first] << " " << ch[i].second << "|" << dp[ch[i].second] << "), " << palka[i] << "\n";
    }
    int curr = 1;
    auto print = [&] (auto f, const int x) -> int {
        if (!x) {
            return -1;
        }
        int U = curr++;
        int u = U;
        for (int i = 0; i < palka[x]-1; i += 1) {
            int v = curr++;
            cout << u << " " << v << "\n";
            u = v;
        }
        int v1 = f(f, ch[x].first), v2 = f(f, ch[x].second);
        if (v1 != -1) {
            cout << u << " " << v1 << "\n";
        }
        if (v2 != -1) {
            cout << u << " " << v2 << "\n";
        }
        return U;
    };
}