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
    ll n; cin >> n;
    struct Line {
        __int128 k;
        __int128 b;
        __int128 operator() (ll x) const {
            return k*x+b;
        }
    };
    struct shit {
        ll x;
        ll y;
    };
    deque<Line> lines;
    auto divide = [&] (ll a, ll b) -> __int128 {
        assert(b != 0);
        __int128 res = a/b;
        if ((a > 0 && b < 0) || (a < 0 && b > 0)) res = a/b-bool(a%b);
        return res;
    };
    auto cross = [&] (Line l1, Line l2) -> __int128 {
//        cout << ll(l1.k) << "x +" << ll(l1.b) << endl;
//        cout << ll(l2.k) << "x +" << ll(l2.b) << endl;
        __int128 res1 = divide(l1.b-l2.b, l2.k-l1.k);
        __int128 res2 = divide(l2.b-l1.b, l1.k-l2.k);
//        watch(ll(res1));
        assert(res1 == res2);
        return res1;
    };
    auto get = [&] (ll x) -> Line { // прямоугольники не включают друг друга так что за O(1) (амортизировано)
        // запросы по возрастанию
        while (lines.size() >= 2 && cross(lines[0], lines[1]) <= x) {
            lines.pop_front();
            // нам нужно получить точку левее
        }
        assert(!lines.empty());
        return lines.front();
    };
    auto upd = [&] (Line line) -> void {
        while (lines.size() >= 2 &&
        cross(lines[lines.size()-1], lines[lines.size()-2]) >=
        cross(lines[lines.size()-1], line)) {
            lines.pop_back();
            // банально наша ЛУЧШЕ последней
        }
        lines.push_back(line);
    };
    vector<shit> a(n);
    for (ll i = 0; i < n; i += 1) {
        cin >> a[i].x >> a[i].y;
    }
    sort(a.begin(), a.end(), [&] (shit a, shit b) {
        return a.x < b.x;
    });
    vector<ll> dp(n);
    for (ll i = 0; i < n; i += 1) {
        ll x = a[i].x;
        ll y = a[i].y;
        if (i == 0) {
            dp[i] = x*y;
            upd(Line(y, 0));
            continue;
        }
        // обновления по убыванию, запросы по возрастанию
//        watch(y);
        upd(Line(y, dp[i-1]));
//        cout << ll(get(x).k) << "x + " << ll(get(x).b) << " !" << endl;
        dp[i] = get(x)(x); // гарантированно берем iый
//        watch(dp[i]);
//        for (ll test = 0; test < lines.size(); test += 1) {
//            cout << ll(lines[test].k) << "x + " << ll(lines[test].b) << "   ";
//        }cout << endl;
//        for (ll test = 0; test < lines.size()-1; test += 1) {
//            cout << ll(cross(lines[test], lines[test+1])) << "***";
//        }cout << endl;
    }
    cout << dp.back() << endl;
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
