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
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math,trapv")
#endif
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distrib(1ll, 20ll);
//constexpr ll N = (ll)(1e15);
constexpr ll MOD7 =  999987301;
constexpr ll MOD99 = 989989103;
constexpr ll MOD33 = 979989193;
constexpr ll MOD44 = 969988837;
constexpr ll MOD55 = 959988847;
constexpr ll MOD66 = 949988839;
constexpr ll MOD77 = 939989423;
constexpr ll MOD88 = 929989679;

ll longestCommonSubarrayLength(const vector<ll>& A, const vector<ll>& B) {
    ll n = A.size();
    ll m = B.size();
    if (n == 0 || m == 0) return 0;
    if (n > m) {
        return longestCommonSubarrayLength(B, A);
    }
    vector<ll> dp(m + 1, 0);
    ll maxLength = 0;
    for (ll i = 0; i < n; ++i) {
        vector<ll> new_dp(m + 1, 0);
        for (ll j = 0; j < m; ++j) {
            if (A[i] == B[j]) {
                new_dp[j + 1] = dp[j] + 1;
                maxLength = max(maxLength, new_dp[j + 1]);
            }
        }
        dp = new_dp;
    }
    return maxLength;
}
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
ll revbase33 = powm(base, MOD33-2, MOD33);
ll revbase44 = powm(base, MOD44-2, MOD44);
ll revbase55 = powm(base, MOD55-2, MOD55);
ll revbase66 = powm(base, MOD66-2, MOD66);
ll revbase77 = powm(base, MOD77-2, MOD77);
ll revbase88 = powm(base, MOD88-2, MOD88);
vector<ll> base_power7(MAXN, 1);
vector<ll> base_power99(MAXN, 1);
vector<ll> base_power33(MAXN, 1);
vector<ll> base_power44(MAXN, 1);
vector<ll> base_power55(MAXN, 1);
vector<ll> base_power66(MAXN, 1);
vector<ll> base_power77(MAXN, 1);
vector<ll> base_power88(MAXN, 1);
vector<ll> base_rev_power7(MAXN, 1);
vector<ll> base_rev_power99(MAXN, 1);
vector<ll> base_rev_power33(MAXN, 1);
vector<ll> base_rev_power44(MAXN, 1);
vector<ll> base_rev_power55(MAXN, 1);
vector<ll> base_rev_power66(MAXN, 1);
vector<ll> base_rev_power77(MAXN, 1);
vector<ll> base_rev_power88(MAXN, 1);
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
        base_power33[i] = (base_power33[i-1]*base)%MOD33;
        base_power44[i] = (base_power44[i-1]*base)%MOD44;
        base_power55[i] = (base_power55[i-1]*base)%MOD55;
        base_power66[i] = (base_power66[i-1]*base)%MOD66;
        base_power77[i] = (base_power77[i-1]*base)%MOD77;
        base_power88[i] = (base_power88[i-1]*base)%MOD88;
        base_rev_power7[i] = (base_rev_power7[i-1]*revbase7)%MOD7;
        base_rev_power99[i] = (base_rev_power99[i-1]*revbase99)%MOD99;
        base_rev_power33[i] = (base_rev_power33[i-1]*revbase33)%MOD33;
        base_rev_power44[i] = (base_rev_power44[i-1]*revbase44)%MOD44;
        base_rev_power55[i] = (base_rev_power55[i-1]*revbase55)%MOD55;
        base_rev_power66[i] = (base_rev_power66[i-1]*revbase66)%MOD66;
        base_rev_power77[i] = (base_rev_power77[i-1]*revbase77)%MOD77;
        base_rev_power88[i] = (base_rev_power88[i-1]*revbase88)%MOD88;
    }
    ll n; cin >> n;
    vector<ll> a(n);
    fo(i, 0, n) {
        cin >> a[i];
    }
    clog << "got that" << endl;
    ll m=2e4;
    cin >> m;
    vector<ll> b(m);
    vector<ll> pref_b_7(m+1, 0);
    vector<ll> pref_b_99(m+1, 0);
    vector<ll> pref_b_33(m+1, 0);
    vector<ll> pref_b_44(m+1, 0);
    vector<ll> pref_b_55(m+1, 0);
    vector<ll> pref_b_66(m+1, 0);
    vector<ll> pref_b_77(m+1, 0);
    vector<ll> pref_b_88(m+1, 0);
    fo(i, 0, m) {
//        b[i] = distrib(rng);
//        clog << b[i] << ' ';
        cin >> b[i];
        pref_b_7[i+1] = (pref_b_7[i]+b[i]*base_power7[i])%MOD7;
        pref_b_99[i+1] = (pref_b_99[i]+b[i]*base_power99[i])%MOD99;
        pref_b_33[i+1] = (pref_b_33[i]+b[i]*base_power33[i])%MOD33;
        pref_b_44[i+1] = (pref_b_44[i]+b[i]*base_power44[i])%MOD44;
        pref_b_55[i+1] = (pref_b_55[i]+b[i]*base_power55[i])%MOD55;
        pref_b_66[i+1] = (pref_b_66[i]+b[i]*base_power66[i])%MOD66;
        pref_b_77[i+1] = (pref_b_77[i]+b[i]*base_power77[i])%MOD77;
        pref_b_88[i+1] = (pref_b_88[i]+b[i]*base_power88[i])%MOD88;
    }
//    clog << endl;
    ll k=2e4;
    cin >> k;
    vector<ll> c(k);
    vector<ll> pref_c_7(k+1, 0);
    vector<ll> pref_c_99(k+1, 0);
    vector<ll> pref_c_33(k+1, 0);
    vector<ll> pref_c_44(k+1, 0);
    vector<ll> pref_c_55(k+1, 0);
    vector<ll> pref_c_66(k+1, 0);
    vector<ll> pref_c_77(k+1, 0);
    vector<ll> pref_c_88(k+1, 0);
    fo(i, 0, k) {
//        c[i] = distrib(rng);
//        clog << c[i] << ' ';
        cin >> c[i];
        pref_c_7[i+1] = (pref_c_7[i]+c[i]*base_power7[i])%MOD7;
        pref_c_99[i+1] = (pref_c_99[i]+c[i]*base_power99[i])%MOD99;
        pref_c_33[i+1] = (pref_c_33[i]+c[i]*base_power33[i])%MOD33;
        pref_c_44[i+1] = (pref_c_44[i]+c[i]*base_power44[i])%MOD44;
        pref_c_55[i+1] = (pref_c_55[i]+c[i]*base_power55[i])%MOD55;
        pref_c_66[i+1] = (pref_c_66[i]+c[i]*base_power66[i])%MOD66;
        pref_c_77[i+1] = (pref_c_77[i]+c[i]*base_power77[i])%MOD77;
        pref_c_88[i+1] = (pref_c_88[i]+c[i]*base_power88[i])%MOD88;
    }
//    clog << endl;
    ll l=1, r=min(m, k);
    ll good = 0;
    while (l <= r) {
        ll mid = (l+r) >> 1;
        unordered_set<ll> b_st7;
        unordered_set<ll> b_st99;
        unordered_set<ll> b_st33;
        unordered_set<ll> b_st44;
        unordered_set<ll> b_st55;
        unordered_set<ll> b_st66;
        unordered_set<ll> b_st77;
        unordered_set<ll> b_st88;
        unordered_set<ll> c_st7;
        unordered_set<ll> c_st99;
        unordered_set<ll> c_st33;
        unordered_set<ll> c_st44;
        unordered_set<ll> c_st55;
        unordered_set<ll> c_st66;
        unordered_set<ll> c_st77;
        unordered_set<ll> c_st88;
        fo(i, 0, m+1-mid) {
            b_st7.insert(((pref_b_7[i+mid]-pref_b_7[i])*base_rev_power7[i])%MOD7);
            b_st99.insert(((pref_b_99[i+mid]-pref_b_99[i])*base_rev_power99[i])%MOD99);
            b_st33.insert(((pref_b_33[i+mid]-pref_b_33[i])*base_rev_power33[i])%MOD33);
            b_st44.insert(((pref_b_44[i+mid]-pref_b_44[i])*base_rev_power44[i])%MOD44);
            b_st55.insert(((pref_b_55[i+mid]-pref_b_55[i])*base_rev_power55[i])%MOD55);
            b_st66.insert(((pref_b_66[i+mid]-pref_b_66[i])*base_rev_power66[i])%MOD66);
            b_st77.insert(((pref_b_77[i+mid]-pref_b_77[i])*base_rev_power77[i])%MOD77);
            b_st88.insert(((pref_b_88[i+mid]-pref_b_88[i])*base_rev_power88[i])%MOD88);
        }
        fo(i, 0, k+1-mid) {
            c_st7.insert(((pref_c_7[i+mid]-pref_c_7[i])*base_rev_power7[i])%MOD7);
            c_st99.insert(((pref_c_99[i+mid]-pref_c_99[i])*base_rev_power99[i])%MOD99);
            c_st33.insert(((pref_c_33[i+mid]-pref_c_33[i])*base_rev_power33[i])%MOD33);
            c_st44.insert(((pref_c_44[i+mid]-pref_c_44[i])*base_rev_power44[i])%MOD44);
            c_st55.insert(((pref_c_55[i+mid]-pref_c_55[i])*base_rev_power55[i])%MOD55);
            c_st66.insert(((pref_c_66[i+mid]-pref_c_66[i])*base_rev_power66[i])%MOD66);
            c_st77.insert(((pref_c_77[i+mid]-pref_c_77[i])*base_rev_power77[i])%MOD77);
            c_st88.insert(((pref_c_88[i+mid]-pref_c_88[i])*base_rev_power88[i])%MOD88);
        }
        bool intersected7 = false;
        bool intersected99 = false;
        bool intersected33 = false;
        bool intersected44 = false;
        bool intersected55 = false;
        bool intersected66 = false;
        bool intersected77 = false;
        bool intersected88 = false;
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
        for (const ll& element : b_st33) {
            if (c_st33.find(element) != c_st33.end()) {
                intersected33 = true;
                break;
            }
        }
        for (const ll& element : b_st44) {
            if (c_st44.find(element) != c_st44.end()) {
                intersected44 = true;
                break;
            }
        }
        for (const ll& element : b_st55) {
            if (c_st55.find(element) != c_st55.end()) {
                intersected55 = true;
                break;
            }
        }
        for (const ll& element : b_st66) {
            if (c_st66.find(element) != c_st66.end()) {
                intersected66 = true;
                break;
            }
        }
        for (const ll& element : b_st77) {
            if (c_st77.find(element) != c_st77.end()) {
                intersected77 = true;
                break;
            }
        }
        for (const ll& element : b_st88) {
            if (c_st88.find(element) != c_st88.end()) {
                intersected88 = true;
                break;
            }
        }
        if (intersected7 && intersected99 && intersected33 && intersected44 &&
            intersected55 && intersected66 && intersected77 && intersected88) {
            good = mid;
            l = mid+1;
        } else {
            if (intersected7 + intersected99 + intersected33 + intersected44 +
                intersected55 + intersected66 + intersected77 + intersected88 > 4) {
                clog << "alert" << endl;
                clog << intersected7 << intersected99 << intersected33 << intersected44 <<
                        intersected55 << intersected66 << intersected77 << intersected88 << endl;
            }
            r = mid-1;
        }
    }
//    clog << "ready" << endl;
//    ll OG = longestCommonSubarrayLength(b, c);
//    clog << good << " " << OG << endl;
//    assert(good == OG);
    if (good > 0) {
        clog << "peresech_size: " << good << endl;
        cout << m-good+k-good << endl;
    } else {
        clog << "lets see" << endl;
        ll dp[MAXN];
        fo(i, 0, MAXN) {
            dp[i] = INT_MAX;
        }
        fo(i, 0, m) {
            dp[b[i]] = m-1;
        }

        /*ll start = -1;
        fo(i, 0, n) {
            if (dp[a[i]] == m-1) {
                start = i;
                break;
            }
        }
        assert(start != -1);
        roff(i, start-1, 0) {
            dp[a[i]] = min(dp[a[i]], dp[a[i+1]]+2);
        }
        forr(i, start+1, n-1) {
            dp[a[i]] = min(dp[a[i]], dp[a[i-1]]+2);
        }*/

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
//        fo(i, 0, n) {
//            clog << dp[a[i]] << ' ';
//        }
//        clog << endl;
        ll res = INT_MAX;
        fo(i, 0, k) {
            res = min(res, dp[c[i]]+k-1);
        }
        assert(res > 0);
        assert(res < 4.1e5);
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