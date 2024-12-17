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
void solve() {
    ll n, q; cin >> n >> q;
    vll a(n);
    for (ll i = 0; i < n; i += 1) {
        cin >> a[i];
    }
    auto shit = a;
    auto nvm = a;
    struct Ask {
        ll last_set_idx;
        ll l;
        ll r;
        ll idx;
    };
    struct Set {
        ll pos;
        ll from;
        ll to;
    };
    vector<Set> set;
    vector<Ask> ask;
    for (ll i = 0; i < q; i += 1) {
        ll tp; cin >> tp;
        if (tp == 1) {
            ll l, r; cin >> l >> r;
            l -= 1;
            r -= 1;
            ask.push_back(Ask(set.size()-1, l, r, ask.size()));
        } else {
            ll pos, val; cin >> pos >> val;
            shit.push_back(val);
            pos -= 1;
            set.push_back(Set(pos, a[pos], val));
            a[pos] = val;
        }
    }
    sort(shit.begin(), shit.end());
    shit.erase(unique(shit.begin(), shit.end()), shit.end());

    for (auto &x : set) {
        x.from = lower_bound(shit.begin(), shit.end(), x.from)-shit.begin();
        x.to = lower_bound(shit.begin(), shit.end(), x.to)-shit.begin();
    }
    a = nvm;
    for (ll i = 0; i < n; i += 1) {
        a[i] = lower_bound(shit.begin(), shit.end(), a[i])-shit.begin();
    }
    vector<ll> ans(ask.size());
    const ll K = 2000;
    sort(ask.begin(), ask.end(), [&] (Ask a, Ask b) {
        if (a.last_set_idx/K != b.last_set_idx/K) return a.last_set_idx/K < b.last_set_idx/K;
        if (a.l/K != b.l/K) return a.l/K < b.l/K;
        return a.r < b.r;
    });
    vll cnt_by_val(1e6);
    vll cnt_by_kol(1e6);
    ll curr_l = 0, curr_r = -1;
    ll set_r = -1;
    auto SET = [&] (ll idx) -> void {
        assert(idx >= 0);
        assert(idx < ll(set.size()));
        Set x = set[idx];
        assert(x.from < 2e5);
        assert(x.from >= 0);
        assert(x.to < 2e5);
        assert(x.to >= 0);
        a[x.pos] = x.to;
        if (x.pos < curr_l || x.pos > curr_r) {
            return;
        }
        cnt_by_kol[cnt_by_val[x.from]] -= 1;
        cnt_by_val[x.from] -= 1;
        cnt_by_kol[cnt_by_val[x.from]] += 1;

        cnt_by_kol[cnt_by_val[x.to]] -= 1;
        cnt_by_val[x.to] += 1;
        cnt_by_kol[cnt_by_val[x.to]] += 1;
    };
    auto UNSET = [&] (ll idx) -> void {
        assert(idx >= 0);
        assert(idx < ll(set.size()));
        Set x = set[idx];
        assert(x.from < 2e5);
        assert(x.from >= 0);
        assert(x.to < 2e5);
        assert(x.to >= 0);
        a[x.pos] = x.from;
        if (x.pos < curr_l || x.pos > curr_r) {
            return;
        }
        cnt_by_kol[cnt_by_val[x.to]] -= 1;
        cnt_by_val[x.to] -= 1;
        cnt_by_kol[cnt_by_val[x.to]] += 1;

        cnt_by_kol[cnt_by_val[x.from]] -= 1;
        cnt_by_val[x.from] += 1;
        cnt_by_kol[cnt_by_val[x.from]] += 1;
    };
    auto ADD = [&] (ll idx) -> void {
        assert(idx < ll(a.size()));
        assert(idx >= 0);
        assert(a[idx] < 2e5);
        assert(a[idx] >= 0);
        assert(cnt_by_val[a[idx]] >= 0);
        assert(cnt_by_val[a[idx]] < 2e5);
        cnt_by_kol[cnt_by_val[a[idx]]] -= 1;
        cnt_by_val[a[idx]] += 1;
        assert(cnt_by_val[a[idx]] >= 0);
        assert(cnt_by_val[a[idx]] < 2e5);
        cnt_by_kol[cnt_by_val[a[idx]]] += 1;
    };
    auto DEL = [&] (ll idx) -> void {
        assert(idx < ll(a.size()));
        assert(idx >= 0);
        assert(a[idx] < 2e5);
        assert(a[idx] >= 0);
        assert(cnt_by_val[a[idx]] >= 0);
        assert(cnt_by_val[a[idx]] < 2e5);
        cnt_by_kol[cnt_by_val[a[idx]]] -= 1;
        cnt_by_val[a[idx]] -= 1;
        assert(cnt_by_val[a[idx]] >= 0);
        assert(cnt_by_val[a[idx]] < 2e5);
        cnt_by_kol[cnt_by_val[a[idx]]] += 1;
    };
    for (const auto &[last_set_idx, l, r, idx] : ask) {
        while (set_r < last_set_idx) {
            SET(set_r+1);
            set_r += 1;
        }
        while (set_r > last_set_idx) {
            UNSET(set_r);
            set_r -= 1;
        }
        while (curr_l > l) {
            ADD(curr_l-1);
            curr_l -= 1;
        }
        while (curr_r < r) {
            ADD(curr_r + 1);
            curr_r += 1;
        }
        while (curr_r > r) {
            DEL(curr_r);
            curr_r -= 1;
        }
        while (curr_l < l) {
            DEL(curr_l);
            curr_l += 1;
        }
        ll MEX = 1;
        while (cnt_by_kol[MEX] != 0) {
            assert(cnt_by_kol[MEX] > 0);
            MEX += 1;
        }
        ans[idx] = MEX;
    }
    cout << ans << endl;
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
