#include <bits/stdc++.h>

using namespace std;
#define endl "\n"
using ll = long long;
const ll INF = 1e18;
mt19937 mt(time(0));
void solve() {
    ll n, q; cin >> n >> q;
    vector<ll> p(n+1), sz(n+1, 1);
    iota(p.begin(), p.end(), 0ll);
    auto find = [&] (auto f, ll u) -> ll {
        if (p[u] != u) {
            return f(f, p[u]);
        }
        return p[u];
    };
    vector<pair<ll&, ll>> modns;
    stack<ll> move_to;
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
    for (ll i = 0; i < q; i += 1) {
        string type; cin >> type;
        if (type == "persist") {
            move_to.push({ll(modns.size())});
        } else if (type == "union") {
            ll u, v; cin >> u >> v;
            unite(u, v);
            cout << n-modns.size()/2 << endl;
        } else {
            while (ll(modns.size()) > move_to.top()) {
                modns.back().first = modns.back().second;
                modns.pop_back();
            }
            cout << n-modns.size()/2 << endl;
            move_to.pop();
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