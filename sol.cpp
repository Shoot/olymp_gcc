#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    struct Edge {
        int u;
        int v;
    };
    vector<Edge> edges;
    edges.push_back({});
    vector<int> deactivate_vert(q+1);
    vector<int> deactivate_road(q+1);
    for (int i = 1; i <= q; i += 1) {
        char type;
        cin >> type;
        if (type == 'D') {
            int u;
            cin >> u;
            deactivate_vert[i] = u;
        }
        if (type == 'A') {
            int u, v;
            cin >> u >> v;
            edges.push_back({u, v});
        }
        if (type == 'R') {
            int r;
            cin >> r;
            deactivate_road[i] = r;
        }
    }
    vector<bool> sv(n+1, 1);
    vector<bool> se(edges.size(), 1);
    for (int i = 1; i <= q; i += 1) {
        if (deactivate_vert[i] != 0) {
            sv[deactivate_vert[i]] = 0;
        }
    }
    for (int i = 1; i <= q; i += 1) {
        if (deactivate_road[i] != 0) {
            se[deactivate_road[i]] = 0;
        }
    }
    vector<int> ans(n+1, -1);
    vector<multiset<int>> adj(n+1);
    auto activate_and_write_ans = [&] (auto f, int u, int x) -> void {
        if (ans[u] != -1) {
            return;
        }
        ans[u] = x;
        for (const auto &v : adj[u]) {
            f(f, v, x);
        }
    };
    for (int i = 1; i < edges.size(); i += 1) {
        if (se[i]) {
            auto [u, v] = edges[i];
            adj[u].insert(v);
            adj[v].insert(u);
        }
    }
    for (int i = 1; i <= n; i += 1) {
        if (sv[i]) {
            activate_and_write_ans(activate_and_write_ans, i, q);
        }
    }
    for (int i = q; i >= 1; i -= 1) {
        if (deactivate_vert[i]) {
            activate_and_write_ans(activate_and_write_ans, deactivate_vert[i], i-1);
        }
        if (deactivate_road[i]) {
            auto [u, v] = edges[deactivate_road[i]];
            adj[u].insert(v);
            adj[v].insert(u);
            if (ans[u] == -1 && ans[v] != -1) {
                // подключили к живому
                activate_and_write_ans(activate_and_write_ans, u, i-1);
            }
            if (ans[v] == -1 && ans[u] != -1) {
                // подключили к живому
                activate_and_write_ans(activate_and_write_ans, v, i-1);
            }
        }
    }
    for (int i = 1; i <= n; i += 1) {
        cout << ans[i] << "\n";
    }
}