#include <bits/stdc++.h>
using namespace std;
#define int long long
#ifdef LO
#pragma GCC optimize("trapv")
#endif
#ifndef LO
#pragma GCC optimize("Ofast,unroll-loops")
#endif
constexpr int MOD = (119<<23)+1;
//constexpr int MOD = 1e9+7;
signed main() {
#ifndef LO
    clog << "FIO\n";
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
    int T = 1;
//    cin >> T;
//    for (int tt = 0; tt < T; tt += 1) {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> adj(n+1);
    for (int i = 0; i < n-1; i += 1) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<unordered_map<int,int>> cnt_d(n+1);
    int ans = 0;
    vector<vector<int>> match_with(n+1, vector<int>(k+1));
    auto dfs = [&] (auto f, int u, int p, int d) -> int {
        int sz = 1;
        int argmax = -1;
        int f_argmax = -1;
        for (const auto &x : adj[u]) {
            if (x != p) {
                int chsz = f(f, x, u, d+1);
                if (chsz > f_argmax) {
                    argmax = x;
                    f_argmax = chsz;
                }
                sz += chsz;
            }
        }

        match_with[u][0] = 1;
        for (const auto &x : adj[u]) {
            if (x != p) {
                for (int dist = 1; dist <= k; dist += 1) {
                    if (cnt_d[x].count(d+dist)) {
                        ans += cnt_d[x][d+dist]*match_with[u][k-dist];
                    }
                }
                for (int dist = 1; dist <= k; dist += 1) {
                    if (cnt_d[x].count(d+dist)) {
                        match_with[u][dist] += cnt_d[x][d+dist];
                    }
                }
            }
        }
        if (argmax != -1) {
            swap(cnt_d[argmax], cnt_d[u]);
            for (const auto &x : adj[u]) {
                if (x != p && x != argmax) {
                    for (const auto &[a, b] : cnt_d[x]) {
                        cnt_d[u][a] += b;
                    }
                }
            }
        }
        cnt_d[u][d] += 1;
        return sz;
    };
    dfs(dfs, 1, -1, 1);
//    for (const auto &[a, b] : cnt_d[1]) {
//        cout << a << ": " << b << "\n";
//    }
    cout << ans << "\n";
}