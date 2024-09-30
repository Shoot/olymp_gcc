#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using ld = long double;
using qll = queue<ll>;
using vll = vector<ll>;
using qld = queue<ld>;
using vld = vector<ld>;
using qpll = queue<pll>;
using vpll = vector<pll>;
#define all(value) value.begin(), value.end()
#define fo(XX, X, fi) for(ll XX = X; XX < fi; XX++)
#define forr(XX, X, fi) for(ll XX = X; XX <= fi; XX++)
ostream& endl(ostream& os) {
    return os << '\n';
}
#define vv(type,name,n,...) \
    vector<vector<type>> name(n,vector<type>(__VA_ARGS__))
#define vvv(type,name,n,m,...) \
    vector<vector<vector<type>>> name(n,vector<vector<type>>(m,vector<type>(__VA_ARGS__)))
#ifdef LOCAL
#include <algo/debug.h>
#else
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math,trapv")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distrib(2ll, 10ll);
constexpr ll MOD = 1e9+7;
void in(vector<ll> & a) {
    for (auto & x : a) cin >> x;
}
void in(vector<ll> & a, ll l, ll r) {
    for (ll i=l; i < r; i+=1) {
        cin >> a[i];
    }
}
void inn(vector<ll> & a, ll l, ll rr) {
    for (ll i=l; i <= rr; i+=1) {
        cin >> a[i];
    }
}
ll powm(ll a, ll b) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*a) % MOD;
        b >>= 1;
        a = (a*a) % MOD;
    }
    return d;
}
ll powm(ll a, ll b, ll MOD) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*a) % MOD;
        b >>= 1;
        a = (a*a) % MOD;
    }
    return d;
}
ll poww(ll a, ll b) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*a);
        b >>= 1;
        a = (a*a);
    }
    return d;
}
ll mul(ll a, ll b) {
    return (a*b)%MOD;
}
ll sum(ll a, ll b) {
    return (a+b)%MOD;
}
ll sub(ll a, ll b) {
    return (a-b+100*MOD)%MOD;
}
ll fj0dsq983gf8(ll index, vector<ll> & tree)  {
    index += 1;
    ll sum = 0;
    while (index > 0) {
        sum += tree[index-1];
        index -= index & -index;
    }
    return sum;
} // zero-indexed!!!
ll get_sum_ft(ll left, ll right, vector<ll> & tree) {
    ll n = (ll)tree.size();
    if (!(left <= right)) return 0;
    assert(left <= right);
    if (right >= n) {
        clog << "FENWICK ALERT: R >= tree.size() (IT'S ZERO INDEXED !!!)" << endl;
        right = n-1;
    }
    ll ans = fj0dsq983gf8(right, tree);
    if (left-1 >= 0) {
        ans -= fj0dsq983gf8(left - 1, tree);
    }
    return ans;
} // zero-indexed!!!
void inc_ft(ll index, ll inc, vector<ll> & tree) {
    ll n = (ll)tree.size();
    assert(index >= 0);
    assert(index < n);
    index += 1;
    while (index < n) {
        tree[index] += inc;
        index += index & -index;
    }
} // zero-indexed!!!
void build_ft(vector<ll> & a, vector<ll> & tree) {
    ll n = (ll)tree.size();
    assert(tree.size() == a.size());
    for (ll i = 0; i < n; i++) {
        tree[i] += a[i];
        ll r = i | (i + 1);
        if (r < n) tree[r] += tree[i];
    }
} // zero-indexed!!!
ll inv(ll i, ll m) {
    if (i == 1) return 1; return m-((inv(m%i, i)*m)/i);
}
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; for (ll i=0; i < n; i+=1) cin >> a[i];
    vector<ll> a(n); for (ll i=0; i < n; i+=1) cin >> a[i];
}
*/

void solve() {
    ll n; cin >> n;
    vll a(n); in(a);
    vll p(n); in(p);
    ll rev_1e4 = powm(1e4, MOD-2);
    for (auto & x: p) {
        x = mul(x, rev_1e4);
    }
    vll notp = p;
    for (auto & x: notp) {
        x = sub(1, x);
    }
    ll dp[10][10][2][2];
    fo(i, 0, 10) {
        fo(j, 0, 10) {
            for(auto v1: {0, 1}) {
                for(auto v2: {0, 1}) {
                    dp[i][j][v1][v2] = 0ll;
                }
            }
        }
    }
    fo(i, 0, 10) {
        fo(j, 0, 10) {
            dp[i][j][0][0] = 1ll;
        }
    }
    fo(x, 0, n) {
        ll temp[2][2];
        fo(i, 0, 10) {
            fo(j, 0, 10) {
                for(auto v1: {0, 1}) {
                    for(auto v2: {0, 1}) {
                        temp[v1][v2] =
                                (
                                dp[i][j][v1][v2]*notp[x] +
                                dp[i][j][v1 ^ bool(a[x] & (1 << i))][v2 ^ bool(a[x] & (1 << j))]*p[x]
                                )
                                % MOD;
                    }
                }
                for(auto v1: {0, 1}) {
                    for(auto v2: {0, 1}) {
                        dp[i][j][v1][v2] = temp[v1][v2];
                    }
                }
            }
        }
    }
    ll ans = 0;
    for(ll i = 0; i < 10; i++){
        for(ll j = 0; j < 10; j++){
            ll pw2 = (1ll<<(i+j)) % MOD;
            ans += (1ll*pw2*dp[i][j][1][1]) % MOD;
            ans %= MOD;
            for(ll k : {0,1}) for(ll l : {0,1}) dp[i][j][k][l] = 0;
        }
    }
    cout << ans << endl;
}

int32_t main(int32_t argc, char* argv[]) {
    bool use_fast_io = true;
    for (int32_t i = 1; i < argc; ++i) {
        if (string(argv[i]) == "-local-no-fast-io") {
            use_fast_io = false;
//            cout << "No fastIO" << endl;
            break;
        }
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
    while (tt--) {
        solve();
    }
    return 0;
}
