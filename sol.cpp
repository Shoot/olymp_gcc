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
#ifndef LO
    clog << "FIO\n";
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
    cout << unitbuf;
//#ifdef LO
//    cout << unitbuf;
//#endif
    int n=12;
    int worst_tree_val = -INF;
    mt19937 mt(time(0));
    int tries = 0;
    vector<int> gen(n);
    std::function<void()> go;
    auto gen_tree = [&] (auto f, int i) -> void {
        if (i == n) {
            go();
            return;
        }
        for (int j = 0; j < i; j += 1) {
            gen[i] = j;
            f(f, i+1);
        }
    };
    int total_trees = 1;
    for (int i = 2; i < n; i += 1) {
        total_trees *= i;
    }
    go = [&] () -> void {
        tries += 1;
//        vector<int> repl(n);
//        iota(repl.begin(), repl.end(), 0);
//        shuffle(repl.begin(), repl.end(), mt);
        vector<vector<int>> adj(n);
        vector<pair<int,int>> edges;
        for (int i = 1; i < n; i += 1) {
            int u = i, v = gen[i];
            edges.push_back({v, u});
            adj[v].push_back(u);
            adj[u].push_back(v);
        }
        int mini = INF;
        int mini_i = -1;
        int mini_rt = -1;
        for (int i = 0; i < (1<<(n-1)); i += 1) {
            for (int rt = 0; rt == 0; rt += 1) {
                vector<bool> heavy(n-1);
                vector<vector<pair<bool,int>>> wadj(n);
                for (int j = 0; j < n-1; j += 1) {
                    wadj[edges[j].first].push_back({bool((1<<j)&i), edges[j].second});
                    wadj[edges[j].second].push_back({bool((1<<j)&i), edges[j].first});
                }
                vector<int> head(n, -INF), end(n, -INF);
                vector<int> par(n, -INF);
                vector<int> d(n, -INF);
                auto dfs = [&] (auto f, int u, int hd) -> void {
                    if (hd == -1) {
                        hd = u;
                        head[u] = u;
                    }
                    end[u] = u;
                    bool leaf = true;
                    int cnt = 0;
                    for (const auto &[w, x] : wadj[u]) {
                        leaf &= x == par[u];
                        cnt += x != par[u] && w;
                    }
                    for (const auto &[w, x] : wadj[u]) {
                        if (x != par[u]) {
                            d[x] = d[u]+1;
                            par[x] = u;
                            if (w && cnt == 1) {
                                head[x] = head[u];
                                f(f, x, u);
                                end[u] = end[x];
                            } else {
                                f(f, x, -1);
                            }
                        }
                    }
                };
                dfs(dfs, rt, -1);
                int metric = 0;
                for (int j = 0; j < n; j += 1) {
                    int tot = 0;
                    int x = j;
                    while (x != rt) {
                        if (head[x] != x) {
                            if (end[x] == x) {
                                tot += 1;
                            } else {
                                tot += __lg(d[end[x]]-d[head[x]]+1-1)+2;
                            }
                            x = head[x];
                        } else {
                            x = par[x];
                            tot += 1;
                        }
                    }
                    metric = max(metric, tot);
                }
                if (metric < mini) {
                    mini_i = i;
                    mini_rt = rt;
                    mini = metric;
                }
            }
        }
//        if (worst_tree_val == mini /*&& !(tries&0b111111)*/) {
//            cout << "HI" << mini << " " << tries << "\n";
//        }
        if (100ll*tries/total_trees != 100ll*(tries-1)/total_trees) {
            cout << 100ll*tries/total_trees << "% = " << tries << " / " << total_trees << "\n";
        }
        if (worst_tree_val < mini) {
            for (auto &[u, v] : edges) {
                cout << u << " " << v << "\n";
            }
            cout << "\n";
            for (int i = 0; i < n-1; i += 1) {
                if (mini_i&(1<<i)) {
                    cout << edges[i].first << " " << edges[i].second << "\n";
                }
            }
            worst_tree_val = mini;
            cout << mini_i << " " << mini_rt << " = heavy edges, root\n";
            cout << mini << " " << worst_tree_val << "!\n";
            cout << "==================================\n";
        }
//        int x;
//        cin >> x;
    };
    gen_tree(gen_tree, 1);
}