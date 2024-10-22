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
#define watch(xxx) cout << "value of " << #xxx << " is " << xxx << endl;
template <class T, class S> inline bool chmax(T &a, const S &b) { return (a < b ? a = b, 1 : 0); }
template <class T, class S> inline bool chmin(T &a, const S &b) { return (a > b ? a = b, 1 : 0); }
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
void scan(ll &a) { cin >> a; }
void scan(char &a) { cin >> a; }
void scan(double &a) { cin >> a; }
void scan(long double &a) { cin >> a; }
void scan(string &a) { cin >> a; }
template <class T, class S> void scan(pair<T, S> &p) { scan(p.first), scan(p.second); }
template <class T> void scan(vector<T> &a) {for(auto &i : a) scan(i);}
template <class T> void scan(T &a) { cin >> a; }
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
#ifdef LOCAL
#include <algo/debug.h>
#else
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math,trapv")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distrib(1ll, 3ll);
//constexpr ll MOD = 1e9+7;
constexpr ll MOD = 998244353;
void in(vector<ll> & a) {
    for (auto & zero_leaf : a) cin >> zero_leaf;
}
void in(vector<ll> & a, ll l, ll r) {
    for (ll i=l; i < r; i+=1) {
        cin >> a[i];
    }
}
void inn(vector<ll> & a, ll l, ll rr) {
    for (ll i=l; i <= rr; i+=1) {
        cin >> a[i];
    }
}
ll powm(ll a, ll b) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*a) % MOD;
        b >>= 1;
        a = (a*a) % MOD;
    }
    return d;
}
ll powm(ll a, ll b, ll MODD) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*a) % MODD;
        b >>= 1;
        a = (a*a) % MODD;
    }
    return d;
}
ll poww(ll a, ll b) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*a);
        b >>= 1;
        a = (a*a);
    }
    return d;
}
ld poww(ld a, ll b) {
    assert(b >= 0);
    ld d = 1;
    while (b) {
        if (b&1) d = (d*a);
        b >>= 1;
        a = (a*a);
    }
    return d;
}
ll mul(ll a, ll b) {
    return (a*b)%MOD;
}
ll mul(ll a, ll b, ll MODD) {
    return (a*b)%MODD;
}
ll sum(ll a, ll b) {
    return (a+b)%MOD;
}
ll sum(ll a, ll b, ll MODD) {
    return (a+b)%MODD;
}
ll sub(ll a, ll b) {
    return (a-(b%MOD)+MOD)%MOD;
}
ll sub(ll a, ll b, ll MODD) {
    return (a-(b%MODD)+MODD)%MODD;
}
ll fj0dsq983gf8(ll index, vector<ll> & tree)  {
    index += 1;
    ll sum = 0;
    while (index > 0) {
        sum += tree[index-1];
        index -= index & -index;
    }
    return sum;
} // zero-indexed!!!
ll get_sum_ft(ll left, ll right, vector<ll> & tree) {
    ll n = (ll)tree.size();
    if (left > right) return 0;
    assert(left <= right);
    if (right >= n) {
        clog << "FENWICK ALERT: R >= tree.size() (IT'S ZERO INDEXED !!!)" << endl;
        right = n-1;
    }
    ll dist_from_last_bfs = fj0dsq983gf8(right, tree);
    if (left-1 >= 0) {
        dist_from_last_bfs -= fj0dsq983gf8(left - 1, tree);
    }
    return dist_from_last_bfs;
} // zero-indexed!!!
void inc_ft(ll index, ll inc, vector<ll> & tree) {
    ll n = (ll)tree.size();
    assert(index >= 0);
    assert(index < n);
    index += 1;
    while (index < n) {
        tree[index] += inc;
        index += index & -index;
    }
} // zero-indexed!!!
void build_ft(vector<ll> & a, vector<ll> & tree) {
    ll n = (ll)tree.size();
    assert(tree.size() == a.size());
    for (ll i = 0; i < n; i++) {
        tree[i] += a[i];
        ll good = i | (i + 1);
        if (good < n) tree[good] += tree[i];
    }
} // zero-indexed!!!
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; for (ll i=0; i < n; i+=1) cin >> a[i];
    vector<ll> a(n); for (ll i=0; i < n; i+=1) cin >> a[i];
}
*/
void solve() {
    const __int128 DEAD = 1e20;
    ll n, q;
    cin >> n >> q;
    vll height(n);
    vll health(n);
    struct node {
        ll pos_of_minimum=0, larger_than_1e16=0;
        __int128 val_for_merging=0, unpushed_val_for_merging=0;
    };
    vector<node> st(4*n+5);
    for (ll i = 0; i < n; i += 1) {
        cin >> height[i] >> health[i];
        if (health[i] <= 0) assert(false);
    }
    auto merge = [&] (node a, node b) -> node {
        node ret;
        ret.larger_than_1e16 = a.larger_than_1e16 + b.larger_than_1e16;
        if (a.val_for_merging < b.val_for_merging) {
            ret.val_for_merging = a.val_for_merging;
            ret.pos_of_minimum = a.pos_of_minimum;
        } else {
            ret.val_for_merging = b.val_for_merging;
            ret.pos_of_minimum = b.pos_of_minimum;
        }
        assert(ret.unpushed_val_for_merging == 0);
        return ret;
    };
    auto build = [&] (auto f, ll v, ll tl, ll tr) -> void {
        if (tl == tr) {
            st[v].pos_of_minimum = tl;
            st[v].val_for_merging = health[tl];
            return;
        }
        ll tm = (tl+tr) >> 1;
        f(f, 2*v+1, tl, tm);
        f(f, 2*v+2, tm+1, tr);
        st[v] = merge(st[2*v+1], st[2*v+2]);
    };
    auto push = [&] (ll v, ll tl, ll tr) {
        st[2*v+1].unpushed_val_for_merging += st[v].unpushed_val_for_merging;
        st[2*v+2].unpushed_val_for_merging += st[v].unpushed_val_for_merging;
        st[2*v+1].val_for_merging += st[v].unpushed_val_for_merging;
        st[2*v+2].val_for_merging += st[v].unpushed_val_for_merging;
        st[v].unpushed_val_for_merging = 0;
        ll tm = (tl+tr) >> 1;
        if (st[v].larger_than_1e16 == tr-tl+1) {
            st[2*v+1].larger_than_1e16 = tm-tl+1;
            st[2*v+2].larger_than_1e16 = tr-(tm+1)+1;
        }
    };
    auto get_merged_segment = [&] (auto f, ll v, ll tl, ll tr, ll l, ll r) -> node {
        if (tl == l && tr == r) {
            return st[v];
        }
        push(v, tl, tr);
        ll tm = (tl+tr) >> 1;
        if (l <= tm && r >= tm+1) {
            return merge(f(f, 2*v+1, tl, tm, l, min(tm, r)),
                         f(f, 2*v+2, tm+1, tr, max(tm+1, l), r));
        }
        if (l <= tm) {
            return f(f, 2*v+1, tl, tm, l, min(tm, r));
        }
        if (r >= tm+1) {
            return f(f, 2*v+2, tm+1, tr, max(tm+1, l), r);
        }
        assert(false);
    };
    auto range_inc = [&] (auto f, ll v, ll tl, ll tr, ll l, ll r, __int128 value) -> void {
        if (tl == l && tr == r) {
            if (value == DEAD) {
                st[v].larger_than_1e16 = r-l+1;
            }
            st[v].val_for_merging += value;
            st[v].unpushed_val_for_merging += value;
            return;
        }
        push(v, tl, tr);
        ll tm = (tl+tr) >> 1;
        if (l <= tm) {
            f(f, 2*v+1, tl, tm, l, min(tm, r), value);
        }
        if (r > tm) {
            f(f, 2*v+2, tm+1, tr, max(tm+1, l), r, value);
        }
        st[v] = merge(st[2*v+1], st[2*v+2]);
    };
    build(build, 0, 0, n-1);
    // pos of minimum health after range inc
    for (ll i = 0; i < q; i += 1) {
        ll tp=distrib(rng)%2+1;
        cin >> tp;
        if (tp == 1) {
            ll l, r, x;
            cin >> l >> r >> x;
            l -= 1;
            r -= 1;
            range_inc(range_inc, 0, 0, n-1, l, r, -x);
            while (st[0].val_for_merging <= 0) {
                ll maxi = st[0].pos_of_minimum;
                for (ll drop = st[0].pos_of_minimum; drop <= min(n-1, maxi); drop += 1) {
                    maxi = max(maxi, drop+height[drop]-1);
                }
//                cout << st[0].pos_of_minimum << " ----> " << min(n-1, maxi) << endl;
                range_inc(range_inc, 0, 0, n-1,
                          st[0].pos_of_minimum,
                          min(n-1, maxi), DEAD);
            }
        } else {
            ll l, r;
            cin >> l >> r;
            l -= 1;
            r -= 1;
            ll ans = r-l+1-get_merged_segment(get_merged_segment, 0, 0, n-1, l, r).larger_than_1e16;
            cout << ans << endl;
        }
    }
}

int32_t main(int32_t argc, char* argv[]) {
//    ifstream cin("distance.in");
//    ofstream cout("distance.out");
    cout << setprecision(17);
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