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
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//uniform_int_distribution<ll> distrib(1ll, 200000ll);
//constexpr ll MOD = 1e9 + 7;
constexpr __int128 MOD = 957363431467152001;
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; fo(i, 0, n) cin >> a[i];
    vector<ll> a(n); fo(i, 0, n) cin >> a[i];
}
*/
//namespace std {
//    template <>
//    struct hash<__int128> {
//        std::size_t operator()(__int128 value) const {
//            uint64_t high = static_cast<uint64_t>(value >> 64);
//            uint64_t low = static_cast<uint64_t>(value);
//            return std::hash<uint64_t>()(high) ^ (std::hash<uint64_t>()(low) << 1);
//        }
//    };
//}
__int128 powm(__int128 a, __int128 b){
    __int128 d = 1;
    while(b){
        if (b&1) d = (d*a) % MOD;
        b >>= 1;
        a = (a*a) % MOD;
    }
    return d;
}
__int128 mul(__int128 a, __int128 b){
    return ((a*b)%MOD);
}

void solve() {
    ll n;
    cin >> n;
    string s;
    cin >> s;
    __int128 pos = 250001;
    __int128 base = 250001;
    __int128 revbase = powm(base, MOD-2);
    __int128 looking_r = 0;
    __int128 right_to_left = 0;
    fo(i, 0, n) {
        if (s[i] == '>') {
            pos += 1;
        } else if (s[i] == '<') {
            pos -= 1;
        } else if (s[i] == '+') {
            looking_r = (looking_r + mul(1, powm(base, pos)))%MOD;
//            right_to_left = (right_to_left + mul(1, powm(base, pos)))%MOD;
        } else {
            looking_r = (looking_r - mul(1, powm(base, pos)))%MOD;
//            right_to_left = (right_to_left - mul(1, powm(base, pos)))%MOD;
        }
    }
    unordered_map<__int128, ll> kol_r_by_value;
    __int128 curr_r = 0;
    ll tot = 0;
    roff(i, n-1, 0) {
        // отменяем для looking_r
        if (s[i] == '>') {
            pos -= 1;
            curr_r = mul(curr_r, base);
        } else if (s[i] == '<') {
            pos += 1;
            curr_r = mul(curr_r, revbase);
        } else if (s[i] == '+') {
            looking_r = (looking_r - mul(1, powm(base, pos)))%MOD;
            curr_r = (curr_r + mul(1, powm(base, 250001)))%MOD;
        } else {
            looking_r = (looking_r + mul(1, powm(base, pos)))%MOD;
            curr_r = (curr_r - mul(1, powm(base, 250001)))%MOD;
        }
        kol_r_by_value[curr_r] += 1;
        if (kol_r_by_value.contains(looking_r)) tot += kol_r_by_value[looking_r];
    }
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