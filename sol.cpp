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
//uniform_int_distribution<ll> distrib(1ll, 4ll);
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
    if (b < 0) {
        a = powm(a, MOD-2);
        b = -b;
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
struct shit {
    __int128 hash=0;
    ll pos=0;
};
void solve() {
//    s = "";
//    n = 1e3;
    cin >> n;
    cin >> s;
    const ll zero_pos = 500001;
    ll looking_r_pos = zero_pos;
    ll prefix_pos = zero_pos;
    ll overall_temp_pos = zero_pos;
    __int128 base = 1e6+1238;
    __int128 revbase = powm(base, MOD-2);
    unordered_map<__int128, ll> kol_r_by_value;
    __int128 overall_hash = 0;
    __int128 prefix_hash_rev = 0;
    __int128 suffix_hash = 0;
    fo(i, 0, n) {
        if (s[i] == '>') {
            overall_temp_pos += 1;
        } else if (s[i] == '<') {
            overall_temp_pos -= 1;
        } else if (s[i] == '+') {
            overall_hash = sum(overall_hash, powm(base, overall_temp_pos));
        } else {
            overall_hash = sub(overall_hash, powm(base, overall_temp_pos));
        }
    }
    kol_r_by_value[0] = 1; // добавляем длину r = 0
    ll tot = 0;
    roff(i, n-1, 0) {
        clog << "-----" << endl;
        clog << "длина l = " << i << endl;
        if (i+1 < n) {
            clog << "добавляем длину r = " << n-i-1 << endl;
            if (s[i+1] == '>') {
                suffix_hash = mul(suffix_hash, base);
            } else if (s[i+1] == '<') {
                suffix_hash = mul(suffix_hash, revbase);
            } else if (s[i+1] == '+') {
                suffix_hash = sum(suffix_hash, powm(base, zero_pos));
            } else {
                suffix_hash = sub(suffix_hash, powm(base, zero_pos));
            }
            kol_r_by_value[suffix_hash] += 1;
            clog << (ll)suffix_hash << "+= 1" << endl;
        }
        if (s[i] == '>') {
            prefix_pos += 1;
        } else if (s[i] == '<') {
            prefix_pos -= 1;
        } else if (s[i] == '+') {
            prefix_hash_rev = sub(prefix_hash_rev, powm(base, prefix_pos));
        } else {
            prefix_hash_rev = sum(prefix_hash_rev, powm(base, prefix_pos));
        }
        clog << (ll)prefix_hash_rev << " - (looking)" << endl;
//        clog << "looking for hash = " << (ll)suffix_hash << endl;
//        if (i-1 < 0 || s[i-1] != '>' && s[i-1] != '<') {
        // если последнее в l - это сдвиг то не считаем
        if (kol_r_by_value.contains(prefix_hash_rev)) {
//            clog << "l resulting pos" << looking_r_pos << endl;
//            clog << "+= " << kol_r_by_value[suffix_hash] << endl;
            tot += kol_r_by_value[prefix_hash_rev];
            clog << "+= " << kol_r_by_value[prefix_hash_rev] << endl;
            if (overall_hash != 0) {
                kol_r_by_value[prefix_hash_rev] = 0;
            }
        }

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