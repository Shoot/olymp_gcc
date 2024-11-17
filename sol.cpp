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
    ll n, q; cin >> n >> q;
    vvll binup(20, vll(n));
    vvll sm(n);
    for (ll i = 1; i < n; i += 1) {
        ll x; cin >> x;
        binup[0][i] = x;
        sm[x].push_back(i);
    }
    binup[0][0] = 0;
    for (ll i = 1; i < 20; i += 1) {
        for (ll v = 0; v < n; v += 1) {
            binup[i][v] = binup[i-1][binup[i-1][v]];
        }
    }
    vll ask(2*q+1);
    cin >> ask[1];
    cin >> ask[2];
    ll x, y, z;
    cin >> x >> y >> z;
    for (ll i = 3; i <= 2*q; i += 1) {
        ask[i] = x*ask[i-2]+y*ask[i-1]+z;
        if (ask[i] >= n) ask[i] %= n;
    }
    ll prev_ans = 0;
    ll su = 0;
    vvll ladder;
    vll way(n, -1);
    vll order(n, -1);
    vll deepest(n);
    vll h(n);
    auto find_deepest = [&] (auto f, ll v, ll par, ll d) -> void {
        deepest[v] = d;
        h[v] = d;
        for (const auto &x : sm[v]) {
            if (x != par) {
                f(f, x, v, d+1);
                deepest[v] = max(deepest[v], deepest[x]);
            }
        }
    };
    find_deepest(find_deepest, 0, -1, 0);
    auto make_ladders = [&] (auto f, ll v, ll par) -> void {
        if (way[v] == -1) {
            ladder.emplace_back();
            way[v] = ladder.size()-1;
        }
        ladder[way[v]].push_back(v);
        order[v] = ladder[way[v]].size()-1;
        ll deepest_child = 0;
        for (const auto &x : sm[v]) {
            if (x != par) {
                deepest_child = max(deepest_child, deepest[x]);
            }
        }
        ll chosen = -1;
        for (const auto &x : sm[v]) {
            if (x != par && deepest[x] == deepest_child) {
                chosen = x;
                way[x] = way[v];
                f(f, x, v);
                break;
            }
        }
        for (const auto &x : sm[v]) {
            if (x != par && x != chosen) {
                f(f, x, v);
            }
        }
    };
    make_ladders(make_ladders, 0, -1);
//    for (const auto &l : ladder) {
//        cout << l << "!" << endl;
//    }
    auto get_ans = [&] (ll v, ll k) -> ll {
        if (k == 0) return v;
        if (k >= h[v]) return 0ll;
//        watch(k);
        ll i = 63-__builtin_clzl(k);
        ll go = 1ll << i;
        v = binup[i][v];
        ll rest = k-go;
//        cout << "rest = " << rest << endl;
        while (rest) {
            ll can_do = max(0ll, order[v]-rest);
            rest -= order[v]-can_do;
            v = ladder[way[v]][can_do];
            if (rest == 0) break;
            v = binup[0][v];
            rest -= 1;
        }
        return v;
    };
    for (ll i = 1; i <= q; i += 1) {
        ll u = ask[2*i-1]+prev_ans;
        if (u >= n) u %= n;
        ll MY_ANS = get_ans(u, ask[2*i]);
//        cout << u << ", dist = " << dist << endl;
//        for (ll bit = 0; bit < 17; bit += 1) {
//            if ((1ll << bit)&ask[2*i]) u = binup[bit][u];
//        }
        su += MY_ANS;
        prev_ans = MY_ANS;
//        assert(MY_ANS == u);
    }
    cout << su << endl;
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
