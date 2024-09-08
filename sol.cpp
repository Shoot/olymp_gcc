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
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math,trapv")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//uniform_int_distribution<ll> distrib(1ll, 200000ll);
constexpr ll MOD7 = 1e9 + 7;
constexpr ll N = 1e6;
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; fo(i, 0, n) cin >> a[i];
    vector<ll> a(n); fo(i, 0, n) cin >> a[i];
}
*/
ll __query__ (ll index, vector<ll> & tree)  {
    ll sum = 0;
    while (index > 0) {
        sum += tree[index];
        index -= index & -index;
    }
    return sum;
}

ll get(ll left, ll right, vector<ll> & tree) {
    return __query__(right+5, tree) - __query__(left+5 - 1, tree);
}

void add(ll index, ll inc, vector<ll> & tree) {
    index += 5;
    while (index < tree.size()) {
        tree[index] += inc;
        index += index & -index;
    }
}

void solve() {
    ll n; cin >> n;
    vector<ll> a(n);
    unordered_map<ll, bool> mp;
    fo(i, 0, n) {
        cin >> a[i];
        mp[a[i]] = true;
    }
    sort(all(a));
    bool good = false;
    fo(i, 0, n) {
        fo(j, i+1, n) {
            if ((a[i]+a[j])%2 == 0 && mp[(a[i]+a[j])/2]) {
                cout << "Yes" << endl;
                cout << a[i] << " " << a[j] << endl;
                cout << (a[i]+a[j])/2 << endl;
                good = true;
                break;
            }
        }
        if (good) break;
    }
    if (!good) {
        cout << "No" << endl;
        cout << a[n-1] << " " << a[0] << endl;
    }
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