#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef long double ld;
typedef vector<ll> vll;
typedef vector<pll> vpll;
typedef vector<ld> vld;
typedef queue<ll> qll;
typedef queue<ld> qld;
typedef queue<pll> qpll;
#define all(value) value.begin(), value.end()
#define all(value) value.begin(), value.end()
#define fo(XX, X, fi) for(ll XX = X; XX < fi; XX++)
#define forr(XX, X, fi) for(ll XX = X; XX <= fi; XX++)
#define rrof(XX, X, fi) for(ll XX = X; XX >= fi; XX--)
#define roff(XX, X, fi) for(ll XX = X; XX >= fi; XX--)
#define of(XX, X, fi) for(ll XX = X; XX > fi; XX--)
#define ro(XX, X, fi) for(ll XX = X; XX > fi; XX--)
#define yes(XX) (XX ? "YES" : "NO")
#define endll endl
#define endl '\n'
#ifdef LOCAL
#include <algo/debug.h>
#else
#define debug(...) 68
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math,trapv")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distrib(2ll, 10ll);
constexpr ll MOD = 1e9+7;
void in(vector<ll> & a) {
    for(auto & x: a) cin >> x;
}
void in(vector<ll> & a, ll l, ll r) {
    fo(i, l, r) {
        cin >> a[i];
    }
}
void inn(vector<ll> & a, ll l, ll rr) {
    forr(i, l, rr) {
        cin >> a[i];
    }
}
ll powm(ll a, ll b){
    assert(b >= 0);
    ll d = 1;
    while(b){
        if (b&1) d = (d*a) % MOD;
        b >>= 1;
        a = (a*a) % MOD;
    }
    return d;
}
ll poww(ll a, ll b){
    assert(b >= 0);
    ll d = 1;
    while(b){
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
    ll a[n]; fo(i, 0, n) cin >> a[i];
    vector<ll> a(n); fo(i, 0, n) cin >> a[i];
}
*/
vector<ll> res(1e6, 666);
vector<vpll> increments (1e6);
bitset<1000000ll> seen;
vector<vll> sm(1e6);
vll tr (1e6, 0);
void dfs(ll h, ll v, ll curr) {
    for(auto const &[inc, depth]: increments[v]) {
        tr[h] += inc;
        tr[h+depth+1] -= inc;
    }
    curr += tr[h];
    res[v] = curr;
    for(auto const &child: sm[v]) {
        if (!seen[child]) {
            seen[child] = true;
            dfs(h+1, child, curr);
        }
    }
    for(auto const &[inc, depth]: increments[v]) {
        tr[h] -= inc;
        tr[h+depth+1] += inc;
    }
}
void solve() {
    ll n;
    cin >> n;
    fo(i, 0, n-1) {
        ll x, y; cin >> x >> y;
        x -= 1;
        y -= 1;
        sm[x].push_back(y);
        sm[y].push_back(x);
    }
    ll q_n;
    cin >> q_n;
    fo(i, 0, q_n) {
        ll v, increment, depth;
        cin >> v >> depth >> increment;
        v -= 1;
        increments[v].push_back(make_pair(increment, min(400000ll, depth)));
    }
    // PODVESIM ZA 0
    seen[0] = true;
    dfs(0, 0, 0);
    fo(v, 0, n) cout << res[v] << ' ';
    cout << endl;
}

int32_t main (int32_t argc, char* argv[]) {
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