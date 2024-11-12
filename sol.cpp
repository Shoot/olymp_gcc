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
#define all(xxx) xxx.begin(), xxx.end()
#define watch(xxx) cout << "value of " << #xxx << " is " << xxx << endl;
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
uniform_int_distribution<ll> distrib(1ll, 10ll);
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
    vll a(n); for (auto &x : a) cin >> x;
    a.insert(a.begin(), 0ll);
    struct shit {
        ll val;
        ll pos;
        auto operator<(const shit& other) {
            return val < other.val;
        };
    };
    vector<shit> positions(n+1);
    for (ll i = 0; i <= n; i += 1) {
        positions[i].val = a[i];
        positions[i].pos = i;
    }
    sort(all(positions));
    vll idx_by_order(n+1);
    for (ll i = 0; i <= n; i += 1) {
        idx_by_order[positions[i].pos] = i;
    }
    vll simple_sorted_for_ub;
    for (ll i = 0; i <= n; i += 1) simple_sorted_for_ub.push_back(positions[i].val);
    struct node {
        ll val=1e18;
        ll push=0;
    };
    vector<node> ST_plus_val(4*n+10);
    vector<node> ST_minus_val(4*n+10);
    vector<node> BASIC(4*n+10);
    auto merge = [&] (ll v, vector<node>& tree) {
        tree[v].val = min(tree[2*v+1].val, tree[2*v+2].val);
    };
    auto push = [&] (ll v, vector<node>& tree) {
        tree[2*v+1].val += tree[v].push;
        tree[2*v+1].push += tree[v].push;
        tree[2*v+2].val += tree[v].push;
        tree[2*v+2].push += tree[v].push;
        tree[v].push = 0;
    };
    auto set_point = [&] (auto f, ll v, ll tl, ll tr, ll pos, ll val, vector<node>& tree) -> void {
        if (tl == tr) {
            tree[v].val = val;
            return;
        }
        push(v, tree);
        ll tm = (tl+tr) >> 1;
        if (pos <= tm) {
            f(f, 2*v+1, tl, tm, pos, val, tree);
        } else {
            f(f, 2*v+2, tm+1, tr, pos, val, tree);
        }
        merge(v, tree);
    };
    auto add_on_segment = [&] (auto f, ll v, ll tl, ll tr, ll l, ll r, ll inc, vector<node>& tree)  -> void {
        if (tl == l && tr == r) {
            tree[v].val += inc;
            tree[v].push = inc;
            return;
        }
        push(v, tree);
        ll tm = (tl+tr) >> 1;
        if (l <= tm) {
            f(f, 2*v+1, tl, tm, l, min(r, tm), inc, tree);
        }
        if (r >= tm+1) {
            f(f, 2*v+2, tm+1, tr, max(tm+1, l), r, inc, tree);
        }
        merge(v, tree);
    };
    auto get_minimum = [&] (auto f, ll v, ll tl, ll tr, ll l, ll r, vector<node>& tree) -> ll {
        if (l > r) return 1e18;
        if (tl == l && tr == r) {
            return tree[v].val;
        }
        push(v, tree);
        ll tm = (tl+tr) >> 1;
        ll x = 1e18;
        if (l <= tm) {
            x = min(x, f(f, 2*v+1, tl, tm, l, min(r, tm), tree));
        }
        if (r >= tm+1) {
            x = min(x, f(f, 2*v+2, tm+1, tr, max(tm+1, l), r, tree));
        }
        return x;
    };
    set_point(set_point, 0, 0, n, idx_by_order[0], 0-positions[idx_by_order[0]].val, ST_minus_val);
    set_point(set_point, 0, 0, n, idx_by_order[0], 0+positions[idx_by_order[0]].val, ST_plus_val);
    set_point(set_point, 0, 0, n, idx_by_order[0], 0, BASIC);
    for (ll i = 1; i <= n; i += 1) {
        ll THIS = positions[idx_by_order[i]].val;
        ll first_minus = upper_bound(all(simple_sorted_for_ub), THIS)-simple_sorted_for_ub.begin();
        ll old_goes_now = 1e18;
        old_goes_now = min(old_goes_now, get_minimum(get_minimum,0,0,n,0,first_minus-1,ST_minus_val)+THIS);
        old_goes_now = min(old_goes_now, get_minimum(get_minimum,0,0,n,first_minus,n,ST_plus_val)-THIS);
        ll VAL = abs(positions[idx_by_order[i]].val-positions[idx_by_order[i-1]].val);
        add_on_segment(add_on_segment, 0, 0, n, 0, n, VAL, ST_minus_val);
        add_on_segment(add_on_segment, 0, 0, n, 0, n, VAL, ST_plus_val);
        add_on_segment(add_on_segment, 0, 0, n, 0, n, VAL, BASIC);
        ll SHIT = min(get_minimum(get_minimum,0,0,n,idx_by_order[i-1],idx_by_order[i-1],BASIC), old_goes_now);
        set_point(set_point, 0, 0, n, idx_by_order[i-1], SHIT-positions[idx_by_order[i-1]].val, ST_minus_val);
        set_point(set_point, 0, 0, n, idx_by_order[i-1], SHIT+positions[idx_by_order[i-1]].val, ST_plus_val);
        set_point(set_point, 0, 0, n, idx_by_order[i-1], SHIT, BASIC);
    }
    cout << get_minimum(get_minimum,0,0,n,0,n,BASIC) << endl;
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