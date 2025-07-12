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
constexpr int MOD = (119<<23)+1;
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
        int n;
        cin >> n;
        vector<vector<int>> adj(n+1);
        vector<int> d(n+1);
        vector<int> P(n+1);
        d[1] = 1;
        for (int i = 2; i <= n; i += 1) {
            cin >> P[i];
            d[i] = d[P[i]]+1;
            adj[P[i]].push_back(i);
        }
        vector<int> tree(n);
        auto add = [&] (int idx, int inc) -> void {
            for (idx += 1; idx-1 < tree.size(); idx += idx&-idx) {
                tree[idx-1] += inc;
            }
        };
        auto gt = [&] (int idx) -> int {
            int ret = 0;
            for (idx += 1; idx > 0; idx -= idx&-idx) {
                ret += tree[idx-1];
            }
            return ret;
        };
        vector<int> tin(n+1), tout(n+1);
        int t = 0;
        auto dfs = [&] (auto f, int u) -> void {
            tin[u] = t++;
            for (const auto &x : adj[u]) {
                f(f, x);
            }
            tout[u] = t-1;
        };
        dfs(dfs, 1);
        auto inc_v = [&] (int u) -> void {
            add(tin[u], 1);
        };
        auto gt_v = [&] (int u) -> int {
            return gt(tout[u]) - gt(tin[u]-1);
        };

        int c = 1, greatest_c_ch = 0;
        inc_v(1);
        for (int i = 2; i <= n; i += 1) {
            inc_v(i);
            if (tin[i] > tin[c] && tout[i] <= tout[c]) {
                int l = 0, r = adj[c].size()-1;
                int good = -1; // = second_on_path(c, /* -> */ i)
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (tout[adj[c][mid]] >= tout[i]) {
                        good = mid;
                        r = mid-1;
                    } else {
                        l = mid+1;
                    }
                }
                assert(good != -1);
                int u = adj[c][good];
                if (gt_v(u) > i/2) {
                    c = u;
                    greatest_c_ch = i/2;
                } else {
                    greatest_c_ch = max(greatest_c_ch, gt_v(u));
                }
            } else {
                int u = P[c];
                if (i-gt_v(c) > i/2) {
                    c = u;
                    greatest_c_ch = i/2;
                } else {
                    greatest_c_ch = max(greatest_c_ch, i-gt_v(c));
                }
            }
            cout << i-2*greatest_c_ch << " ";
        }cout << "\n";
    }
}