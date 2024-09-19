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
bool impossible(ll i, ll j) {
    if (i >= n || i < 0 || j >= m || j < 0) {
        return true;
    }
    return false;
}
void solve()
{
    cin >> n >> m >> k;
    vector<vector<bool>> r(n, vector<bool> (m));
    fo(i, 0, n) {
        fo(j, 0, m) {
            r[i][j] = j%2;
        }
    }
    ll todo = k-m;
    fo(i, 0, n-1) {
        if (i%2 == 1) continue;
        if (todo < 0) break;
        fo(j, 0, m) {
            r[i][j] = !r[i+1][j];
        }
        todo -= m;
    }
    clog << "TODO=" << todo << endl;
    while (todo < 0) {
        cout << todo << endl;
        roff(i, n-1, 0) {
            bool stop = false;
            roff(j, m-1, 0) {
                if      (
                        (impossible(i-1, j) || r[i-1][j] != r[i][j]) &&
                        (impossible(i+1, j) || r[i+1][j] != r[i][j]) &&
                        (impossible(i, j-1) || r[i][j-1] != r[i][j]) &&
                        (impossible(i, j+1) || r[i][j+1] != r[i][j])
                        ) {
                    r[i][j] = !r[i][j];
                    cout << i << " " << j << endl;
                    stop = true;
                    break;
                }
            }
            if (stop) break;
        }
        todo += 1;
    }
    fo(i, 0, n) {
        fo(j, 0, m) {
            cout << r[i][j];
        }
        cout << endl;
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