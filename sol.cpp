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
ld EPS = 1e-1l;
void solve() {
    ll n, m, k; cin >> n >> m >> k;
    struct Point {
        ll x;
        ll y;
    };
    auto get_phi = [&] (Point a, Point b) -> ld {
        ld dx = b.x-a.x;
        ld dy = b.y-a.y;
        ld phi = atan2l(dy, dx);
        if (phi < 0) phi += 2.l*M_PI;
        return phi;
    };
    vector<Point> polygon(n);
    vector<Point> queries(m);
    for (ll i = 0; i < n; i += 1) {
        // триангулируем из точки A1
        // Поступает запрос:
        // 1) находим полярный угол относительно A1
        // 2) бинпоиск треугольника
        // 3) пересекаем с полуплоскостью
        cin >> polygon[i].x >> polygon[i].y;
    }
    Point best(1e18, 1e18);
    for (ll i = 0; i < m; i += 1) {
        cin >> queries[i].x >> queries[i].y;
    }
    ll ind = 0;
    for (ll i = 0; i < n; i += 1) {
        if (best.y > polygon[i].y || (best.y == polygon[i].y && best.x > polygon[i].x)) {
            best = polygon[i];
            ind = i;
        }
    }
    rotate(polygon.begin(), polygon.begin() + ind, polygon.end());
    vector<ld> angles;
    for (ll i = 1; i < n; i += 1) {
        ld angle = get_phi(polygon[0], polygon[i])*180.l/M_PI;
        angles.push_back(angle);
    }
    struct Line {
        ld k;
        ld b;
        ld operator()(ld arg) {
            return k*arg+b;
        }
    };
    struct Segment {
        Point fi;
        Point se;
    };
    auto seg_to_line = [&] (Segment a) -> Line {
        ld dx = a.se.x - a.fi.x;
        ld dy = a.se.y - a.fi.y;
        ld k = dy/dx;
        ld b = a.fi.y-k*a.fi.x;
        return Line(k, b);
    };
    vector<Segment> sides;
    for (ll i = 0; i < n-1; i += 1) {
        sides.push_back(Segment(polygon[i], polygon[i+1]));
    }
    ll INSIDE = 0;
    auto ask = [&] (ll x, ll y) -> bool {
        if (x == polygon[0].x && y == polygon[0].y) {
            return true;
        }
        ld angle = get_phi(polygon[0], Point(x, y))*180.l/M_PI;
        ll it = ll(angles.size());
        ll l = 0, r = angles.size()-1;
        while (l <= r) {
            ll mid = (l + r) >> 1;
            if (angles[mid]-angle > EPS) {
                r = mid - 1;
                it = mid;
            } else {
                l = mid + 1;
            }
        }
        if (it == 0) {
            assert(angles[it]-angle > EPS);
            return false;
        }
        if (it == ll(angles.size())) {
            if (polygon.back().x == polygon.front().x && polygon.back().x == x) {
                if (y >= polygon.front().y && y <= polygon.back().y) {
                    return true;
                    // вертикальная прямая прямо со старта
                }
                return false;
            } else {
                ld val = seg_to_line(Segment(polygon.back(), polygon.front()))(x);
                if (abs(val-y) < EPS) {
                    if ((x >= polygon.back().x && x <= polygon.front().x) || (x <= polygon.back().x && x >= polygon.front().x)) {
                        return true;
                    }
                    return false;
                }
                return false;
                // на границе только если
            }
        } else {
            ll dx = sides[it].se.x-sides[it].fi.x;
            if (dx > 0) {
                // НАД
                Line li = seg_to_line(sides[it]);
                if (li(x) < y || abs(li(x) - y) < EPS) {
                    return true;
                }
                return false;
            }
            if (dx < 0) {
                // ПОД
                Line li = seg_to_line(sides[it]);
                if (li(x) > y || abs(li(x) - y) < EPS) {
                    return true;
                    INSIDE += 1;
                }
                return false;
            }
            assert(abs(x-polygon.front().x) > EPS);
            // вертикальный
            if (x <= sides[it].fi.x && sides[it].fi.x >= polygon[0].x) {
                return true;
            }
            if (x >= sides[it].fi.x && sides[it].fi.x <= polygon[0].x) {
                return true;
            }
            return false;
        }
        assert(false);
    };
    for (ll i = 0; i < ll(queries.size()); i += 1) {
        if (ask(queries[i].x, queries[i].y)) {
            INSIDE += 1;
        }
    }
    cout << (INSIDE >= k?"YES":"NO") << endl;
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
