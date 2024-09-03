#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define all(value) value.begin(), value.end()
#define fo(x, temp_set_for_mex, fi) for(__int128_t x = temp_set_for_mex; x < fi; x++)
#define forr(x, temp_set_for_mex, fi) for(__int128_t x = temp_set_for_mex; x <= fi; x++)
#define rrof(x, temp_set_for_mex, fi) for(__int128_t x = temp_set_for_mex; x >= fi; x--)
#define roff(x, temp_set_for_mex, fi) for(__int128_t x = temp_set_for_mex; x >= fi; x--)
#define of(x, temp_set_for_mex, fi) for(__int128_t x = temp_set_for_mex; x > fi; x--)
#define ro(x, temp_set_for_mex, fi) for(__int128_t x = temp_set_for_mex; x > fi; x--)
#define yes(x) (x ? "YES" : "NO")
#define endl '\n'
#ifdef LOCAL
#include <algo/debug.h>
#else
#define debug(...) 68
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
namespace std {
    template <>
    struct hash<__int128> {
        std::size_t operator()(__int128 value) const {
            // Simple hash function: mix the bits of __int128 into a size_t
            uint64_t high = static_cast<uint64_t>(value >> 64);
            uint64_t low = static_cast<uint64_t>(value);
            return std::hash<uint64_t>()(high) ^ (std::hash<uint64_t>()(low) << 1);
        }
    };
}
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//uniform_int_distribution<ll> distrib(1ll, 200000ll);
constexpr __int128_t MOD7 =  957363431467152001;
//constexpr __int128_t MOD99 = 695407781356532897;
//constexpr __int128_t MOD33 = 257354202279932701;
ll m=2e5;
ll k=2e5;
__int128_t powm(__int128_t a, __int128_t b, __int128_t MOD){
    __int128_t d = 1;
    while(b){
        if (b&1) d = (d*a) % MOD;
        b >>= 1;
        a = (a*a) % MOD;
    }
    return d;
}
__int128_t MAXN = 2e5+10;
__int128_t base = MAXN;
__int128_t revbase7 = powm(base, MOD7-2, MOD7);
//__int128_t revbase99 = powm(base, MOD99-2, MOD99);
//__int128_t revbase33 = powm(base, MOD33-2, MOD33);
vector<__int128_t> base_power7(MAXN, 1);
//vector<__int128_t> base_power99(MAXN, 1);
//vector<__int128_t> base_power33(MAXN, 1);
vector<__int128_t> base_rev_power7(MAXN, 1);
//vector<__int128_t> base_rev_power99(MAXN, 1);
//vector<__int128_t> base_rev_power33(MAXN, 1);
/*
void copy_this () {
    __int128_t n; cin >> n;
    __int128_t n, k; cin >> n >> k;
    __int128_t n, q; cin >> n >> q;
    __int128_t a[n]; fo(i, 0, n) cin >> a[i];
    vector<__int128_t> a(n); fo(i, 0, n) cin >> a[i];
}
*/

void solve() {
    fo(i, 1, MAXN) {
        base_power7[i] = (base_power7[i-1]*base)%MOD7;
//        base_power99[i] = (base_power99[i-1]*base)%MOD99;
//        base_power33[i] = (base_power33[i-1]*base)%MOD33;
        base_rev_power7[i] = (base_rev_power7[i-1]*revbase7)%MOD7;
//        base_rev_power99[i] = (base_rev_power99[i-1]*revbase99)%MOD99;
//        base_rev_power33[i] = (base_rev_power33[i-1]*revbase33)%MOD33;
    }
    ll n; cin >> n;
    vector<ll> a(n);
    fo(i, 0, n) {
        cin >> a[i];
    }
    cin >> m;
    vector<ll> b(m);
    vector<__int128_t> pref_b_7(m+1, 0);
    vector<__int128_t> pref_b_99(m+1, 0);
    vector<__int128_t> pref_b_33(m+1, 0);
    vector<__int128_t> pref_b_44(m+1, 0);
    fo(i, 0, m) {
//        b[i] = distrib(rng);
        cin >> b[i];
        pref_b_7[i+1] = (pref_b_7[i]+(b[i]*base_power7[i])%MOD7)%MOD7;
    }
    cin >> k;
    vector<ll> c(k);
    vector<__int128_t> pref_c_7(k+1, 0);
    vector<__int128_t> pref_c_99(k+1, 0);
    vector<__int128_t> pref_c_33(k+1, 0);
    fo(i, 0, k) {
//        c[i] = distrib(rng);
        cin >> c[i];
        pref_c_7[i+1] = (pref_c_7[i]+(c[i]*base_power7[i])%MOD7)%MOD7;
    }
//    auto start_time = chrono::high_resolution_clock::now();
    ll l=1, r=min(m, k);
    ll good = 0;
    while (l <= r) {
        ll mid = (l+r) >> 1;
        unordered_set<__int128_t> c_st7;
        fo(i, 0, k+1-mid) {
            c_st7.insert((((pref_c_7[i+mid]-pref_c_7[i]+MOD7)%MOD7)*base_rev_power7[i])%MOD7);
        }
        bool intersected7 = false;
        fo(i, 0, m+1-mid) {
            if (c_st7.find((((pref_b_7[i+mid]-pref_b_7[i]+MOD7)%MOD7)*base_rev_power7[i])%MOD7) != c_st7.end()) {
                intersected7 = true;
                break;
            }
        }
        if (intersected7) {
            good = mid;
            l = mid+1;
        } else {
            r = mid-1;
        }
    }
//    clog << "ans: " << good << endl;
//    auto stop = chrono::high_resolution_clock::now();
//    auto duration = duration_cast<chrono::microseconds>(stop - start_time);
//    clog << "Time taken by function: " << duration.count() << " microseconds" << endl;
//    ll OG = og_counter(b, c);
//    clog << good << " " << OG << endl;
//    assert(good == OG);
    if (good > 0) {
//        clog << "peresech_size: " << good << endl;
        cout << m-good+k-good << endl;
    } else {
//        clog << "lets see" << endl;
        ll dp[MAXN];
        fo(i, 0, MAXN) {
            dp[i] = INT_MAX;
        }
        fo(i, 0, m) {
            dp[b[i]] = m-1;
        }

        while(true) {
            forr(i, 1, n-1) {
                dp[a[i]] = min(dp[a[i]], dp[a[i-1]]+2);
            }
            roff(i, n-2, 0) {
                dp[a[i]] = min(dp[a[i]], dp[a[i+1]]+2);
            }
            bool enough = true;
            forr(i, 1, n-1) {
                if (dp[a[i]] != min(dp[a[i]], dp[a[i-1]]+2)) {
                    enough = false;
                }
            }
            roff(i, n-2, 0) {
                if (dp[a[i]] != min(dp[a[i]], dp[a[i+1]]+2)) {
                    enough = false;
                }
            }
            if (enough) break;
//            else clog << "not enough" << endl;
        }

//        fo(i, 0, k) {
//            assert(dp[b[i]] == m-1);
//        }
        ll res = INT_MAX;
        fo(i, 0, k) {
            res = min(res, dp[c[i]]+k-1);
        }
//        assert(res > 0);
//        assert(res < 4.1e5);
        cout << res << endl;
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
        //clog.tie(nullptr);
    }
    __int128_t tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}