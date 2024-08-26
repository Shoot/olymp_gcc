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
uniform_int_distribution<ll> distrib(100, 900);
constexpr ll N = (ll)(2e4);
constexpr ll MOD = 998244353;
ll pow(ll a, ll b){
    ll ans = 1;
    while(b){
        if (b&1) ans = (ans*a) % MOD;
        b >>= 1;
        a = (a*a) % MOD;
    }
    return ans;
}
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; fo(i, 0, n) cin >> a[i];
    vector<ll> a(n); fo(i, 0, n) cin >> a[i];
}
*/
map<ll, ll> prime_factors(ll n) {
    map<ll, ll> factors;
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            ++factors[i];
            n /= i;
        }
    }
    if (n > 1) factors[n]++; // мб простое
    return factors;
}

ll div2(ll a) {
    return (a*(MOD+1)/2)%MOD;
}

void solve () {
    ll a, b; cin >> a >> b;
    ll ans = b;
    for (auto [divisor, powweerr] : prime_factors(a)) {
        ans = (ans*(b * powweerr + 1))%MOD;
    }
    // b*(e_1+1)*(e_2+1)*...*(e_n+1)/2
    cout << (((ans)%MOD)*powmod)%MOD << endl;
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
//    fo(i, 0, 1) skip.insert(distrib(rng));
//    cin >> tt;
    while (tt--) solve();
    return 0;
}