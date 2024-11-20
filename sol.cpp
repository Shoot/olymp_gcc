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
    ll n = 2;
    cin >> n;
    struct Point {
        ld x;
        ld y;
        auto operator<=> (const Point &other) const = default;
    };
    struct Segment {
        Point fi;
        Point se;
        auto operator<=> (const Segment &other) const = default;
    };
    vector<Segment> segs(n);
    for (ll i = 0; i < n; i += 1) {
//        watch(i);
        cin >> segs[i].fi.x >> segs[i].fi.y >> segs[i].se.x >> segs[i].se.y;
//        segs[i].fi.x = distrib(rng);
//        segs[i].fi.y = distrib(rng);
//        segs[i].se.x = distrib(rng);
//        segs[i].se.y = distrib(rng);
//        watch(segs[i].fi.x);
//        watch(segs[i].fi.y);
//        watch(segs[i].se.x);
//        watch(segs[i].se.y);
        if (segs[i].fi.x > segs[i].se.x) {
            swap(segs[i].fi, segs[i].se);
        }
        if (segs[i].fi.x == segs[i].se.x) {
            segs[i].se.x += 1e-15;
        }
    }
    sort(segs.begin(), segs.end(), [&] (Segment a, Segment b) {
        return a.fi.x < b.fi.x;
    });
    set<ld> key_points;
    map<ld, vll> starts;
    map<ld, vll> ends;
    for (ll i = 0; i < n; i += 1) {
        Segment S = segs[i];
        key_points.insert(S.fi.x);
        key_points.insert(S.se.x);
        starts[S.fi.x].push_back(i);
        ends[S.se.x].push_back(i);
    }
    struct Line {
        ld k;
        ld b;
        ld operator()(ld arg) {
            return k*arg+b;
        }
    };
    auto seg_to_line = [&] (Segment a) -> Line {
        ld dx = a.se.x - a.fi.x;
        ld dy = a.se.y - a.fi.y;
        ld k = dy/dx;
        ld b = a.fi.y-k*a.fi.x;
//        watch(k);
//        watch(b);
        return Line(k, b);
    };
    auto cross = [&] (Line l1, Line l2) -> ld {
        ld a = l1.b-l2.b;
        ld b = l2.k-l1.k;
        return a/b;
    };
    auto get_probable_intersection_x = [&] (Segment a, Segment b) -> ld {
        Line A = seg_to_line(a);
        Line B = seg_to_line(b);
        return cross(A, B);
    };
//    bool OG = false;
//    for (ll i = 0; i < n; i += 1) {
//        for (ll j = 0; j < n; j += 1) {
//            if (i == j) continue;
//            Segment x = segs[i];
//            Segment y = segs[j];
//            if (abs(seg_to_line(x).k-seg_to_line(y).k) < EPS && abs(seg_to_line(x).b-seg_to_line(y).b) < EPS) {
//                if (x.fi.x >= y.fi.x && x.fi.x <= y.se.x) {
//                    OG = true;
//                }
//                if (y.fi.x >= x.fi.x && y.fi.x <= x.se.x) {
//                    OG = true;
//                }
//            } else {
//                ld need = get_probable_intersection_x(x, y);
//                if (need > x.fi.x || abs(need-x.fi.x) < EPS) {
//                    if (need < x.se.x || abs(need-x.se.x) < EPS) {
//                        if (need > y.fi.x || abs(need-y.fi.x) < EPS) {
//                            if (need < y.se.x || abs(need-y.se.x) < EPS) {
//                                OG = true;
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
    bool FOUND = false;
    ld tp;
    auto comp = [&] (auto const &a, auto const &b) {
        return seg_to_line(segs[a])(tp) < seg_to_line(segs[b])(tp);
    };
    multiset<ll, decltype(comp)> current_starts(comp);
    auto GODO = [&] (Segment x, Segment y) -> void {
        if (abs(seg_to_line(x).k-seg_to_line(y).k) < EPS && abs(seg_to_line(x).b-seg_to_line(y).b) < EPS) {
            if (x.fi.x >= y.fi.x && x.fi.x <= y.se.x) {
                FOUND = true;
            }
            if (y.fi.x >= x.fi.x && y.fi.x <= x.se.x) {
                FOUND = true;
            }
        } else if (abs(seg_to_line(x).k - seg_to_line(y).k) > EPS) {
            ld need = get_probable_intersection_x(x, y);
            if (need < tp && abs(need-tp) > EPS) {
                assert(true);
            } else if ((x.se.x > need || abs(need-x.se.x) < EPS) && (y.se.x > need || abs(y.se.x-need) < EPS)) {
                FOUND = true;
            }
        }
    };
    vector<multiset<ll>::iterator> where(n);
    while (!key_points.empty()) {
        tp = *key_points.begin();
//        cout << "time point = " << tp << endl;
        key_points.erase(key_points.begin());
        for (const auto &ind : starts[tp]) {
//            cout << "added " << ind << endl;
            Segment x = segs[ind];
//            watch(x.fi.x);
//            watch(x.fi.y);
            auto it = current_starts.upper_bound(ind);
            if (it != current_starts.end()) {
                Segment y = segs[*it];
                GODO(x, y);
            }
            if (it != current_starts.begin()) {
                it = prev(it);
                Segment y = segs[*it];
                GODO(x, y);
            }
            where[ind] = current_starts.insert(ind);
        }
        for (const auto &ind : ends[tp]) {
            auto it = where[ind];
            if (next(it) != current_starts.end() && it != current_starts.begin()) {
                Segment x = segs[*prev(it)];
                Segment y = segs[*next(it)];
                GODO(x, y);
            }
            current_starts.erase(where[ind]);
        }
    }
//    watch(FOUND);
//    watch(OG);
//    assert(FOUND == OG);
    cout << (FOUND?"YES":"NO") << endl;
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
