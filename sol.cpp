#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
using namespace std;
#define endl "\n"
using ll = long long;
const ll INF = 1e18;
mt19937 mt(time(0));
void solve() {
    ll n; cin >> n; ll m; cin >> m;
    vector<ll> p(n+1);
    iota(p.begin(), p.end(), 0ll);
    vector<ll> dsusz(n+1, 1);
    auto find = [&] (auto f, ll u) -> ll {
        if (p[u] == u) {
            return u;
        }
        return p[u]=f(f, p[u]);
    };
    auto unite = [&] (ll u, ll v) -> void {
        u = find(find, u);
        v = find(find, v);
        if (dsusz[u] > dsusz[v]) {
            swap(u, v);
        }
        if (u == v) {
            return;
        }
        p[u] = v;
        dsusz[v] += dsusz[u];
    };
    struct Edge {
        ll u;
        ll v;
        ll w;
    };
    vector<Edge> Es(m);
    for (ll i = 0; i < m; i += 1) {
        ll u, v, w; cin >> u >> v >> w;
        Es[i].u = u;
        Es[i].v = v;
        Es[i].w = w;
    }
    sort(Es.begin(), Es.end(), [&] (Edge a, Edge b) {
        if (a.w == b.w) {
            return make_pair(a.u, a.v) < make_pair(b.u, b.v);
        }
        return a.w < b.w;
    });
    ll su = 0;
    for (ll i = 0; i < m; i += 1) {
        if (find(find, Es[i].u) != find(find, Es[i].v)) {
            unite(Es[i].u, Es[i].v);
            su += Es[i].w;
        }
    }
    cout << su << endl;
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
