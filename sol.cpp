#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using vll = vector<long long>;
void solve() {
    ll q; cin >> q;
    const ll INF = 1e18;
    const ll N = 1e9+10;
    struct Node {
        ll first_zero;
    };
    map<ll, Node> mp;
    map<ll, ll> a;
    auto merge = [&] (Node &one, const Node &another) -> void {
        one.first_zero = min(one.first_zero, another.first_zero);
    };
    auto set_point = [&] (auto f, ll v, ll tl, ll tr, ll pos, ll val) -> void {
        Node ss = {INF};
        mp[v] = ss;
        if (tl == tr) {
            a[pos] = val;
            if (val == 0) {
                mp[v].first_zero = pos;
            } else {
                mp[v].first_zero = INF;
            }
            return;
        }
        ll tm = (tl + tr) >> 1;
        if (pos <= tm) {
            f(f, 2*v+1, tl, tm, pos, val);
        }
        if (pos >= tm+1) {
            f(f, 2*v+2, tm+1, tr, pos, val);
        }
        if (mp.count(2*v+1)) mp[v].first_zero = min(mp[v].first_zero, mp[2*v+1].first_zero);
        else mp[v].first_zero = min(mp[v].first_zero, tl);
        if (mp.count(2*v+2)) mp[v].first_zero = min(mp[v].first_zero, mp[2*v+2].first_zero);
        else mp[v].first_zero = min(mp[v].first_zero, tm+1);
    };
    auto get_segment = [&] (auto f, ll v, ll tl, ll tr, ll l, ll r) -> Node {
        if (tl == l && tr == r) {
            Node ss = {tl};
            if (!mp.count(v)) {
                mp[v] = ss;
            }
            return mp[v];
        }
        ll tm = (tl + tr) >> 1;
        Node x = {INF};
        if (l <= tm) {
            auto t = f(f, 2*v+1, tl, tm, l, min(r, tm));
            merge(x, t);
        }
        if (r >= tm+1) {
            auto t = f(f, 2*v+2, tm+1, tr, max(l, tm+1), r);
            merge(x, t);
        }
        return x;
    };
    for (ll i = 0; i < q; i += 1) {
        ll x; cin >> x;
        if (x < 0) {
            set_point(set_point, 0, 1, N, -x, 0);
        } else {
            auto ans = get_segment(get_segment, 0, 1, N, x, N);
            cout << ans.first_zero << "\n";
            set_point(set_point, 0, 1, N, ans.first_zero, 1);
        }
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}