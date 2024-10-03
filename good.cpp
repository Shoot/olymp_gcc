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

void solve() {
    LL(n);
    vvll sm(n+1);
    fo(i,0,n-1){
        ll u, v;
        cin >> u >> v;
        sm[u].push_back(v);
        sm[v].push_back(u);
    }
    // dp[v][i] — подъем на 1 << i
    ll log = 2;
    ll nn = n; while (nn != 1) {
        nn >>= 1;
        log += 1;
    }
    // идем по вершинам в порядке сверху вниз (сверху от текущей все посчитано)
    // dp[v][i] = dp[dp[v][i-1]][i-1]
//    vll euler3;
//    function<void(ll)> compute_euler3 = [&](ll v){
//        seen[v] = true;
//        euler3.push_back(v);
//        for (const auto &x: sm[v]) {
//            if (!seen[x]) {
//                compute_euler3(x);
//                euler3.push_back(v);
//            }
//        }
//    };
    bitset<1000000ll> seen;
    vector<vector<ll>> dp (n+1, vector<ll>(log, 1));
    vll depth(n+1, -1);
    function<void(ll, ll)> compute_binary_lifts = [&](ll v, ll p){
        seen[v] = true;
        dp[v][0] = p;
        fo(i, 1, log) {
            dp[v][i] = dp[dp[v][i-1]][i-1];
        }
        for (const auto &x: sm[v]) {
            if (!seen[x]) compute_binary_lifts(x, v);
        }
    };
    function<void(ll, ll)> compute_d = [&](ll v, ll d){
        seen[v] = true;
        depth[v] = d;
        for (const auto &x: sm[v]) {
            if(!seen[x])compute_d(x, d+1);
        }
    };
    compute_binary_lifts(1, 1);
    seen.reset();
    compute_d(1, 0);
    LL(q);
    fo(i,0,q){
        ll origin, destination, limit;
        cin >> origin >> destination >> limit;
        clog << origin << " " << destination << " " << limit << endl;
        if (n == 1) {
            cout << 1 << endl;
            continue;
        }
        if (origin == destination) {
            cout << destination << endl;
            continue;
        }
        ll origincopy = origin;
        ll destinationcopy = destination;
        ll d1 = depth[origincopy];
        ll d2 = depth[destinationcopy];
        if (d1 > d2) {
            swap(d1, d2);
            swap(origincopy, destinationcopy);
        }
        ll diff = d2-d1;
        assert(diff >= 0);
        fo(j,0,log){
            if((1<<j)&diff){
                destinationcopy = dp[destinationcopy][j];
            }
        }
        if (destinationcopy == origincopy) {
            if (diff <= limit) {
                cout << destination << endl;
                continue;
            } else {
                if (depth[origin] > depth[destination]) {
                    fo(j,0,log){
                        if((1<<j)&limit){
                            origin = dp[origin][j];
                        }
                    }
                    cout << origin << endl;
                } else {
                    ll limit2 = diff-limit;
                    fo(j,0,log){
                        if((1<<j)&limit2){
                            destination = dp[destination][j];
                        }
                    }
                    cout << destination << endl;
                }
            }
            continue;
        }
        fo(j,0,log){
            ll l = 0, r = log-1;
            ll good = -1;
            while (l <= r) {
                ll mid = (l+r) >> 1;
                if (dp[origincopy][mid] != dp[destinationcopy][mid]) {
                    good = mid;
                    l = mid+1;
                } else {
                    r = mid-1;
                }
            }
            if (good != -1) {
                clog << good << endl;
                origincopy = dp[origincopy][good];
                destinationcopy = dp[destinationcopy][good];
            }
        }
        assert(origincopy != destinationcopy);
        assert(dp[origincopy][0] == dp[destinationcopy][0]);
        ll LCA = dp[origincopy][0];
        ll length = depth[origin]-depth[LCA]+depth[destination]-depth[LCA];
        assert(depth[origin]-depth[LCA] >= 0);
        assert(depth[destination]-depth[LCA] >= 0);
        if (length <= limit) {
            cout << destination << endl;
        } else {
            ll do_lca = depth[origin]-depth[LCA];
            if (do_lca >= limit) {
                fo(jj,0,log){
                    if((1<<jj)&limit){
                        origin = dp[origin][jj];
                    }
                }
                cout << origin << endl;
                continue;
            }
            // doshli do lca i spuskaemsya
            ll nehvat = length-limit;
            assert(nehvat <= depth[destination]-depth[LCA]);
            assert(nehvat>0);
            fo(jj,0,log){
                if((1<<jj)&nehvat){
                    destination = dp[destination][jj];
                }
            }
            cout << destination << endl;
        }
    }
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
//    cin >> tt;
    while (tt--) {
        solve();
    }
    return 0;
}
