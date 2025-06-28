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
    const int n=14; // 4??
    const int mul=1; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    int worst_tree_val = -INF;
    mt19937 mt(time(0));
    int tries = 0;
    vector<int> gen(n);
    std::function<void()> go;
    vector<int> cnt_children(n);
    auto gen_tree = [&] (auto f, int i) -> void {
        if (i == n) {
            go();
            return;
        }
        for (int j = 0; j < i; j += 1) {
            gen[i] = j;
            cnt_children[j] += 1;
            if (cnt_children[j] <= 2) {
                f(f, i+1);
            }
            cnt_children[j] -= 1;
        }
    };
    int total_trees = 1;
    for (int i = 2; i < n; i += 1) {
        total_trees *= i;
    }
    go = [&] () -> void {
        tries += 1;
        vector<vector<int>> adj(n);
        vector<pair<int,int>> edges1, edges2, edges;
        for (int i = 1; i < n; i += 1) {
            int u = i, v = gen[i];
            edges.push_back({v, u});
            if (cnt_children[v] == 2) {
                edges2.push_back({v, u});
            } else {
                assert(cnt_children[v] == 1);
                edges1.push_back({v, u});
            }
            adj[v].push_back(u);
            adj[u].push_back(v);
        }
        int mini = INF;
        int mini_i = -1;
        int mini_rt = -1;
        for (int i = 0; i < (1<<edges2.size()); i += 1) {
            for (int rt = 0; rt == 0; rt += 1) {
                vector<vector<pair<bool,int>>> wadj(n);
                for (int j = 0; j < edges2.size(); j += 1) {
                    wadj[edges2[j].first].push_back({bool((1<<j)&i), edges2[j].second});
                    wadj[edges2[j].second].push_back({bool((1<<j)&i), edges2[j].first});
                }
                for (int j = 0; j < edges1.size(); j += 1) {
                    wadj[edges1[j].first].push_back({true, edges1[j].second});
                    wadj[edges1[j].second].push_back({true, edges1[j].first});
                }
                vector<int> head(n, -INF), end(n, -INF);
                vector<int> par(n, -INF);
                vector<int> d(n, -INF);
                vector<int> leaves;
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
                    if (leaf) {
                        leaves.push_back(u);
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
//                for (int j = 0; j < n; j += 1) {
                for (const int &j : leaves) {
                    int tot = 1;
                    int x = j;
                    while (x != rt) {
                        if (head[x] != x) {
                            if (end[x] == x) {
                                tot += 1;
                            } else {
                                tot += min(__lg((d[end[x]]-d[head[x]]+1)*mul-1)+2, (d[x]-d[head[x]]+1)*mul);
                            }
                            x = head[x];
                            if (x != rt) {
                                x = par[x];
                            } else {
                                tot -= 1;
                                break;
                            }
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
            for (int i = 0; i < edges1.size(); i += 1) {
                cout << edges1[i].first << " " << edges1[i].second << "\n";
            }
            for (int i = 0; i < edges2.size(); i += 1) {
                if (mini_i&(1<<i)) {
                    cout << edges2[i].first << " " << edges2[i].second << "\n";
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
//    gen[1] = 0;
//    gen[2] = 1;
//    gen[3] = 2;
//    gen[4] = 3;
//    gen[5] = 4;
//    gen[6] = 4;
//    gen[7] = 4;
//    gen[8] = 7;
//    gen[9] = 7;
//    gen[10] = 2;
//    gen[11] = 10;
//    gen[12] = 1;
//    gen[13] = 12;
//    gen[14] = 12;
//    gen[15] = 14;
//    gen[16] = 14;
//    gen[17] = 27;
//    gen[18] = 17;
//    gen[19] = 18;
//    gen[20] = 18;
//    gen[21] = 17;
//    gen[22] = 28;
//    gen[23] = 22;
//    gen[24] = 22;
//    gen[25] = 24;
//    gen[26] = 24;
//    gen[27] = 5;
//    gen[28] = 5;
//    go();
    gen_tree(gen_tree, 1);
}