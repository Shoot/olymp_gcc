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
//define watch(xxx) cout << "value of " << #xxx << " is " << (xxx) << endl
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
    //assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*best) % MOD;
        b >>= 1;
        best = (best*best) % MOD;
    }
    return d;
}
ll powm(ll best, ll b, ll MODD) {
    //assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*best) % MODD;
        b >>= 1;
        best = (best*best) % MODD;
    }
    return d;
}
ll poww(ll best, ll b) {
    //assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*best);
        b >>= 1;
        best = (best*best);
    }
    return d;
}
ld poww(ld best, ll b) {
    //assert(b >= 0);
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
struct shit {
    ll idx;
    ll high_priority_class, low_priority_class;
};
vector<int> manacher_odd(string s) {
    int n = (int) s.size();
    vector<int> d(n, 1);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i < r)
            d[i] = min(r - i + 1, d[l + r - i]);
        while (i - d[i] >= 0 && i + d[i] < n && s[i - d[i]] == s[i + d[i]])
            d[i]++;
        if (i + d[i] - 1 > r)
            l = i - d[i] + 1, r = i + d[i] - 1;
    }
    return d;
}
vector<int> manacher_even(string s) {
    int n = (int) s.size();
    vector<int> d(n, 0);
    int l = -1, r = -1;
    for (int i = 0; i < n - 1; i++) {
        if (i < r)
            d[i] = min(r - i, d[l + r - i - 1]);
        while (i - d[i] >= 0 && i + d[i] + 1 < n && s[i - d[i]] == s[i + d[i] + 1])
            d[i]++;
        if (i + d[i] > r)
            l = i - d[i] + 1, r = i + d[i];
    }
    return d;
}
void solve() {
//    auto stop = chrono::high_resolution_clock::now();
    string s;
    cin >> s;
    auto d1 = manacher_odd(s);
    auto d2 = manacher_even(s);
    ll n = ll(s.size());
    s.push_back('\0');
    n = ll(s.size());
//    auto start = chrono::high_resolution_clock::now();
    ll classes_cnt = 0;
    ll cnt = 0;
    vvll mp(500);
    for (ll i = 0; i < n; i++) mp[s[i]].push_back(i);
    vll c(n);
    vll p(n);
    for (auto &x : mp) {
        if (x.empty()) continue;
        for (ll u : x)
            c[u] = classes_cnt, p[cnt++] = u;
        classes_cnt++;
    }
    vll c_nw(n);
    for (ll K = 0; classes_cnt < n; K += 1) {
        vvll a(classes_cnt);
        ll two_pow_k = 1ll << K;
        ll classes_cnt_ = 0;
        cnt = 0;
        for (ll i = 0; i < n; i += 1) {
            ll prev = (p[i]-two_pow_k+n)%n;
            a[c[prev]].push_back(prev);
        }
        for (ll i = 0; i < classes_cnt; i++) { // same prev
            for (size_t j = 0; j < a[i].size(); j++) {
                // если суффикс начинает новый класс эквивалентности
                if (j == 0 || c[(a[i][j]+two_pow_k)%n] != c[(a[i][j-1]+two_pow_k)%n])
                    classes_cnt_++;
                c_nw[a[i][j]] = classes_cnt_-1;
                p[cnt++] = a[i][j];
            }
        }
        swap(c, c_nw);
        swap(classes_cnt, classes_cnt_);
    }
    vll rank(n);
    vll sa(n);
    vll lcp(n-1);
    for (ll i = 0; i < n; i += 1) {
        rank[i] = c[i];
        sa[c[i]] = i;
    }
    ll k = 0;

    for (ll i = 0; i < n; i += 1, k ? k -= 1 : 0) {
        if (rank[i] == n-1) {
            k = 0;
            continue;
        }
        ll j = sa[rank[i]+1];
        while (i+k < n && j+k < n && s[i+k] == s[j+k]) k++;
        lcp[rank[i]] = k;
    }
//    for (ll i = 0; i < n; i += 1) {
//        cout << lcp[rank[i]] << ' ';
//    }cout << endl;
    vvll st(20, vll(n));
    st[0] = lcp;
    for (ll b = 1; b < 20; b += 1) {
        for (ll i = 0; i < n; i += 1) {
            st[b][i] = st[b-1][i];
            ll shi = i+(1ll << (b-1));
            if (shi < n) st[b][i] = min(st[b][i], st[b-1][shi]);
        }
    }
    auto get_minimum_lcp = [&] (ll l, ll r) -> ll {
        ll sz = r-l+1;
        if (sz == 0) return lcp[l];
        ll bt = 63-__builtin_clzl(sz);
        return min(st[bt][l], st[bt][r-(1ll << bt)+1]);
    };
    auto is_first_greater = [&] (ll l1, ll r1, ll l2, ll r2) -> bool {
        if (l1 == l2) return false;
        ll rank1 = rank[l1];
        ll rank2 = rank[l2];
        //assert(rank1 != rank2);
        if (rank1 < rank2) return false;
        ll sz = r1-l1+1;
        //assert(sz == r2-l2+1);
        return get_minimum_lcp(rank2, rank1-1) < sz;
    };
    auto is_first_less = [&] (ll l1, ll r1, ll l2, ll r2) -> bool {
        if (l1 == l2) return false;
        ll rank1 = rank[l1];
        ll rank2 = rank[l2];
        //assert(rank1 != rank2);
        if (rank1 > rank2) return false;
        ll sz = r1-l1+1;
        //assert(sz == r2-l2+1);
        return get_minimum_lcp(rank1, rank2-1) < sz;
    };
    auto query = [&] (ll START, ll END) -> ll {
        ll sz = END-START+1;
        ll l = 0, r = n-1;
        ll first_equal = n-1;
        while (l <= r) {
            ll mid = (l+r) >> 1;
            ll idx = sa[mid];
            if (is_first_greater(START, END, idx, idx+sz-1)) {
                l = mid+1;
                first_equal = mid+1;
            } else {
                r = mid-1;
            }
        }
        ll last_equal = n-1;
        l = 0, r = n-1;
        while (l <= r) {
            ll mid = (l+r) >> 1;
            ll idx = sa[mid];
            if (is_first_less(START, END, idx, idx+sz-1)) {
                r = mid-1;
                last_equal = mid-1;
            } else {
                l = mid+1;
            }
        }
        ll kol = last_equal-first_equal+1;
        return kol;
    };
    ll sz = ll(s.size())-1;
//    cout << d1 << endl;
//    cout << d2 << endl;
    ll MAXI = 0;
    for (ll i = 0; i < sz; i += 1) {
        ll l = 2*d1[i]-1;
        ll val = l*query(i-(d1[i]-1), i+(d1[i]-1));
        MAXI = max(MAXI, val);
    }
    for (ll i = 0; i < sz; i += 1) {
        if (d2[i] == 0) continue;
        ll l = d2[i]*2;
        ll val = l*query(i-d2[i]+1, i+d2[i]);
        MAXI = max(MAXI, val);
    }
    cout << MAXI << endl;
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
