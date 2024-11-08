#include <bits/stdc++.h>
using namespace std;
using vbo = vector<bool>;
using ll = long long;
using ull = unsigned long long;
using pll = pair<ll, ll>;
using ld = long double;
using qll = queue<ll>;
using vll = vector<ll>;
using vvll = vector<vector<ll>>;
using qld = queue<ld>;
using vld = vector<ld>;
using qpll = queue<pll>;
using vpll = vector<pll>;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
//ostream& endl(ostream& os) {
//    return os << '\n';
//}
#define all(xxx) xxx.begin(), xxx.end()
#define watch(xxx) cout << "value of " << #xxx << " is " << xxx << endl;
template <class T, class S> inline bool chmax(T &best, const S &b) { return (best < b ? best = b, 1 : 0); }
template <class T, class S> inline bool chmin(T &best, const S &b) { return (best > b ? best = b, 1 : 0); }
template <typename T, typename U>
ostream& operator<<(ostream& os, const pair<T, U>& A) {
    os << A.fi << " " << A.se;
    return os;
}
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& A) {
    for (size_t i = 0; i < A.size(); i++) {
        if (i) os << " ";
        os << A[i];
    }
    return os;
}
void scan(ll &best) { cin >> best; }
void scan(char &best) { cin >> best; }
void scan(double &best) { cin >> best; }
void scan(long double &best) { cin >> best; }
void scan(string &best) { cin >> best; }
template <class T, class S> void scan(pair<T, S> &p) { scan(p.first), scan(p.second); }
template <class T> void scan(vector<T> &best) {for(auto &i : best) scan(i);}
template <class T> void scan(T &best) { cin >> best; }
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
uniform_int_distribution<ll> distrib(0ll, 10ll);
//constexpr ll MOD = 1e9+7;
constexpr ll MOD = 1e9+7;
void in(vector<ll> & best) {
    for (auto & zero_leaf : best) cin >> zero_leaf;
}
void in(vector<ll> & best, ll l, ll r) {
    for (ll i=l; i < r; i+=1) {
        cin >> best[i];
    }
}
void inn(vector<ll> & best, ll l, ll rr) {
    for (ll i=l; i <= rr; i+=1) {
        cin >> best[i];
    }
}
ll powm(ll best, ll b) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*best) % MOD;
        b >>= 1;
        best = (best*best) % MOD;
    }
    return d;
}
ll powm(ll best, ll b, ll MODD) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*best) % MODD;
        b >>= 1;
        best = (best*best) % MODD;
    }
    return d;
}
ll poww(ll best, ll b) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*best);
        b >>= 1;
        best = (best*best);
    }
    return d;
}
ld poww(ld best, ll b) {
    assert(b >= 0);
    ld d = 1;
    while (b) {
        if (b&1) d = (d*best);
        b >>= 1;
        best = (best*best);
    }
    return d;
}
ll mul(ll best, ll b) {
    return (best*b)%MOD;
}
ll mul(ll best, ll b, ll MODD) {
    return (best*b)%MODD;
}
ll sum(ll best, ll b) {
    return (best+b)%MOD;
}
ll sum(ll best, ll b, ll MODD) {
    return (best+b)%MODD;
}
ll sub(ll best, ll b) {
    return (best-(b%MOD)+MOD)%MOD;
}
ll sub(ll best, ll b, ll MODD) {
    return (best-(b%MODD)+MODD)%MODD;
}
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll best[n]; for (ll i=0; i < n; i+=1) cin >> best[i];
    vector<ll> best(n); for (ll i=0; i < n; i+=1) cin >> best[i];
}
*/

void solve() {
    ll n, m;
    cin >> n >> m;
    vll a(n);
    vll b(n);
    for (ll i = 0; i < n; i += 1) {
        cin >> a[i] >> b[i];
    }
    vvll sm(n);
    vpll edges;
    for (ll i = 0; i < m; i += 1) {
        ll u, v;
        cin >> u >> v;
        u -= 1; v -= 1;
        sm[u].push_back(v);
        sm[v].push_back(u);
        edges.push_back(pll(u,v));
    }
    sort(all(sm[0]));
    vll d(n, 1e18);
    d[0] = 0;
    bitset<1'000'000> seen;
    queue<ll> q;
    q.push(0);
    while (!q.empty()) {
        ll tp = q.front(); q.pop();
        seen[tp] = true;
        for (const auto &x : sm[tp]) if (!seen[x]) {
            seen[x] = true;
            d[x] = d[tp]+1;
            q.push(x);
        }
    }
    vll ans(n);
    vpll nvm_sorted(n);
    for (ll i = 0; i < n; i += 1) {
        nvm_sorted[i].first = a[i]-b[i]*(d[i]+1);
        nvm_sorted[i].second = i;
    }
    sort(all(nvm_sorted), greater<>());
    fill(all(ans), nvm_sorted[0].first);
    ans[nvm_sorted[0].second] = nvm_sorted[1].first;
    vvll forward_sm(n), same_d(n);
    for(auto &layer_arr:edges)
    {
        if(d[layer_arr.first]-1==d[layer_arr.second])forward_sm[layer_arr.first].push_back(layer_arr.second);
        if(d[layer_arr.second]-1==d[layer_arr.first])forward_sm[layer_arr.second].push_back(layer_arr.first);
        if(d[layer_arr.first]==d[layer_arr.second]){
            same_d[layer_arr.first].push_back(layer_arr.second);
            same_d[layer_arr.second].push_back(layer_arr.first);
        }
    }
    vvll deepest_first(n);
    for(ll i=0;i<n;i++) deepest_first[d[i]].push_back(i);
    reverse(all(deepest_first));
    // нам осталось обновить d(1,u) == d(v,u) и d(1,u) + 1 == d(u,v)
    // Первый случай
    vvll dp(2, vll(n, -1e18));
    // dp[used_same_layer_edge][v] = max val for this vertex
    for (auto const & layer_vs : deepest_first) {
        // init
        for (const auto &v : layer_vs) {
            dp[0][v] = max(dp[0][v], a[v]-b[v]*d[v]);
        }
        // inter-layer-shit
        for (const auto &v : layer_vs) {
            for (const auto &same_depth_vertex : same_d[v]) {
                dp[1][same_depth_vertex] = max(dp[1][same_depth_vertex], dp[0][v]);
            }
        }
        for (const auto &v : layer_vs) {
            ans[v] = max(ans[v], dp[1][v]);
        }
        for (const auto &v : layer_vs) {
            for (const auto &up : forward_sm[v]) {
                for (ll i = 0; i < 2; i += 1) {
                    dp[i][up] = max(dp[i][up], dp[i][v]);
                }
            }
        }
    }
    dp.assign(2, vll(n, -1e18));
    for (auto const & layer_vs : deepest_first) {
        for (const auto &v : layer_vs) {
            ans[v] = max(ans[v], dp[0][v]);
        }
        // init
        for (const auto &v : layer_vs) {
            dp[0][v] = max(dp[0][v], a[v]-b[v]*(d[v]-1));
        }

        for (const auto &v : layer_vs) {
            for (const auto &up : forward_sm[v]) {
                dp[0][up] = max(dp[0][up], dp[0][v]);
            }
        }
    }
    for(const auto &layer_arr : sm[0]) cout << ans[layer_arr] << endl;
}

int32_t main(int32_t argc, char* argv[]) {
//    ifstream cin("distance.in");
//    ofstream cout("distance.out");
    cout << fixed << setprecision(17);
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