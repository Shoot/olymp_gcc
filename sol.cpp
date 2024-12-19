#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
using namespace std;
//define endl "\n"
using ll = int;
const ll INF = 1e9;
mt19937 mt(time(0));
void solve() {
    ll n, m; cin >> n >> m;
    vector<pair<ll, ll>> edges(m);
    for (auto &[u, v] : edges) {
        cin >> u >> v;
    }
    vector<ll> p(n+1), sz(n+1, 1);
    iota(p.begin(), p.end(), 0ll);
    auto find = [&] (auto f, ll u) -> ll {
        if (p[u] != u) {
            return f(f, p[u]);
        }
        return p[u];
    };
    vector<pair<ll&, ll>> modns;
    auto unite = [&] (ll u, ll v) -> void {
        u = find(find, u);
        v = find(find, v);
        if (u == v) {
            return;
        }
        if (sz[u] > sz[v]) {
            swap(u, v);
        }
        modns.push_back({sz[v], sz[v]});
        sz[v] += sz[u];
        modns.push_back({p[u], p[u]});
        p[u] = v;
    };
    struct Q {
        ll l;
        ll r;
        ll idx;
    };
    ll q; cin >> q;
    vector<ll> ans(q);
    vector<Q> ask(q);
    for (ll i = 0; i < q; i += 1) {
        ll l, r; cin >> l >> r;
        ask[i].l = l - 1;
        ask[i].r = r - 1;
        ask[i].idx = i;
    }
    const ll C = 200;
    sort(ask.begin(), ask.end(), [&] (Q a, Q b) {
        if (a.l/C == b.l/C) return a.r < b.r;
        return a.l/C < b.l/C;
    });
    ll last_made = -1;
    for (ll i = 0; i < q; i += 1) {
        for (ll j = max(last_made, ask[i].l/C*C+C); j <= ask[i].r;  j += 1) { // without rollback
            auto [u, v] = edges[j];
            unite(u, v);
        }
        last_made = max(last_made, ll(ask[i].r));
        ll r = ll(modns.size());
        for (ll idx = ask[i].l; idx <= min(ask[i].r, ask[i].l/C*C+C-1); idx += 1) {
            auto [u, v] = edges[idx];
            unite(u, v);
        }
        ans[ask[i].idx] = n-modns.size()/2;
        while (ll(modns.size()) > r) {
            modns.back().first = modns.back().second;
            modns.pop_back();
        }
        if (i+1 < q && ask[i+1].l/C != ask[i].l/C) {
            while (modns.size() > 0) {
                modns.back().first = modns.back().second;
                modns.pop_back();
            }
            last_made = -1;
        }
    }
    for (const auto &x : ans) {
        cout << x << "\n";
    }
}

int main(int32_t argc, char* argv[]) {
    bool use_fast_io = true;
    for (int32_t i = 1; i < argc; i += 1) use_fast_io &= string(argv[i]) != "-local-no-fast-io";
    if (use_fast_io) ios::sync_with_stdio(false), cin.tie(0);
    ll tt = 1;
    while (tt--)
        solve();
    return 0;
}
