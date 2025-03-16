#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast,unroll-loops")
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<vector<pair<int,int>>> adj(n+1+4*n+10);
    int FIRST = -1;
    int LAST = -1;
    auto build = [&] (auto f, int u, int tl, int tr) -> void {
        if (tl == tr) {
            if (tl == 1) {
                FIRST = n+1+u;
            }
            if (tl == n) {
                LAST = n+1+u;
            }
            adj[n+1+u].push_back({1, tl});
            return;
        }
        int tm = (tl + tr) >> 1;
        f(f, 2*u+1, tl, tm);
        f(f, 2*u+2, tm+1, tr);
        adj[n+1+u].push_back({0, n+1+2*u+1});
        adj[n+1+u].push_back({0, n+1+2*u+2});
    };
    build(build, 0, 1, n);
    auto add_edges = [&] (auto f, int u, int tl, int tr, int l, int r, int i) -> void {
        if (l == tl && r == tr) {
            adj[i].push_back({0, n+1+u});
            return;
        }
        int tm = (tl + tr) >> 1;
        if (l <= tm) {
            f(f, 2*u+1, tl, tm, l, min(r, tm), i);
        }
        if (r >= tm+1) {
            f(f, 2*u+2, tm+1, tr, max(l, tm+1), r, i);
        }
    };
    for (int i = 1; i <= n; i += 1) {
        int l, r;
        cin >> l >> r;
        add_edges(add_edges, 0, 1, n, l, r, i);
    }
    vector<vector<pair<int,int>>> iadj(n+1+4*n+10);
    for (int i = 0; i < adj.size(); i += 1) {
        for (const auto &[w, x] : adj[i]) {
            iadj[x].push_back({w, i});
        }
    }
    deque<int> q1;
    vector<int> dist1(n+1+4*n+10, 1e8);
    dist1[FIRST] = 0;
    q1.push_back({FIRST});
    while (!q1.empty()) {
        auto u = q1.front();
        q1.pop_front();
        for (const auto &[w, x] : iadj[u]) {
            if (dist1[x] > dist1[u] + w) {
                dist1[x] = dist1[u] + w;
                if (w) {
                    q1.push_back(x);
                } else {
                    q1.push_front(x);
                }
            }
        }
    }
    deque<int> qn;
    vector<int> distn(n+1+4*n+10, 1e8);
    distn[LAST] = 0;
    qn.push_back({LAST});
    while (!qn.empty()) {
        auto u = qn.front();
        qn.pop_front();
        for (const auto &[w, x] : iadj[u]) {
            if (distn[x] > distn[u] + w) {
                distn[x] = distn[u] + w;
                if (w) {
                    qn.push_back(x);
                } else {
                    qn.push_front(x);
                }
            }
        }
    }
    priority_queue<pair<int,int>> q;
    vector<int> finaldist(n+1+4*n+10, 1e9);
    for (int i = 1; i < n+1+4*n+10; i += 1) {
        finaldist[i] = dist1[i] + distn[i] + 1;
        q.push({-finaldist[i], i});
    }
    vector<bool> seen(n+1+4*n+10);
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        if (seen[u]) {
            continue;
        }
        seen[u] = true;
        for (const auto &[w, x] : iadj[u]) {
            if (finaldist[x] > finaldist[u] + w) {
                finaldist[x] = finaldist[u] + w;
                q.push({-finaldist[x], x});
            }
        }
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; i += 1) {
        int x;
        cin >> x;
        cout << (finaldist[x]>=1e8?-1:finaldist[x]) << "\n";
    }
}