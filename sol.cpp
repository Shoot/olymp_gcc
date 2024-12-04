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
//ostream& endl(ostream& os) {
//    return os << '\n';
//}
//define all(xxx) xxx.begin(), xxx.end()
//define watch(xxx) cout << "value of " << #xxx << " is " << xxx << endl
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
uniform_int_distribution<ll> distrib(0ll, 10ll);
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
void solve() {
    ll n, m;
    cin >> n >> m;
    vvll sm(n+1);
    vpll edges;
    for (ll i = 0; i < m; i += 1) {
        ll u, v; cin >> u >> v;
        sm[u].push_back(v);
        sm[v].push_back(u);
        edges.push_back(pll(u, v));
    }
    bitset<1'000'000> seen;
    vll h(n+1);
    vll up(n+1);
    auto calc_h = [&] (auto f, ll v) -> void {
        seen[v] = true;
        for (const auto &x : sm[v]) {
            if (!seen[x]) {
                seen[x] = true;
                h[x] = h[v] + 1;
                f(f, x);
            }
        }
    };
    for (ll i = 1; i <= n; i += 1) {
        if (!seen[i]) {
            h[i] = 1;
            calc_h(calc_h, i);
        }
    }
    auto get_best_up_in_subtree = [&] (auto f, ll v, ll par) -> void {
        seen[v] = true;
        up[v] = h[v];
        for (const auto &x : sm[v]) {
            if (!seen[x]) {
                f(f, x, v);
                up[v] = min(up[v], up[x]);
            } else {
                if (x != par) {
                    up[v] = min(up[v], h[x]);
                }
            }
        }
    };
    seen.reset();
    for (ll i = 1; i <= n; i += 1) {
        if (!seen[i]) {
            get_best_up_in_subtree(get_best_up_in_subtree, i, i);
        }
    }
    map<pll, ll> mp;
    auto get_color = [&] (ll u, ll v) -> ll {
        if (u > v) swap(u, v);
        assert(u != v);
        auto edge = pll(u, v);
        if (!mp.contains(edge)) {
            return -1;
        }
        return mp[edge];
    };
    ll COLOR = 0;
    auto set_color = [&] (ll u, ll v, ll C) -> void {
        if (u > v) swap(u, v);
        assert(u != v);
        auto edge = pll(u, v);
        mp[edge] = C;
    };
    auto color = [&] (auto f, ll v, ll C, ll par) -> void {
        seen[v] = true;
        for (const auto &x : sm[v]) {
            if (x == par) continue;
            if (!seen[x]) {
                seen[x] = true;
                if (up[x] >= h[v]) {
                    COLOR += 1;
                    set_color(v, x, COLOR);
                    f(f, x, COLOR, v);
                } else {
                    set_color(v, x, C);
                    f(f, x, C, v);
                }
            } else {
                if (h[x] < h[v]) {
                    set_color(v, x, C);
                }
            }
        }
    };
    seen.reset();
    for (ll i = 1; i <= n; i += 1) {
        if (!seen[i]) {
            color(color, i, COLOR, i);
        }
    }
    cout << COLOR << endl;
    vll ans(m);
    for (ll i = 0; i < m; i += 1) {
        ans[i] = get_color(edges[i].first, edges[i].second);
    }
    map<ll, ll> nvm;
    ll nxt = 1;
    for (ll i = 0; i < m; i += 1) {
        ll x = ans[i];
        if (!nvm.contains(x)) {
            nvm[x] = nxt++;
        }
        x = nvm[x];
        cout << x << ' ';
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
