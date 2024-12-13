#include <bits/stdc++.h>

using namespace std;
using ll = long long;
void solve () {
    ll n; cin >> n;
    vector<vector<ll>> up(20, vector<ll>(n+1));
    vector<ll> h(n+1);
    auto get_lca = [&] (ll u, ll v) -> ll {

        // нужно узнать высоту
        assert(up[19][u] == up[19][v]);
        if (u == v) {
            return u;
        }
        for (ll bt = 19; bt >= 0; bt -= 1) {
            if (up[bt][u] != up[bt][v]) {
                v = up[bt][v];
                u = up[bt][u];
            }
        }
        assert(u != v);
        u = up[0][u];
        v = up[0][v];
        assert(u == v);
        return u;
    };
    auto link = [&] (ll what, ll to_what) -> ll {

    };
}
int main()
{
    solve();
    return 0;
}