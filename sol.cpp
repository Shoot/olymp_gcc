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
uniform_int_distribution<ll> distrib(1ll, 5ll);
constexpr ll MOD = 1e9+7;
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
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; fo(i, 0, n) cin >> a[i];
    vector<ll> a(n); fo(i, 0, n) cin >> a[i];
}
*/

ll n;
bool isOk(vector<ll> & input) {
    if (n == 1) {
        return true;
    }
    ll i = 1;
    while (i < n) {
        if ((i+1 < n) && (input[i+1] >= input[i])) return false;
        if ((input[i-1] >= input[i])) return false;
        i += 2;
    }
    return true;
}
void solve()
{
    n = distrib(rng);
    cin >> n;
    vector<ll> a (n);
    for(auto &x: a) {
//        x = distrib(rng);
//        clog << x << endl;
        cin >> x;
    }
    sort(a.begin(),a.end());
    bool OGok = false;
    do {
        if (isOk(a)) {
            OGok = true;
        }
    }
    while (next_permutation(all(a)));
    sort(a.begin(),a.end());
    vector<ll>rs;
    ll itl=0,itr=(n+1)/2;
    ll cur_move=0;
    ll moves=0;
    while(moves<n)
    {
        rs.push_back((cur_move==0?a[itl]:a[itr]));
        if(cur_move==0)itl++;
        else itr++;
        cur_move=!cur_move;
        moves++;
    }
    bool ok=true;
    for(ll i=1;i<n;i++)ok&=rs[i-1]!=rs[i];
    assert(OGok == ok);
    if(!ok)
    {
        cout<<-1<<endl;
        return;
    }
    for(auto &x:rs)cout<<x<<" ";
    cout<<endl;
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
    while (tt--) {
        clog << "TEST #" << tt << endl;
        solve();
    }
    return 0;
}