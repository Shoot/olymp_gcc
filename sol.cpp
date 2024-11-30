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
using vvpll = vector<vector<pll>>;
using qld = queue<ld>;
using vld = vector<ld>;
using qpll = queue<pll>;
using vpll = vector<pll>;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
ostream& endl(ostream& os) {
    return os << '\n';
}
//define all(xxx) xxx.begin(), xxx.end()
//define watch(xxx) cout << "value of " << #xxx << " is " << (xxx) << endl
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
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math,trapv")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distrib(0ll, 5ll);
//constexpr ll MOD = 819356875157278019ll;
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
vvll sm;
vvll sm_rev;
vbo seen;
vll comp;
void solve() {
    ll n; cin >> n;
    sm.assign(n+10, vll());
    sm_rev.assign(n+10, vll());
    seen.assign(n+10, false);
    comp.assign(n+10, -1);
    ll m; cin >> m;
    ll hrs; cin >> hrs;
    vll hr(n); for (auto &x : hr) cin >> x;
    for (ll i = 0; i < m; i += 1) {
        ll u, v; cin >> u >> v;
        if ((hr[u-1] + 1)%hrs == hr[v-1]) {
            clog << u << " -> " << v << endl;
            sm[u].push_back(v);
            sm_rev[v].push_back(u);
        }
        if ((hr[v-1] + 1)%hrs == hr[u-1]) {
            clog << v << " -> " << u << endl;
            sm[v].push_back(u);
            sm_rev[u].push_back(v);
        }
    }
    vll toposort;
    auto dfs = [&] (auto f, ll v) -> void {
        seen[v] = true;
        for (const auto &x : sm[v]) {
            if (!seen[x]) {
                seen[x] = true;
                f(f, x);
            }
        }
        toposort.push_back(v);
    };
    ll COMP = 0;
    auto dfs_rev = [&] (auto f, ll v) -> void {
        comp[v] = COMP;
        for (const auto &x : sm_rev[v]) {
            if (comp[x] == -1) {
                comp[x] = COMP;
                f(f, x);
            }
        }
    };
    for (ll i = 1; i <= n; i += 1) {
        if (!seen[i]) dfs(dfs, i);
    }
    reverse(toposort.begin(), toposort.end());
    for (const auto &x : toposort) {
        if (comp[x] == -1) {
            dfs_rev(dfs_rev, x);
            COMP += 1;
        }
    }
    vll outdeg(n+1);
    vll compsz(n+1);
    for (ll i = 1; i <= n; i += 1) {
        compsz[comp[i]] += 1;
        for (const auto &x : sm[i]) {
            if (comp[x] != comp[i]) {
                outdeg[comp[i]] += 1;
            }
        }
    }
    ll best_comp = -1;
    ll ans = 1e18;
    for (ll i = 1; i <= n; i += 1) {
        if (!outdeg[comp[i]]) {
            if (ans > compsz[comp[i]]) {
                ans = compsz[comp[i]];
                best_comp = comp[i];
            }
        }
    }
    cout << ans << endl;
    for (ll i = 1; i <= n; i += 1) {
        if (comp[i] == best_comp) {
            cout << i << ' ';
        }
    }cout << endl;
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
