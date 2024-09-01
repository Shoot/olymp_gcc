#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define all(value) value.begin(), value.end()
#define fo(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x < fi; x++)
#define forr(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x <= fi; x++)
#define rrof(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x >= fi; x--)
#define roff(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x >= fi; x--)
#define of(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x > fi; x--)
#define ro(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x > fi; x--)
#define yes(x) (x ? "YES" : "NO")
#define endl '\n'
#ifdef LOCAL
#include <algo/debug.h>
#else
#define debug(...) 68
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distrib(1, 11);
constexpr ll N = (ll)(1e15);
constexpr ll MOD99 = 998244353;
constexpr ll MOD7 = 1e9 + 7;
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; fo(i, 0, n) cin >> a[i];
    vector<ll> a(n); fo(i, 0, n) cin >> a[i];
}
*/
void add_one(ll x, ll y, unordered_map<ll, unordered_map<ll, ll>> & bit) {
    for (; x <= N; x += (x & (-x))) {
        for (ll i = y; i <= N; i += (i & (-i))) { bit[x][i] += 1ll; }
    }
}
ll query(ll x1, ll y1, ll x2, ll y2, unordered_map<ll, unordered_map<ll, ll>> & bit) {
    ll ans = 0;
    for (ll i = x2; i; i -= (i & (-i))) {
        for (ll j = y2; j; j -= (j & (-j))) {
            if (bit.contains(i) && bit[i].contains(j))
            ans += bit[i][j];
        }
    }
    for (ll i = x2; i; i -= (i & (-i))) {
        for (ll j = y1 - 1; j; j -= (j & (-j))) {
            if (bit.contains(i) && bit[i].contains(j))
            ans -= bit[i][j];
        }
    }
    for (ll i = x1 - 1; i; i -= (i & (-i))) {
        for (ll j = y2; j; j -= (j & (-j))) {
            if (bit.contains(i) && bit[i].contains(j))
            ans -= bit[i][j];
        }
    }
    for (ll i = x1 - 1; i; i -= (i & (-i))) {
        for (ll j = y1 - 1; j; j -= (j & (-j))) {
            if (bit.contains(i) && bit[i].contains(j))
            ans += bit[i][j];
        }
    }
    return ans;
}
ll tot=0;
ll n, x;
void compute(ll l, ll r, vector<ll> & a, vector<ll> & b) {
    if (l == r) {
        ll single_good = (a[l]+b[l] <= x);
        clog << "l=r=" << l << ", adding " << single_good << endl;
        tot += single_good;
        return;
    }
    ll sz = (r-l+1)/2;
    ll mid = (l+r) >> 1;
    vector<ll> su_l (sz, N);
    vector<ll> su_r (sz, N);
    vector<ll> mi_l (sz);
    vector<ll> mi_r (sz);
    unordered_map<ll, unordered_map<ll, ll>> mp_l;
    unordered_map<ll, unordered_map<ll, ll>> mp_r;
    ll su = 0;
    ll mini = N;
    fo(i, 0, sz) {
        su += b[mid-i];
        mini = min(mini, a[mid-i]);
        if (su >= N) {
            break;
        }
        clog << "adding to mp_l: " << su << "," << mini << endl;
        add_one(mini, su, mp_l);
        su_l[i] = su;
        mi_l[i] = mini;
    }
    su = 0;
    mini = N;
    fo(i, 0, sz) {
        su += b[mid+1+i];
        mini = min(mini, a[mid+1+i]);
        if (su >= N) {
            break;
        }
        clog << "adding to mp_r: " << su << "," << mini << endl;
        add_one(mini, su, mp_r);
        su_r[i] = su;
        mi_r[i] = mini;
    }
    clog << "su_l: ";
    for (ll j: su_l) {
        clog << j << ' ';
    }
    clog << endl;
    clog << "mi_l: ";
    for (ll j: mi_l) {
        clog << j << ' ';
    }
    clog << endl;
    clog << "su_r: ";
    for (ll j: su_r) {
        clog << j << ' ';
    }
    clog << endl;
    clog << "mi_r: ";
    for (ll j: mi_r) {
        clog << j << ' ';
    }
    clog << endl;
    fo(i, 0, sz) {
        ll minimum = mi_l[i];
        ll summa = su_l[i];
        clog << minimum << "," << summa;
        ll from_here = query(minimum, 0, N, x-summa-minimum, mp_r);
        clog << " (l -> r) from " << i << ": " << from_here << endl;
        tot += from_here;
    }
    fo(i, 0, sz) {
        ll minimum = mi_r[i];
        ll summa = su_r[i];
        ll from_here = query(minimum+1, 0, N, x-summa-minimum, mp_l);
        clog << minimum << "," << summa;
        clog << " (r -> l) from " << i << ": " << from_here << endl;
        tot += from_here;
    }
    compute(l, mid, a, b);
    compute(mid+1, r, a, b);
}
void solve() {
    cin >> n >> x;
    ll oldn = n;
    forr(i, 0, 20) {
        if ((1 << i) >= n) {
            n = (1 << i);
            break;
        }
    }
    assert((n & (n-1)) == 0);
    vector<ll> a(n, N);
    vector<ll> b(n, N);
    fo(i, 0, oldn) {
        cin >> a[i];
        assert(a[i] > 0);
    }
    fo(i, 0, oldn) {
        cin >> b[i];
        assert(b[i] > 0);
    }
    compute(0, n-1, a, b);
    cout << tot << endl;
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
    while (tt--) solve();
    return 0;
}