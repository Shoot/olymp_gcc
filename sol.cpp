#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define all(value) value.begin(), value.end()
#define fo(x, temp_set_for_mex, fi) for(__int128 x = temp_set_for_mex; x < fi; x++)
#define forr(x, temp_set_for_mex, fi) for(__int128 x = temp_set_for_mex; x <= fi; x++)
#define rrof(x, temp_set_for_mex, fi) for(__int128 x = temp_set_for_mex; x >= fi; x--)
#define roff(x, temp_set_for_mex, fi) for(__int128 x = temp_set_for_mex; x >= fi; x--)
#define of(x, temp_set_for_mex, fi) for(__int128 x = temp_set_for_mex; x > fi; x--)
#define ro(x, temp_set_for_mex, fi) for(__int128 x = temp_set_for_mex; x > fi; x--)
#define yes(x) (x ? "YES" : "NO")
#define endl '\n'
#ifdef LOCAL
#include <algo/debug.h>
#else
#define debug(...) 68
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math,trapv")
#endif
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distrib(1ll, 200000ll);
constexpr __int128 MOD7 =  957363431467152001;
constexpr __int128 MOD99 = 695407781356532897;
constexpr __int128 MOD33 = 257354202279932701;
ll m=2e5;
ll k=2e5;
ll og_counter(const vector<ll>& A, const vector<ll>& B) {
    ll a_sz = (ll)A.size();
    ll b_sz = (ll)B.size();
    if (a_sz < b_sz) return og_counter(B, A);
    vector<ll> prev(b_sz + 1, 0);
    vector<ll> curr(b_sz + 1, 0);
    ll maxL = 0;
    for (__int128 i = 1; i <= a_sz; ++i) {
        for (__int128 j = 1; j <= b_sz; ++j) {
            if (A[i - 1] == B[j - 1]) {
                curr[j] = prev[j - 1] + 1;
                maxL = max(maxL, curr[j]);
            } else {
                curr[j] = 0;
            }
        }
        swap(prev, curr);
    }
    return maxL;
}
__int128 powm(__int128 a, __int128 b, __int128 MOD){
    __int128 d = 1;
    while(b){
        if (b&1) d = (d*a) % MOD;
        b >>= 1;
        a = (a*a) % MOD;
    }
    return d;
}
__int128 MAXN = 2e5+10;
__int128 base = MAXN;
__int128 revbase7 = powm(base, MOD7-2, MOD7);
__int128 revbase99 = powm(base, MOD99-2, MOD99);
__int128 revbase33 = powm(base, MOD33-2, MOD33);
vector<__int128> base_power7(MAXN, 1);
vector<__int128> base_power99(MAXN, 1);
vector<__int128> base_power33(MAXN, 1);
vector<__int128> base_rev_power7(MAXN, 1);
vector<__int128> base_rev_power99(MAXN, 1);
vector<__int128> base_rev_power33(MAXN, 1);
/*
void copy_this () {
    __int128 n; cin >> n;
    __int128 n, k; cin >> n >> k;
    __int128 n, q; cin >> n >> q;
    __int128 a[n]; fo(i, 0, n) cin >> a[i];
    vector<__int128> a(n); fo(i, 0, n) cin >> a[i];
}
*/

void solve() {
    fo(i, 1, MAXN) {
        assert(i-1 < base_power7.size());
        base_power7[i] = (base_power7[i-1]*base)%MOD7;
        base_power99[i] = (base_power99[i-1]*base)%MOD99;
        base_power33[i] = (base_power33[i-1]*base)%MOD33;
        base_rev_power7[i] = (base_rev_power7[i-1]*revbase7)%MOD7;
        base_rev_power99[i] = (base_rev_power99[i-1]*revbase99)%MOD99;
        base_rev_power33[i] = (base_rev_power33[i-1]*revbase33)%MOD33;
    }
//    __int128 n; cin >> n;
//    vector<__int128> a(n);
//    fo(i, 0, n) {
//        cin >> a[i];
//    }
//    cin >> m;
    vector<ll> b(m);
    vector<__int128> pref_b_7(m+1, 0);
    vector<__int128> pref_b_99(m+1, 0);
    vector<__int128> pref_b_33(m+1, 0);
    vector<__int128> pref_b_44(m+1, 0);
    fo(i, 0, m) {
        assert(i < b.size());
        b[i] = distrib(rng);
        clog << b[i] << ' ';
//        cin >> b[i];
        assert(i+1 < pref_b_7.size());
        assert(i < b.size());
        assert(i < base_power7.size());
        pref_b_7[i+1] = (pref_b_7[i]+(b[i]*base_power7[i])%MOD7)%MOD7;
        pref_b_99[i+1] = (pref_b_99[i]+(b[i]*base_power99[i])%MOD99)%MOD99;
        pref_b_33[i+1] = (pref_b_33[i]+(b[i]*base_power33[i])%MOD33)%MOD33;
    }clog << endl;
//    cin >> k;
    vector<ll> c(k);
    vector<__int128> pref_c_7(k+1, 0);
    vector<__int128> pref_c_99(k+1, 0);
    vector<__int128> pref_c_33(k+1, 0);
    fo(i, 0, k) {
        c[i] = distrib(rng);
        clog << c[i] << ' ';
//        cin >> c[i];
        assert(i+1 < pref_c_7.size());
        assert(i < c.size());
        assert(i < base_power7.size());
        pref_c_7[i+1] = (pref_c_7[i]+(c[i]*base_power7[i])%MOD7)%MOD7;
        pref_c_99[i+1] = (pref_c_99[i]+(c[i]*base_power99[i])%MOD99)%MOD99;
        pref_c_33[i+1] = (pref_c_33[i]+(c[i]*base_power33[i])%MOD33)%MOD33;
    }clog << endl;
    auto start_time = chrono::high_resolution_clock::now();
    ll l=1, r=min(m, k);
    ll good = 0;
    while (l <= r) {
        ll mid = (l+r) >> 1;
        unordered_set<__int128> b_st7;
        unordered_set<__int128> b_st99;
        unordered_set<__int128> b_st33;
        unordered_set<__int128> c_st7;
        unordered_set<__int128> c_st99;
        unordered_set<__int128> c_st33;
        fo(i, 0, m+1-mid) {
            assert(i+mid < pref_b_7.size());
            assert(i < pref_b_7.size());
            assert(i < base_rev_power7.size());
            b_st7.insert((((pref_b_7[i+mid]-pref_b_7[i]+MOD7)%MOD7)*base_rev_power7[i])%MOD7);
            b_st99.insert((((pref_b_99[i+mid]-pref_b_99[i]+MOD99)%MOD99)*base_rev_power99[i])%MOD99);
            b_st33.insert((((pref_b_33[i+mid]-pref_b_33[i]+MOD33)%MOD33)*base_rev_power33[i])%MOD33);
        }
        fo(i, 0, k+1-mid) {
            assert(i+mid < pref_c_7.size());
            assert(i < pref_c_7.size());
            assert(i < base_rev_power7.size());
            c_st7.insert((((pref_c_7[i+mid]-pref_c_7[i]+MOD7)%MOD7)*base_rev_power7[i])%MOD7);
            c_st99.insert((((pref_c_99[i+mid]-pref_c_99[i]+MOD99)%MOD99)*base_rev_power99[i])%MOD99);
            c_st33.insert((((pref_c_33[i+mid]-pref_c_33[i]+MOD33)%MOD33)*base_rev_power33[i])%MOD33);
        }
        bool intersected7 = false;
        bool intersected99 = false;
        bool intersected33 = false;
        for (const __int128& element : b_st7) {
            if (c_st7.find(element) != c_st7.end()) {
                intersected7 = true;
                break;
            }
        }
        for (const __int128& element : b_st99) {
            if (c_st99.find(element) != c_st99.end()) {
                intersected99 = true;
                break;
            }
        }
        for (const __int128& element : b_st33) {
            if (c_st33.find(element) != c_st33.end()) {
                intersected33 = true;
                break;
            }
        }
        if (intersected7 && intersected99 && intersected33) {
            good = mid;
            l = mid+1;
        } else {
            if (intersected7 + intersected99 + intersected33) {
                clog << "alert" << endl;
                clog << intersected7 << intersected99 << intersected33 << endl;
            }
            r = mid-1;
        }
    }
    clog << "ans: " << good << endl;
    auto stop = chrono::high_resolution_clock::now();
    auto duration = duration_cast<chrono::microseconds>(stop - start_time);
    clog << "Time taken by function: " << duration.count() << " microseconds" << endl;
    ll OG = og_counter(b, c);
    clog << good << " " << OG << endl;
    assert(good == OG);
//    if (good > 0) {
//        clog << "peresech_size: " << good << endl;
//        cout << m-good+k-good << endl;
//    } else {
//        clog << "lets see" << endl;
//        __int128 dp[MAXN];
//        fo(i, 0, MAXN) {
//            dp[i] = INT_MAX;
//        }
//        fo(i, 0, m) {
//            dp[b[i]] = m-1;
//        }
//
//        while(true) {
//            forr(i, 1, n-1) {
//                dp[a[i]] = min(dp[a[i]], dp[a[i-1]]+2);
//            }
//            roff(i, n-2, 0) {
//                dp[a[i]] = min(dp[a[i]], dp[a[i+1]]+2);
//            }
//            bool enough = true;
//            forr(i, 1, n-1) {
//                if (dp[a[i]] != min(dp[a[i]], dp[a[i-1]]+2)) {
//                    enough = false;
//                }
//            }
//            roff(i, n-2, 0) {
//                if (dp[a[i]] != min(dp[a[i]], dp[a[i+1]]+2)) {
//                    enough = false;
//                }
//            }
//            if (enough) break;
//            else clog << "not enough" << endl;
//        }
//
//        fo(i, 0, k) {
//            assert(dp[b[i]] == m-1);
//        }
//        __int128 res = INT_MAX;
//        fo(i, 0, k) {
//            res = min(res, dp[c[i]]+k-1);
//        }
//        assert(res > 0);
//        assert(res < 4.1e5);
//        cout << res << endl;
//    }
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
    __int128 tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}