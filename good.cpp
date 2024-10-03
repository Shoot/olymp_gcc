// https://codeforces.com/contest/2014/submission/284237706
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using ld = long double;
using qll = queue<ll>;
using vll = vector<ll>;
using vvll = vector<vector<ll>>;
using qld = queue<ld>;
using vld = vector<ld>;
using qpll = queue<pll>;
using vpll = vector<pll>;
#define all(value) value.begin(), value.end()
#define fo(XX, X, fi) for(ll XX = X; XX < fi; XX++)
#define forr(XX, X, fi) for(ll XX = X; XX <= fi; XX++)
#define roff(XX, X, fi) for(ll XX = X; XX >= fi; XX--)
ostream& endl(ostream& os) {
    return os << '\n';
}
#define vv(type,name,n,...) \
    vector<vector<type>> name(n,vector<type>(__VA_ARGS__))
#define vvv(type,name,n,m,...) \
    vector<vector<vector<type>>> name(n,vector<vector<type>>(m,vector<type>(__VA_ARGS__)))
#define LL(...) \
  ll __VA_ARGS__; \
  IN(__VA_ARGS__)
#define fi first
#define se second
template <class T, class S> inline bool chmax(T &a, const S &b) { return (a < b ? a = b, 1 : 0); }
template <class T, class S> inline bool chmin(T &a, const S &b) { return (a > b ? a = b, 1 : 0); }
template <typename T, typename U>
ostream& operator<<(ostream& os, const pair<T, U>& A) {
    os << A.fi << " " << A.se;
    return os;
}
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& A) {
    for (size_t i = 0; i < A.size(); i++) {
        if(i) os << " ";
        os << A[i];
    }
    return os;
}
void scan(int &a) { cin >> a; }
void scan(long long &a) { cin >> a; }
void scan(char &a) { cin >> a; }
void scan(double &a) { cin >> a; }
void scan(long double &a) { cin >> a; }
void scan(string &a) { cin >> a; }
template <class T, class S> void scan(pair<T, S> &p) { scan(p.first), scan(p.second); }
template <class T> void scan(vector<T> &a) {for(auto &i : a) scan(i);}
template <class T> void scan(T &a) { cin >> a; }
void IN() {}
template <class Head, class... Tail> void IN(Head &head, Tail &...tail) {
    scan(head);
    IN(tail...);
}
void print() {
    cout << "\n";
}
template <class Head, class... Tail>
void print(Head&& head, Tail&&... tail) {
    cout << head;
    if (sizeof...(Tail)) cout << " ";
    print(forward<Tail>(tail)...);
}
#ifdef LOCAL
#include <algo/debug.h>
#else
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math,trapv")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distrib(0ll, LLONG_MAX);
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
ld poww(ld a, ll b) {
    assert(b >= 0);
    ld d = 1;
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
bitset<1000000> seen;
void solve() {
    seen.reset();
    ll n, c;
    cin >> n >> c;
    vll a(n+1);
    forr(i,1,n){
        cin>>a[i];
    }
    vvll sm(n+1);
    fo(i, 0, n-1) {
        ll u, v;
        cin >> u >> v;
        sm[v].push_back(u);
        sm[u].push_back(v);
    }
    vvll vs;
    vs.emplace_back();
    ll maxh = -1;
    function<void(ll, ll)> dfs = [&] (ll v, ll h) {
        maxh = max(maxh, h);
        seen[v] = true;
        if (h >= vs.size()) vs.emplace_back();
        vs[h].push_back(v);
        for (const auto &x : sm[v]) {
            if (!seen[x]) {
                dfs(x, h+1);
            }
        }
    };
    dfs(1, 1);
    seen.reset();
    vector<vector<ll>> dp(n+1, vector<ll> (2));
    // dp[v][flag] - профит с поддерева вершины v, если она спасена(flag=1) или убита(flag=0)
    function<void(ll)> compute_dp = [&] (ll v) {
        seen[v] = true;
        ll tot1 = a[v];
        for (const auto &x : sm[v]) {
            if (seen[x]) {
                tot1 += max(dp[x][0], dp[x][1]-2*c);
            }
        }
        ll tot0 = 0;
        for (const auto &x : sm[v]) {
            if (seen[x]) {
                tot0 += max(dp[x][0], dp[x][1]);
            }
        }
        dp[v][1] = tot1;
        dp[v][0] = tot0;
//        clog << "dp[" << v << "][1] = " << tot1 << endl;
//        clog << "dp[" << v << "][0] = " << tot0 << endl;
    };
    roff(h, maxh, 1) {
        auto &curr_layer = vs[h];
//        for (const auto &x : curr_layer) {
//            clog << x << ';';
//        }
//        clog << endl;
        for (const auto &x : curr_layer) {
            compute_dp(x);
        }
    }
    cout << max(dp[1][0], dp[1][1]) << endl;
}

int32_t main(int32_t argc, char* argv[]) {
    cout << setprecision(17);
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