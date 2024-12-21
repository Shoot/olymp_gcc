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
//uniform_int_distribution<ll> distrib(0ll, 5ll);
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
vll p(2e5);
vll sz(2e5, 1);
ll get_p(ll a) {
    return p[a] == a ? a : p[a] = get_p(p[a]);
}
ll su;
void solve() {
    ll n = 10;
    vvll sm(n+1);
    ll U, V;
    for (ll i = 0; i < n-1; i += 1) {
        U = rng()%n+1;
        V = rng()%n+1;
        while (U == V) {
            U = rng()%n+1;
        }
//        cin >> U >> V;
        sm[U].push_back(V);
        sm[V].push_back(U);
//        cout << U << " " << V << "\n";
    }
    vvll up(20, vll(n+1));
    vll h(n+1);
    bitset<11> seen;
    auto dfs = [&] (auto f, ll v, ll par) -> void {
        seen[v] = true;
        for (const auto &x : sm[v]) {
            if (x != par && !seen[x]) {
                h[x] = h[v] + 1;
                up[0][x] = v;
                f(f, x, v);
            }
        }
    };
    up[0][1] = 1;
    dfs(dfs, 1, -1);
    for (ll i = 1; i < 20; i += 1) {
        for (ll v = 1; v <= n; v += 1) {
            up[i][v] = up[i-1][up[i-1][v]];
        }
    }
    su = 0;
    for (ll UU = 1; UU <= n; UU += 1) for (ll VV = 1; VV <= n; VV += 1) {
        ll u = UU;
        ll v = VV;
        if (h[u] < h[v]) swap(u, v);
        ll d = h[u] - h[v];
        for (ll bt = 19; bt >= 0; bt -= 1) {
            if (d&(1ll << bt)) {
                u = up[bt][u];
            }
        }
        if (u == v) {
//            cout << UU << VV << "(2)->" << v << endl;
            su += h[v];
            continue;
        }
        for (ll bt = 19; bt >= 0; bt -= 1) {
            if (up[bt][u] != up[bt][v]) {
                u = up[bt][u];
                v = up[bt][v];
            }
        }
        assert(u != v);
        u = up[0][u];
        v = up[0][v];
        if (u == v) {
            su += h[v];
//            cout << UU << VV << "->" << v << endl;
        } else {
//            cout << "BAD\n";
        }
    }
//    cout << su << ":)" << endl;
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
    ll tt = 1e7;
//    cin >> tt;
    ll maxi = 0;
    while (tt--) {
        su = 0;
        solve();
        if (maxi < su) {
            maxi = su;
            cout << maxi << "\n";
        }
    }
    cout << maxi << "!\n";
    return 0;
}