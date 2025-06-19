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
constexpr int INF = 1e6;
signed main() {
#ifndef LO
    clog << "FIO\n";
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
    int T=1;
//    cin >> T;
    for (int tt = 0; tt < T; tt += 1) {
        int shops, refiners, m;
        cin >> shops >> refiners >> m;
        vector<int> need(shops+1);
        for (int i = 1; i <= shops; i += 1) {
            cin >> need[i];
        }
        vector<int> have(refiners+1);
        for (int i = 1; i <= refiners; i += 1) {
            cin >> have[i];
        }
        vector<tuple<int,int,int>> edges(m);
        for (auto &[u, v, w] : edges) {
            cin >> u >> v >> w;
            v += shops;
        }
        int target_flow_value = accumulate(need.begin(), need.end(), 0ll);
        auto can = [&] (const int x) -> bool {
            int src = 0;
            int snk = shops+refiners+1;
            struct Edge { // u -> v
                int v;
                int adjv_idx; // u <- v index in adj[v]
                int cap;
            };
            vector<vector<Edge>> adj(snk+1);
            auto add_edge = [&] (int u, int v, int cap) -> void {
                int adj_v_idx = adj[v].size();
                int adj_u_idx = adj[u].size();
                adj[u].push_back(Edge(v, adj_v_idx, cap));
                adj[v].push_back(Edge(u, adj_u_idx, 0));
            };
            vector<vector<int>> cap(snk+1, vector<int>(snk+1));
            for (int i = 1; i <= shops; i += 1) {
                add_edge(src, i, need[i]);
            }
            for (int i = shops+1; i <= shops+refiners; i += 1) {
                add_edge(i, snk, have[i-shops]);
            }
            for (const auto &[u, v, w] : edges) {
                if (w <= x) {
                    cap[u][v] = INF;
                    add_edge(u, v, INF);
                }
            }
            auto bfs = [&] () -> vector<int> {
                queue<int> q;
                q.push(src);
                vector<int> layer(snk+1);
                layer[src] = 1;
                while (!q.empty()) {
                    auto v = q.front();
                    q.pop();
                    for (const auto &e : adj[v]) {
                        if (e.cap&&!layer[e.v]) {
                            layer[e.v] = layer[v]+1;
                            q.push(e.v);
                        }
                    }
                }
                return layer;
            };
            int total = 0;
            while (true) {
                auto layer = bfs();
                if (!layer[snk]) {
                    break;
                }
                vector<int> it(snk+1);
                auto dfs = [&] (auto f, int u, int flow) -> int {
                    if (u == snk) {
                        return flow;
                    }
                    for (; it[u] < adj[u].size(); it[u] += 1) {
                        auto &uv = adj[u][it[u]];
                        if (!uv.cap || layer[uv.v] != layer[u]+1) {
                            continue;
                        }
                        auto &vu = adj[uv.v][uv.adjv_idx];
                        int got = f(f, uv.v, min(uv.cap, flow));
                        if (got) {
                            uv.cap -= got;
                            vu.cap += got;
                            return got;
                        }
                    }
                    return 0ll;
                };
                while (int inc = dfs(dfs, src, INF)) {
                    total += inc;
                }
            }
            return total == target_flow_value;
        };
        int good = INF+1;
        int l = 1, r = INF;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (can(mid)) {
                good = mid;
                r = mid-1;
            } else {
                l = mid+1;
            }
        }
        cout << (good==INF+1?-1:good) << "\n";
    }
}