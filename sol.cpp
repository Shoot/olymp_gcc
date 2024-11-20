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
uniform_int_distribution<ll> distrib(0ll, 100ll);
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
ld EPS = 1e-10;
void solve() {
    ll n; cin >> n;
    ld S; cin >> S;
    struct Point {
        ld x;
        ld y;
    };
    struct Segment {
        Point a;
        Point b;
    };
    vector<Point> points(n);
    for (ll i = 0; i < n; i += 1) {
        cin >> points[i].x >> points[i].y;
    }
    sort(points.begin(), points.end(), [&] (Point a, Point b) {
        return a.y < b.y;
    });
    struct osn {
        ld deg;
        ll i;
        ll j;
    };
    auto get_phi = [&] (Point a, Point b) -> ld {
        ld dx = b.x-a.x;
        ld dy = b.y-a.y;
//        watch(dx);
//        watch(dy);
//        assert(abs(dx) > EPS);
        ld phi = atan2(dy, dx);
        if (phi < 0) phi += 2.l*M_PI;
        return phi;
    };
    vector<osn> a;
    for (ll i = 0; i < n; i += 1) {
        for (ll j = i+1; j < n; j += 1) {
            ld alpha = get_phi(points[i], points[j]);
            a.push_back(osn(alpha*180.l/M_PI, i, j));
        }
    }
    sort(a.begin(), a.end(), [&] (osn a, osn b) {
        return a.deg < b.deg;
    });
//    for (const auto &[deg, i, j] : a) {
//        cout << deg << " deg: " << i << " -> " << j << endl;
//    }
    vll order_by_idx(n);
    iota(order_by_idx.begin(), order_by_idx.end(), 0ll);
    bool FOUND = false;
    Segment AB;
    auto toch_toch = [&] (Point a, Point b) -> ld {
        return sqrtl((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
    };
    auto get_len = [&] (Segment a) -> ld {
        return toch_toch(a.a, a.b);
    };
    auto calc_S = [&] (Point a) -> ld {
        ld first = get_len(Segment(a, AB.a));
        ld second = get_len(Segment(a, AB.b));
        ld osn = get_len(AB);
        ld p = (first+second+osn)*0.5l;
        ld Sq = sqrtl(p*(p-first)*(p-second)*(p-osn));
        return Sq;
    };
    auto find_tri = [&] (ll l, ll r) -> void {
        if (FOUND) return;
        while (l <= r) {
            ll mid = (l+r) >> 1;
            ld Sq = calc_S(points[mid]);
            if (abs(Sq-S) < EPS) {
                FOUND = true;
                cout << "Yes" << endl;
                cout << ll(round(AB.a.x)) << " " << ll(round(AB.a.y)) << endl;
                cout << ll(round(AB.b.x)) << " " << ll(round(AB.b.y)) << endl;
                cout << ll(round(points[mid].x)) << " " << ll(round(points[mid].y)) << endl;
                break;
            } else if (Sq < S) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    };
    auto find_tri_rev = [&] (ll l, ll r) -> void {
        if (FOUND) return;
        while (l <= r) {
            ll mid = (l+r) >> 1;
            ld Sq = calc_S(points[mid]);
            if (abs(Sq-S) < EPS) {
                FOUND = true;
                cout << "Yes" << endl;
                cout << ll(round(AB.a.x)) << " " << ll(round(AB.a.y)) << endl;
                cout << ll(round(AB.b.x)) << " " << ll(round(AB.b.y)) << endl;
                cout << ll(round(points[mid].x)) << " " << ll(round(points[mid].y)) << endl;
                break;
            } else if (Sq < S) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
    };
    for (ll i = 0; i < n; i += 1) {
        osn x = a[i];
        Point A = points[order_by_idx[x.i]];
        Point B = points[order_by_idx[x.j]];
        ll l1 = 0; ll r1 = min(x.i, x.j);
        ll l2 = max(x.i, x.j); ll r2 = n-1;
        swap(points[order_by_idx[x.i]], points[order_by_idx[x.j]]);
        swap(order_by_idx[x.i], order_by_idx[x.j]);
        AB = Segment(A, B);
        find_tri_rev(l1, r1);
        find_tri(l2, r2);
    }
    if (!FOUND) {
        cout << "No" << endl;
    }
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
