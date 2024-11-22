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
const ll NONEXIST = -1e3;
void solve() {
    struct Line {
        ll k = 0;
        ll b = 1e18;
        ll operator()(ll X) {
            return ll(k)*X + ll(b);
        }
    };
    struct Node {
        int left = NONEXIST;
        int right = NONEXIST;
        Line line;
    };
    ll n; cin >> n;
    vector<vector<Node>> V(n+1, vector<Node>(1, Node()));
    auto push_left = [&] (ll vert, ll i) -> void {
        if (V[vert][i].left == NONEXIST) {
            V[vert].push_back(Node());
            V[vert][i].left = V[vert].size()-1;
        }
    };
    auto push_right = [&] (ll vert, ll i) -> void {
        if (V[vert][i].right == NONEXIST) {
            V[vert].push_back(Node());
            V[vert][i].right = V[vert].size()-1;
        }
    };
    auto get_best = [&] (ll vert, auto f, ll i, ll tl, ll tr, ll pos) -> ll {
        if (tl == tr) {
            return V[vert][i].line(pos);
        }
        ll tm = (tl + tr) >> 1;
        if (pos <= tm && V[vert][i].left != NONEXIST) {
            return min(V[vert][i].line(pos), f(vert, f, V[vert][i].left, tl, tm, pos));
        }
        if (pos >= tm+1 && V[vert][i].right != NONEXIST) {
            return min(V[vert][i].line(pos), f(vert, f, V[vert][i].right, tm+1, tr, pos));
        }
        return V[vert][i].line(pos);
    };
    auto insert_line = [&] (ll vert, auto f, ll i, ll tl, ll tr, Line nw) -> void {
        ll tm = (tl + tr) >> 1;
        ll dominating_m = nw(tm) < V[vert][i].line(tm);
        bool dominating_l = nw(tl) < V[vert][i].line(tl);
        if (dominating_m) swap(nw, V[vert][i].line);
        if (tl == tr) return;
        if ((dominating_m && dominating_l) || (!dominating_m && !dominating_l)) {
            push_right(vert, i);
            f(vert, f, V[vert][i].right, tm+1, tr, nw);
        }
        if ((dominating_m && !dominating_l) || (!dominating_m && dominating_l)) {
            push_left(vert, i);
            f(vert, f, V[vert][i].left, tl, tm, nw);
        }
    };
    const ll L = -1e5-5;
    const ll R = 1e5+5;
//    ll q; cin >> q;
//    for (ll i = 0; i < q; i += 1) {
//        char tp; cin >> tp;
//        if (tp == '+') {
//            Line l;
//            cin >> l.k >> l.b;
//            insert_line(insert_line, V.front(), L, R, l);
//        } else {
//            ll x; cin >> x;
//            cout << get_best(get_best, V.front(), L, R, x) << endl;
//        }
//        watch(V.size());
//    }
    struct shit {
        ll a;
        ll b;
    };
    vector<shit> a(n+1);
    for (ll i = 1; i <= n; i += 1) {
        cin >> a[i].a;
    }
    for (ll i = 1; i <= n; i += 1) {
        cin >> a[i].b;
    }
    vvll sm(n+1);
    for (ll i = 0; i < n-1; i += 1) {
        ll u, v; cin >> u >> v;
        sm[u].push_back(v);
        sm[v].push_back(u);
    }
    vll sz(n+1, 1);
    auto calc_sz = [&] (auto f, ll v, ll par) -> void {
        for (const auto &x : sm[v]) {
            if (x != par) {
                f(f, x, v);
                sz[v] += sz[x];
            }
        }
    };
    calc_sz(calc_sz, 1, 1);
    vll ans(n+1, -666);
    for (const auto &x : V) {
        for (const auto &y : x) {
            assert(y.line.b != 0 || y.line.k != 0);
        }
    }
    auto merge_trees = [&] (auto f, ll into, ll vert, ll i) -> void {
        if (V[vert][i].left != NONEXIST) {
            f(f, into, vert, V[vert][i].left);
        }
        if (V[vert][i].right != NONEXIST) {
            f(f, into, vert, V[vert][i].right);
        }
        if (V[vert][i].line.b < 1e17) insert_line(into, insert_line, 0, L, R, V[vert][i].line);
    };
    auto do_shit = [&] (auto f, ll v, ll par) -> void {
        if (sm[v].size() == 1 && v != 1) {
            ans[v] = 0;
            insert_line(v, insert_line, 0, L, R, Line(a[v].b, ans[v]));
            return;
        }
        ll best_val = -1;
        ll best_child = -1;
        for (const auto &x : sm[v]) {
            if (x != par) {
                f(f, x, v);
                if (best_val < sz[x]) {
                    best_val = sz[x];
                    best_child = x;
                }
            }
        }
        assert(best_val > 0);
        swap(V[best_child], V[v]);
        for (const auto &x : sm[v]) {
            if (x != par && x != best_child) {
                merge_trees(merge_trees, v, x, 0);
//                for (const Node n : V[x]) {
//                    insert_line(v, insert_line, 0, L, R, n.line);
//                }
            }
        }
        ans[v] = get_best(v, get_best, 0, L, R, a[v].a); // гарантированно юзаем v
        insert_line(v, insert_line, 0, L, R, Line(a[v].b, ans[v]));
    };
    do_shit(do_shit, 1, 1);
    for (ll i = 1; i <= n; i += 1) {
        cout << ans[i] << ' ';
    }
    cout << endl;
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
