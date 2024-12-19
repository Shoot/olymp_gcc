#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
using namespace std;
#define endl "\n"
using ll = long long;
const ll INF = 1e18;
mt19937 mt(time(0));
void solve() {
    ll n; cin >> n; ll q; cin >> q;
    struct Edge {
        ll u;
        ll v;
    };
    const ll sz = max(q, 1ll);
    vector<vector<Edge>> tree(4*sz+10);
    auto set_edge = [&] (auto f, ll v, ll tl, ll tr, ll l, ll r, Edge e) -> void {
        if (tl == l && tr == r) {
            tree[v].push_back(e);
            return;
        }
        ll tm = (tl + tr) >> 1;
        if (l <= tm) {
            f(f, 2*v+1, tl, tm, l, min(tm, r), e);
        }
        if (r >= tm+1) {
            f(f, 2*v+2, tm+1, tr, max(l, tm+1), r, e);
        }
    };
    map<pair<ll,ll>, ll> time_last_added;
    vector<bool> is_asked(sz+1);
    vector<ll> answer(sz+1);
    for (ll i = 1; i <= q; i += 1) {
        char type; cin >> type;
        if (type == '?') {
            is_asked[i] = true;
        } else if (type == '+') {
            ll u, v; cin >> u >> v;
            if (u > v) {
                swap(u, v);
            }
            assert(!time_last_added.count({u, v}));
            time_last_added[{u, v}] = i;
        } else {
            ll u, v; cin >> u >> v;
            if (u > v) {
                swap(u, v);
            }
            assert(time_last_added.count({u, v}));
            set_edge(set_edge, 0, 1, sz, time_last_added[{u, v}], i, {u, v});
            time_last_added.erase({u, v});
        }
    }
    for (const auto &[e, t] : time_last_added) {
        auto [u, v] = e;
        set_edge(set_edge, 0, 1, sz, time_last_added[{u, v}], sz, {u, v});
    }
    vector<ll> p(n+1);
    iota(p.begin(), p.end(), 0ll);
    vector<ll> dsusz(n+1, 1);
    auto find = [&] (auto f, ll u) -> ll {
        if (p[u] == u) {
            return u;
        }
        return f(f, p[u]);
    };
    stack<pair<ll&, ll>> stck;
    auto unite = [&] (ll u, ll v) -> void {
        u = find(find, u);
        v = find(find, v);
        if (dsusz[u] > dsusz[v]) {
            swap(u, v);
        }
        if (u == v) {
            return;
        }
        stck.push({p[u], p[u]});
        stck.push({dsusz[v], dsusz[v]});
        p[u] = v;
        dsusz[v] += dsusz[u];
    };
    auto dfs = [&] (auto f, ll V, ll tl, ll tr) -> void {
        ll kol = ll(stck.size());
        for (const auto &[u, v] : tree[V]) {
            unite(u, v);
        }
        if (tl == tr && is_asked[tl]) {
            // answer
            answer[tl] = n-stck.size()/2;
        }
        if (tl != tr) {
            ll tm = (tl + tr) >> 1;
            f(f, 2*V+1, tl, tm);
            f(f, 2*V+2, tm+1, tr);
        }
        while (stck.size() > kol) {
            stck.top().first = stck.top().second;
            stck.pop();
        }
    };
    dfs(dfs, 0, 1, sz);
    for (ll i = 1; i <= q; i += 1) {
        if (is_asked[i]) {
            cout << answer[i] << endl;
        }
    }
}

int main(int32_t argc, char* argv[]) {
    cout << fixed << setprecision(6);
    bool use_fast_io = true;
    for (int32_t i = 1; i < argc; i += 1) use_fast_io &= string(argv[i]) != "-local-no-fast-io";
    if (use_fast_io) ios::sync_with_stdio(false), cin.tie(0);
    ll tt = 1;
    while (tt--)
        solve();
    return 0;
}
