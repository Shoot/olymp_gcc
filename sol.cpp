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
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//uniform_int_distribution<ll> distrib(1ll, 1000000000000000000ll);
//constexpr ll N = (ll)(1e15);
constexpr ll MOD99 = 998302111;
constexpr ll MOD7 = 998266601;
ll powm(ll a, ll b, ll MOD){
    ll d = 1;
    while(b){
        if (b&1) d = (d*a) % MOD;
        b >>= 1;
        a = (a*a) % MOD;
    }
    return d;
}
ll MAXN = 2e5+1;
ll base = MAXN;
ll revbase7 = powm(base, MOD7-2, MOD7);
ll revbase99 = powm(base, MOD99-2, MOD99);
vector<ll> base_power7(MAXN, 1);
vector<ll> base_power99(MAXN, 1);
vector<ll> base_rev_power7(MAXN, 1);
vector<ll> base_rev_power99(MAXN, 1);
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; fo(i, 0, n) cin >> a[i];
    vector<ll> a(n); fo(i, 0, n) cin >> a[i];
}
*/
void solve() {
    fo(i, 1, MAXN) {
        base_power7[i] = (base_power7[i-1]*base)%MOD7;
        base_power99[i] = (base_power99[i-1]*base)%MOD99;
        base_rev_power7[i] = (base_rev_power7[i-1]*revbase7)%MOD7;
        base_rev_power99[i] = (base_rev_power99[i-1]*revbase99)%MOD99;
    }
    ll n; cin >> n;
    vector<ll> a(n);
    fo(i, 0, n) {
        cin >> a[i];
    }
    clog << "got that" << endl;
    ll m; cin >> m;
    vector<ll> b(m);
    vector<ll> pref_b_7(m+1, 0);
    vector<ll> pref_b_99(m+1, 0);
    fo(i, 0, m) {
        cin >> b[i];
        pref_b_7[i+1] = (pref_b_7[i]+b[i]*base_power7[i])%MOD7;
        pref_b_99[i+1] = (pref_b_99[i]+b[i]*base_power99[i])%MOD99;
    }
    ll k; cin >> k;
    vector<ll> c(k);
    vector<ll> pref_c_7(k+1, 0);
    vector<ll> pref_c_99(k+1, 0);
    fo(i, 0, k) {
        cin >> c[i];
        pref_c_7[i+1] = (pref_c_7[i]+c[i]*base_power7[i])%MOD7;
        pref_c_99[i+1] = (pref_c_99[i]+c[i]*base_power99[i])%MOD99;
    }
    ll l=1, r=min(m, k);
    ll good = 0;
    while (l <= r) {
        ll mid = (l+r) >> 1;
        unordered_set<ll> b_st7;
        unordered_set<ll> b_st99;
        unordered_set<ll> c_st7;
        unordered_set<ll> c_st99;
        fo(i, 0, m+1-mid) {
            b_st7.insert(((pref_b_7[i+mid]-pref_b_7[i])*base_rev_power7[i])%MOD7);
            b_st99.insert(((pref_b_99[i+mid]-pref_b_99[i])*base_rev_power99[i])%MOD99);
        }
        fo(i, 0, k+1-mid) {
            c_st7.insert(((pref_c_7[i+mid]-pref_c_7[i])*base_rev_power7[i])%MOD7);
            c_st99.insert(((pref_c_99[i+mid]-pref_c_99[i])*base_rev_power99[i])%MOD99);
        }
        bool intersected7 = false;
        bool intersected99 = false;
        for (const ll& element : b_st7) {
            if (c_st7.find(element) != c_st7.end()) {
                intersected7 = true;
                break;
            }
        }
        for (const ll& element : b_st99) {
            if (c_st99.find(element) != c_st99.end()) {
                intersected99 = true;
                break;
            }
        }
        if (intersected7 + intersected99 == 1) {
            clog << "alert" << endl;
        }
        if (intersected7 && intersected99) {
            good = mid;
            l = mid+1;
        } else {
            r = mid-1;
        }
    }
    if (good > 0) {
        clog << "peresech_size: " << good << endl;
        cout << m-good+k-good << endl;
    } else {
        clog << "lets see" << endl;
        ll dp[MAXN];
        fo(i, 1, MAXN) {
            dp[i] = INT_MAX;
        }
        fo(i, 0, m) {
            dp[b[i]] = m-1;
        }
//        ll start = -1;
//        fo(i, 0, n) {
//            if (dp[a[i]] == m-1) {
//                start = i;
//                break;
//            }
//        }
//        assert(start != -1);
//        roff(i, start-1, 0) {
//            dp[a[i]] = min(dp[a[i]], dp[a[i+1]]+2);
//        }
//        forr(i, start+1, n-1) {
//            dp[a[i]] = min(dp[a[i]], dp[a[i-1]]+2);
//        }
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
            else clog << "not enough" << endl;
        }

        fo(i, 0, k) {
            assert(dp[b[i]] == m-1);
        }
        fo(i, 0, n) {
            clog << dp[a[i]] << ' ';
        }
        clog << endl;
        ll res = INT_MAX;
        fo(i, 0, k) {
            res = min(res, dp[c[i]]+k-1);
        }
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
    ll tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}