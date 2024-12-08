#include <bits/stdc++.h>
using namespace std;
using vbo = vector<bool>;
using ll = long long;
using ull = unsigned long long;
using pll = pair<ll, ll>;
using ld = long double;
using qll = queue<ll>;
using vll = vector<ll>;
using vvll = vector<vector<ll>>;
using vvpll = vector<vector<pll>>;
using qld = queue<ld>;
using vld = vector<ld>;
using qpll = queue<pll>;
using vpll = vector<pll>;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
//ostream& endl(ostream& os) {
//    return os << '\n';
//}
//define all(xxx) xxx.begin(), xxx.end()
//define watch(xxx) cout << "value of " << #xxx << " is " << xxx << endl
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math,trapv")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distrib(0ll, 10ll);
//constexpr ll MOD = 819356875157278019ll;
constexpr ll MOD = 1e9+7;
ll powm(ll best, ll b) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*best) % MOD;
        b >>= 1;
        best = (best*best) % MOD;
    }
    return d;
}
ll powm(ll best, ll b, ll MODD) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*best) % MODD;
        b >>= 1;
        best = (best*best) % MODD;
    }
    return d;
}
ll poww(ll best, ll b) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*best);
        b >>= 1;
        best = (best*best);
    }
    return d;
}
ld poww(ld best, ll b) {
    assert(b >= 0);
    ld d = 1;
    while (b) {
        if (b&1) d = (d*best);
        b >>= 1;
        best = (best*best);
    }
    return d;
}
ll mul(ll best, ll b) {
    return (best*b)%MOD;
}
ll mul(ll best, ll b, ll MODD) {
    return (best*b)%MODD;
}
ll sum(ll best, ll b) {
    return (best+b)%MOD;
}
ll sum(ll best, ll b, ll MODD) {
    return (best+b)%MODD;
}
ll sub(ll best, ll b) {
    return (best-(b%MOD)+MOD)%MOD;
}
ll sub(ll best, ll b, ll MODD) {
    return (best-(b%MODD)+MODD)%MODD;
}
void solve() {
    struct Node {
        ll su = 0;
        ll mx = -1e18;
        ll mn = 1e18;
        ll push_assign = -1;
    };
    ll n, q; cin >> n >> q;
    vector<Node> tree(4*n+10);
    vll a(n);
    for (auto &x : a) cin >> x;
    auto merge = [&] (Node &into, const Node& from) -> void {
        into.su += from.su;
        into.mn = min(into.mn, from.mn);
        into.mx = max(into.mx, from.mx);
        assert(into.push_assign == -1);
    };
    auto build = [&] (auto f, ll v, ll tl, ll tr) -> void {
        if (tl == tr) {
            tree[v].su = a[tl];
            tree[v].mx = a[tl];
            tree[v].mn = a[tl];
            return;
        }
        ll tm = (tl + tr) >> 1;
        f(f, 2*v+1, tl, tm);
        f(f, 2*v+2, tm+1, tr);
        merge(tree[v], tree[2*v+1]);
        merge(tree[v], tree[2*v+2]);
    };
    build(build, 0, 0, n-1);
    auto push = [&] (ll v, ll tl, ll tr) -> void {
        if (tree[v].push_assign != -1) {
            assert(tree[v].push_assign == tree[v].mx);
            assert(tree[v].push_assign == tree[v].mn);
            ll val = tree[v].push_assign;
            tree[v].push_assign = -1;
            tree[2*v+1].push_assign = val;
            tree[2*v+2].push_assign = val;
            ll tm = (tl + tr) >> 1;
            ll leftsz = tm-tl+1;
            assert(leftsz > 0);
            ll rightsz = tr-(tm+1)+1;
            assert(rightsz > 0);
            tree[2*v+1].mn = val;
            tree[2*v+1].mx = val;
            tree[2*v+1].su = leftsz*val;
            tree[2*v+2].mn = val;
            tree[2*v+2].mx = val;
            tree[2*v+2].su = rightsz*val;
        }
    };
    auto assign_segment = [&] (auto f, ll v, ll tl, ll tr, ll l, ll r, ll val) -> void {
        if (tl == l && tr == r) {
            ll sz = tr-tl+1;
            tree[v].su = sz*val;
            tree[v].mx = val;
            tree[v].mn = val;
            tree[v].push_assign = val;
            return;
        }
        push(v, tl, tr);
        ll tm = (tl + tr) >> 1;
        if (l <= tm) {
            f(f, 2*v+1, tl, tm, l, min(r, tm), val);
        }
        if (r >= tm+1) {
            f(f, 2*v+2, tm+1, tr, max(l, tm+1), r, val);
        }
        tree[v] = Node();
        merge(tree[v], tree[2*v+1]);
        merge(tree[v], tree[2*v+2]);
    };
    auto get_segment = [&] (auto f, ll v, ll tl, ll tr, ll l, ll r) -> Node {
        if (tl == l && tr == r) {
            return tree[v];
        }
        push(v, tl, tr);
        ll tm = (tl + tr) >> 1;
        auto ret = Node();
        if (l <= tm) {
            merge(ret, f(f, 2*v+1, tl, tm, l, min(r, tm)));
        }
        if (r >= tm+1) {
            merge(ret, f(f, 2*v+2, tm+1, tr, max(l, tm+1), r));
        }
        return ret;
    };
    auto modulo = [&] (auto f, ll v, ll tl, ll tr, ll l, ll r, ll mod) -> void {
        if (tree[v].mx < mod) { // break condition
            return;
        }
        if (l == tl && r == tr && tree[v].mx == tree[v].mn) { // tag
            ll nwval = tree[v].mx % mod;
            assign_segment(assign_segment, 0, 0, n-1, l, r, nwval);
            ll sz = tr - tl + 1;
            assert(tree[v].su == sz*nwval);
            assert(tree[v].mx == nwval);
            assert(tree[v].mn == nwval);
            assert(tree[v].push_assign == nwval);
            return;
        }
        push(v, tl, tr);
        ll tm = (tl + tr) >> 1;
        if (l <= tm) {
            f(f, 2*v+1, tl, tm, l, min(r, tm), mod);
        }
        if (r >= tm+1) {
            f(f, 2*v+2, tm+1, tr, max(l, tm+1), r, mod);
        }
        tree[v] = Node();
        merge(tree[v], tree[2*v+1]);
        merge(tree[v], tree[2*v+2]);
    };
    for (ll i = 0; i < q; i += 1) {
        ll tp; cin >> tp;
        if (tp == 1) {
            ll l, r; cin >> l >> r; l -= 1; r -= 1;
            cout << get_segment(get_segment, 0, 0, n-1, l, r).su << endl;
        }
        if (tp == 2) {
            ll l, r, mod;
            cin >> l >> r >> mod;
            l -= 1; r -= 1;
            modulo(modulo, 0, 0, n-1, l, r, mod);
        }
        if (tp == 3) {
            ll pos, val;
            cin >> pos >> val;
            pos -= 1;
            assign_segment(assign_segment, 0, 0, n-1, pos, pos, val);
        }
    }
}

int32_t main(int32_t argc, char* argv[]) {
//    ifstream cin("distance.in");
//    ofstream cout("distance.out");
    cout << fixed << setprecision(17);
    bool use_fast_io = true;
    for (int32_t i = 1; i < argc; ++i) {
        if (string(argv[i]) == "-local-no-fast-io") {
            use_fast_io = false;
//            cout << "No fastIO" << endl;
            break;
        }
    }
    if (use_fast_io) {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        cerr.tie(nullptr);
        clog.tie(nullptr);
    }
    ll tt = 1;
//    cin >> tt;

    while (tt--) {
        solve();
    }
    return 0;
}