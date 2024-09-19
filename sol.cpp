#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef long double ld;
#define all(value) value.begin(), value.end()
#define all(value) value.begin(), value.end()
#define fo(XX, X, fi) for(ll XX = X; XX < fi; XX++)
#define forr(XX, X, fi) for(ll XX = X; XX <= fi; XX++)
#define rrof(XX, X, fi) for(ll XX = X; XX >= fi; XX--)
#define roff(XX, X, fi) for(ll XX = X; XX >= fi; XX--)
#define of(XX, X, fi) for(ll XX = X; XX > fi; XX--)
#define ro(XX, X, fi) for(ll XX = X; XX > fi; XX--)
#define yes(XX) (XX ? "YES" : "NO")
#define endll endl
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
constexpr ll MOD = 1e9+7;
const int N = 1e5+10;
/*\
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; fo(i, 0, n) cin >> a[i];
    vector<ll> a(n); fo(i, 0, n) cin >> a[i];
}
*/
ll powm(ll a, ll b){
    assert(b >= 0);
    ll d = 1;
    while(b){
        if (b&1) d = (d*a) % MOD;
        b >>= 1;
        a = (a*a) % MOD;
    }
    return d;
}
ll mul(ll a, ll b) {
    return (a*b)%MOD;
}
ll sum(ll a, ll b) {
    return (a+b)%MOD;
}
ll n, m, k;
struct shit {
    ll t, enemy_number, hp;
};
void solve()
{
    cin >> n;
    vector<ll> a(n+1);
    vector<ll> b(n+1);
    forr(i, 1, n) {
        cin >> a[i];
    }
    forr(i, 1, n) {
        cin >> b[i];
    }
    vector<ll> pra(n+1, 0);
    vector<ll> prb(n+1, 0);
    forr(i, 1, n) {
        pra[i] = gcd(pra[i-1], a[i]);
        prb[i] = gcd(prb[i-1], b[i]);
    }
    ll maxi = pra[n]+prb[n];
    forr(l, 1, n) {
        if (pra[l] != pra[l-1] || prb[l] != prb[l-1]) {
            clog << "l = " << l << endl;
            forr(r, l, n) {
                ll gcda = 0;
                ll gcdb = 0;
                forr(i, 1, l-1) {
                    gcda = gcd(gcda, a[i]);
                    gcdb = gcd(gcdb, b[i]);
                }
                forr(i, l, r) {
                    gcda = gcd(gcda, b[i]);
                    gcdb = gcd(gcdb, a[i]);
                }
                forr(i, l+1, n) {
                    gcda = gcd(gcda, a[i]);
                    gcdb = gcd(gcdb, b[i]);
                }
                maxi = max(maxi, gcda+gcdb);
            }
        }
    }
    cout << maxi << endl;
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
    cin >> tt;
    while (tt--) solve();
    return 0;
}