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
#define all(xxx) xxx.begin(), xxx.end()
#define watch(xxx) cout << "value of " << #xxx << " is " << xxx << endl
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
        ll b = -1e18;
        ll operator()(ll X) {
            return k*X + b;
        }
    };
    struct Node {
        ll left = NONEXIST;
        ll right = NONEXIST;
        Line line;
    };
    vector<Node> V;
    V.emplace_back();
    auto push = [&] (Node& v) -> void {
        if (v.left == NONEXIST) {
            V.emplace_back();
            v.left = V.size()-1;
        }
        if (v.right == NONEXIST) {
            V.emplace_back();
            v.right = V.size()-1;
        }
    };
    auto get_best = [&] (auto f, Node& v, ll tl, ll tr, ll pos) -> ll {
        if (tl == tr) {
            return v.line(pos);
        }
        ll tm = (tl + tr) >> 1;
        push(v);
        assert(v.right >= 0);
        assert(v.left >= 0);
        if (pos <= tm) {
            return max(v.line(pos), f(f, V[v.left], tl, tm, pos));
        }
        return max(v.line(pos), f(f, V[v.right], tm+1, tr, pos));
    };
    auto vniz = [&] (ll a, ll b) -> ll {
        assert(b != 0);
        bool ost = abs(a)%abs(b);
        ll res = abs(a)/abs(b);
        if (a < 0 && b > 0 || a > 0 && b < 0) {
            res = -res;
        }
        return res-ost;
    };
    auto intersect = [&] (Line a, Line b) -> ll {
        // до этого числа доминирует одна (включительно)
        return vniz(b.b-a.b, a.k-b.k);
    };
    auto insert_line = [&] (auto f, Node& v, ll tl, ll tr, Line nw) -> void {
        ll tm = (tl + tr) >> 1;
        bool dominating_m = nw(tm) > v.line(tm);
        bool dominating_l = nw(tl) > v.line(tl);
        if (dominating_m) swap(nw, v.line);
        if (tl == tr) return;
        push(v);
        assert(v.right >= 0);
        assert(v.left >= 0);
        if (dominating_m && dominating_l || !dominating_m && !dominating_l) {
            f(f, V[v.right], tm+1, tr, nw);
        }
        if (dominating_m && !dominating_l || !dominating_m && dominating_l) {
            f(f, V[v.left], tl, tm, nw);
        }
    };
    const ll L = -2e9;
    const ll R = 2e9;
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
    ll n; cin >> n;
    struct shit {
        ll x;
        ll y;
        ll val;
    };
    vector<shit> a(n);
    for (ll i = 0; i < n; i += 1) {
        cin >> a[i].x >> a[i].y >> a[i].val;
    }
    sort(a.begin(), a.end(), [&] (shit a, shit b) {
        return a.x < b.x;
    });
    ll maxi = 0;
    vector<ll> dp(n);
    insert_line(insert_line, V.front(), L, R, Line(0, 0)); // neutral bc we can always get f(x) = 0
    for (ll i = 0; i < n; i += 1) {
        ll x = a[i].x;
        ll y = a[i].y;
        ll val = a[i].val;
        dp[i] = x*y+get_best(get_best, V.front(), L, R, y)-val;
        insert_line(insert_line, V.front(), L, R, Line(-x, dp[i]));
    }
    cout << *max_element(all(dp)) << endl;
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
