#include <bits/stdc++.h>

using namespace std;
#define endl "\n"
using ll = long long;
const ll INF = 1e18;
mt19937 mt(time(0));
void solve() {
    ll n, q; cin >> n >> q;
    vector<vector<ll>> sm(n+1);
    vector<vector<ll>> revsm(n+1);
    vector<ll> par(n+1);
    vector<ll> ans(q+1);
    vector<vector<pair<ll,ll>>> ask(q+1);
    struct Q {
        ll type;
        ll x;
        ll y;
        ll pa;
    };
    vector<Q> Qs;
    for (ll ii = 0; ii < q; ii += 1) {
        ll type; cin >> type;
        Qs.push_back({type});
        if (type == 1) {
            ll x, y; cin >> x >> y;
            Qs.back().x = x;
            Qs.back().y = y;
            sm[y].push_back(x);
            revsm[x].push_back(y);
            clog << y << " -> " << x << endl;
        } else if (type == 2) {
            ll x; cin >> x;
            Qs.back().x = x;
        } else {
            ll x, pa; cin >> x >> pa;
            Qs.back().x = x;
            Qs.back().pa = pa;
            ask[pa].push_back({ii+1, x});
        }
    }
    ll ii = 0;
    ll curr_pack = 0;
    vector<ll> p(n+1), sz(n+1, 1);
    iota(p.begin(), p.end(), 0ll);
    auto find = [&] (auto f, ll u) -> ll {
        if (p[u] != u) {
            p[u] = f(f, p[u]);
        }
        return p[u];
    };
    auto unite = [&] (ll u, ll v) -> void {
        u = find(find, u);
        v = find(find, v);
        if (sz[u] > sz[v]) {
            swap(u, v);
        }
        sz[v] += sz[u];
        p[u] = v;
    };
    vector<bool> seen(n+1);
    vector<ll> tin(n+1), tout(n+1);
    ll t = 0;
    auto dfs = [&] (auto f, ll v) -> void {
        seen[v] = true;
        tin[v] = ++t;
        for (const auto &x : sm[v]) {
            if (!seen[x]) {
                seen[x] = true;
                f(f, x);
            }
        }
        tout[v] = ++t;
    };
    for (ll i = 1; i <= n; i += 1) {
        if (revsm[i].empty()) {
            dfs(dfs, i);
//            cout << i << ":)" << endl;
        }
    }
    auto ischild = [&] (ll u, ll v) -> bool {
        return tin[u] >= tin[v] && tout[u] <= tout[v];
    };
    for (const auto &[type, x, y, pa] : Qs) {
        if (type == 1) {
            unite(x, y);
        } else if (type == 2) {
            curr_pack += 1;
            for (const auto &[idx, v] : ask[curr_pack]) {
                if (find(find, v) == find(find, x) && ischild(x, /*of*/ v)) {
                    ans[idx] = 1;
                } else {
                    ans[idx] = -1;
                }
            }
        }
    }
    for (ll i = 1; i <= q; i += 1) {
        if (ans[i] == 1) {
            cout << "YES" << endl;
        } else if (ans[i] == -1) {
            cout << "NO" << endl;
        }
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