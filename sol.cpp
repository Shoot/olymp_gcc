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
uniform_int_distribution<ll> distrib(1ll, 4ll);
//constexpr ll MOD = 1e9 + 7;
constexpr __int128 MOD = 85664078284794307;
/*\
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; fo(i, 0, n) cin >> a[i];
    vector<ll> a(n); fo(i, 0, n) cin >> a[i];
}
*/
namespace std {
    template <>
    struct hash<__int128> {
        std::size_t operator()(__int128 value) const {
            uint64_t high = static_cast<uint64_t>(value >> 64);
            uint64_t low = static_cast<uint64_t>(value);
            return std::hash<uint64_t>()(high) ^ (std::hash<uint64_t>()(low) << 1);
        }
    };
}
__int128 powm(__int128 a, __int128 b){
    if (b < 0) {
        b = -b;
        a = powm(a, MOD-2);
    }
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
__int128 sum(__int128 a, __int128 b){
    return ((a+b)%MOD);
}
__int128 sub(__int128 a, __int128 b){
    return ((a-b+10*MOD)%MOD);
}
ll n;
string s;
ll brute() {
    ll OG = 0;
    vector<ll> basic (100, 0);
    ll pos = 50;
    fo(i, 0, n) {
        if (s[i] == '+') {
            basic[pos] += 1;
        } else if (s[i] == '-') {
            basic[pos] -= 1;
        } else if (s[i] == '<') {
            pos -= 1;
        } else {
            pos += 1;
        }
    }
    fo(i, 0, n) {
        vector<ll> otr(100, 0);
        ll posotr = 50;
        fo(j, i, n) {
            if (s[j] == '+') {
                otr[posotr] += 1;
            } else if (s[j] == '-') {
                otr[posotr] -= 1;
            } else if (s[j] == '<') {
                posotr -= 1;
            } else {
                posotr += 1;
            }
            OG += otr == basic;
        }
    }
    return OG;
}
void solve() {
    s = "";
    n = 45;
    cin >> n;
    cin >> s;
    const ll zero_pos = 500001;
    ll temp_pos_for_calculating_desired_hash = zero_pos;
    __int128 base = 1e6+1238;
    __int128 desired_hash = 0;
    fo(i, 0, n) {
        if (s[i] == '>') {
            temp_pos_for_calculating_desired_hash += 1;
        } else if (s[i] == '<') {
            temp_pos_for_calculating_desired_hash -= 1;
        } else if (s[i] == '+') {
            desired_hash = sum(desired_hash, powm(base, temp_pos_for_calculating_desired_hash));
        } else {
            desired_hash = sub(desired_hash, powm(base, temp_pos_for_calculating_desired_hash));
        }
    }
    __int128 current_hash = 0;
    ll curr_pos = zero_pos;
    ll tot = 0;
    map<__int128, ll> mp;
    mp[desired_hash] = 1;
    fo(i, 0, n) {
        if (s[i] == '>') {
            curr_pos += 1;
        } else if (s[i] == '<') {
            curr_pos -= 1;
        } else if (s[i] == '+') {
            current_hash = sum(current_hash, powm(base, curr_pos));
        } else {
            current_hash = sub(current_hash, powm(base, curr_pos));
        }
        tot += mp[current_hash];
        mp[sum(current_hash, mul(desired_hash, powm(base, curr_pos-zero_pos)))] += 1;
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