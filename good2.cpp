#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using ld = long double;
using qll = queue<ll>;
using vll = vector<ll>;
using qld = queue<ld>;
using vld = vector<ld>;
using qpll = queue<pll>;
using vpll = vector<pll>;
ostream& endl(ostream& os) {
    return os << '\n';
}
#ifdef LOCAL
#include <algo/debug.h>
#else
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math,trapv")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distrib(2ll, 10ll);
constexpr ll MOD = 1e9+7;
void in(vector<ll> & a) {
    for (auto & x : a) cin >> x;
}
void in(vector<ll> & a, ll l, ll r) {
    for (ll i=l; i < r; i+=1) {
        cin >> a[i];
    }
}
void inn(vector<ll> & a, ll l, ll rr) {
    for (ll i=l; i <= rr; i+=1) {
        cin >> a[i];
    }
}
ll powm(ll a, ll b) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*a) % MOD;
        b >>= 1;
        a = (a*a) % MOD;
    }
    return d;
}
ll poww(ll a, ll b) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*a);
        b >>= 1;
        a = (a*a);
    }
    return d;
}
ll mul(ll a, ll b) {
    return (a*b)%MOD;
}
ll sum(ll a, ll b) {
    return (a+b)%MOD;
}
ll sub(ll a, ll b) {
    return (a-b+100*MOD)%MOD;
}
ll fj0dsq983gf8(ll index, vector<ll> & tree)  {
    index += 1;
    ll sum = 0;
    while (index > 0) {
        sum += tree[index-1];
        index -= index & -index;
    }
    return sum;
} // zero-indexed!!!
ll get_sum_ft(ll left, ll right, vector<ll> & tree) {
    ll n = (ll)tree.size();
    if (!(left <= right)) return 0;
    assert(left <= right);
    if (right >= n) {
        clog << "FENWICK ALERT: R >= tree.size() (IT'S ZERO INDEXED !!!)" << endl;
        right = n-1;
    }
    ll ans = fj0dsq983gf8(right, tree);
    if (left-1 >= 0) {
        ans -= fj0dsq983gf8(left - 1, tree);
    }
    return ans;
} // zero-indexed!!!
void inc_ft(ll index, ll inc, vector<ll> & tree) {
    ll n = (ll)tree.size();
    assert(index >= 0);
    assert(index < n);
    index += 1;
    while (index < n) {
        tree[index] += inc;
        index += index & -index;
    }
} // zero-indexed!!!
void build_ft(vector<ll> & a, vector<ll> & tree) {
    ll n = (ll)tree.size();
    assert(tree.size() == a.size());
    for (ll i = 0; i < n; i++) {
        tree[i] += a[i];
        ll r = i | (i + 1);
        if (r < n) tree[r] += tree[i];
    }
} // zero-indexed!!!
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; for (ll i=0; i < n; i+=1) cin >> a[i];
    vector<ll> a(n); for (ll i=0; i < n; i+=1) cin >> a[i];
}
*/
const ll N = 3e5+100;
void find_sol(ll a, ll b, ll & x, ll & y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return;
    }
    find_sol(b, a%b, x, y);
    x -= (a/b)*y;
    swap(x, y);
}
void solve() {
}

int32_t main(int32_t argc, char* argv[]) {
    bool use_fast_io = true;
    for (int32_t i = 1; i < argc; ++i)
        if (string(argv[i]) == "-local-no-fast-io") {
            use_fast_io = false;
//            cout << "No fastIO" << endl;
            break;
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
