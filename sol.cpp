#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    int n;
    cin >> n;
    vector<int> val(n+1);
    for (int i = 1; i <= n; i += 1) {
        cin >> val[i];
    }
    vector<vector<int>> adj(n+1);
    for (int i = 0; i < n-1; i += 1) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> sz(n+1);
    bitset<1'000'000> done;
    auto calc_sizes = [&] (auto f, int u, int p) -> void {
        sz[u] = 1;
        for (const auto &v : adj[u]) {
            if (v != p && !done[v]) {
                f(f, v, u);
                sz[u] += sz[v];
            }
        }
    };
    int su = 0;
    auto find_centroid_in_subtree = [&] (auto f, int u, int root, int p) -> int {
        int subtree_size = sz[root];
        for (const auto &x : adj[u]) {
            if (x != p && !done[x] && sz[x] > subtree_size / 2) {
                return f(f, x, root, u);
            }
        }
        return u;
    };
    vector<int> w(n+1);
    vector<int> d(n+1);
    vector<pair<int,int>> curr_w_d;
    curr_w_d.reserve(1'000'000);
    auto calc_w_d = [&] (auto f, int u, int p) -> void {
        curr_w_d.push_back({w[u], d[u]});
        for (const auto &x : adj[u]) {
            if (x != p && !done[x]) {
                d[x] = d[u] + 1;
                w[x] = w[u] + val[x];
                f(f, x, u);
            }
        }
    };
    auto solve = [&] (auto f, int root) -> void {
        calc_sizes(calc_sizes, root, -1);
        int centroid = find_centroid_in_subtree(find_centroid_in_subtree, root, root, -1);
        int cnt = 1;
        int suD = 0;
        int suW = val[centroid];
        int suWD = 0 * val[centroid];
        for (const auto &x : adj[centroid]) {
            if (!done[x]) {
                curr_w_d.clear();
                d[x] = 1;
                w[x] = val[x];
                calc_w_d(calc_w_d, x, centroid);
                for (const auto &[W, D] : curr_w_d) {
                    su += cnt * W * D;
                    su += suD * W;
                    su += suW * D;
                    su += suWD;
                }
                for (const auto &[W, D] : curr_w_d) {
                    cnt += 1;
                    suW += W + val[centroid];
                    suD += D;
                    suWD += (W + val[centroid])*D;
                }
            }
        }
        done[centroid] = true;
        for (const auto &x : adj[centroid]) {
            if (!done[x]) {
                f(f, x);
            }
        }
    };
    solve(solve, 1);
    cout << su << "\n";
}