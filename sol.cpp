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
constexpr ll MOD = 1e9+7;
void in(vector<ll> & a) {
    for (auto & zero_leaf : a) cin >> zero_leaf;
}
void in(vector<ll> & a, ll lx, ll rx) {
    for (ll i=lx; i < rx; i+=1) {
        cin >> a[i];
    }
}
void inn(vector<ll> & a, ll lx, ll rr) {
    for (ll i=lx; i <= rr; i+=1) {
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
    auto f = [&] (ll x) {
        return 70+3*x+(90+(10+x)-1)/(10+x)*60;
    };
    ll lx = 0, rx = 9;
    ll RIGHT_LIMIT_DENOM = rx + 10;
    ll good = -1;
    while (lx <= rx) {
        ll mid = (lx+rx) >> 1;
        ll denom = mid + 10;
        auto get_best_in_class_arg_and_val = [&] (ll denom_one) -> pll {
            ll maxi_arg = -1;
            if (90 % denom_one == 0) {
                ll same_quotient_l, same_quotient_r;
                same_quotient_l = 0, same_quotient_r = 1e18;
                while (same_quotient_l <= same_quotient_r) {
                    ll same_quotient_mid = (same_quotient_l+same_quotient_r) >> 1;
                    if (90/same_quotient_mid < 90/denom_one-1) {
                        maxi_arg = same_quotient_mid;
                        same_quotient_r = same_quotient_mid-1;
                    } else {
                        same_quotient_l = same_quotient_mid+1;
                    }
                }
            } else {
                ll same_quotient_l, same_quotient_r;
                same_quotient_l = 0, same_quotient_r = 1e18;
                while (same_quotient_l <= same_quotient_r) {
                    ll same_quotient_mid = (same_quotient_l+same_quotient_r) >> 1;
                    if (90/same_quotient_mid < 90/denom_one) {
                        maxi_arg = same_quotient_mid;
                        same_quotient_r = same_quotient_mid-1;
                    } else {
                        same_quotient_l = same_quotient_mid+1;
                    }
                }
            }
            ll sameR = maxi_arg-1;
            if (90%(sameR) == 0 && denom_one != sameR) {
                sameR -= 1;
            }
            sameR = min(sameR, RIGHT_LIMIT_DENOM);
            ll func_res = f(sameR-10);
            cout << denom_one << ": same to " << sameR << ", f(sameR) = " << func_res << endl;
            return pll(sameR, func_res);
        };

        // ^^^ чтобы округление к одному у всех
        pll this_group = get_best_in_class_arg_and_val(denom);
        pll next_group = get_best_in_class_arg_and_val(this_group.first+1);
        if (this_group.second < next_group.second) {
            good = this_group.second-10;
            rx = mid-1;
        } else {
            lx = mid+1;
        }
        cout << lx << " " << rx << endl;
    }
    cout << good << endl;
    for (ll x = 0; x <= 9; x += 1) {
        cout << "x = " << x << ", "; watch(f(x));
        cout << "nominator / (10 + x) = " << 90 / (10 + x) << ", ";
        cout << "nominator % (10 + x) = " << 90 % (10 + x) << endl << endl;
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