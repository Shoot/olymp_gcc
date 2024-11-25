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
void solve() {
    auto stop = chrono::high_resolution_clock::now();
    function<ll(shit, shit)> comp = [] (shit a, shit b){
        if (a.high_priority_class == b.high_priority_class) {
            return a.low_priority_class < b.low_priority_class;
        }
        return a.high_priority_class < b.high_priority_class;
    };
    ll o = 31;
    ll N = 6e5;
    vll powo(N);
    vll revpow_o(N);
    powo[0] = 1;
    for (ll i = 1; i < N; i += 1) {
        powo[i] = mul(powo[i-1], o);
    }
    revpow_o[N-1] = powm(powo[N-1], MOD-2);
    for (ll i = N-2; i >= 0; i -= 1) {
        revpow_o[i] = mul(revpow_o[i+1], o);
    }
    //assert(powo[0] == 1);
    //assert(powo[1] == o);
    //assert(revpow_o[0] == 1);
    //assert(revpow_o[1] == powm(o, MOD-2));
    string s(3e5, 'a');
//    cin >> s;
    auto s2 = s;
    reverse(s2.begin(), s2.end());
    ll n = ll(s.size());
    vll pref_hash(n+1);
    vll pref_hash2(n+1);
    for (ll i = 1; i <= n; i += 1) {
        pref_hash[i] = sum(pref_hash[i-1], mul(s[i-1]-'a'+1, powo[i-1]));
    }
    for (ll i = 1; i <= n; i += 1) {
        pref_hash2[i] = sum(pref_hash2[i-1], mul(s2[i-1]-'a'+1, powo[i-1]));
    }
    function<ll(ll, ll)> hash = [&] (ll l, ll r) {
        l += 1;
        r += 1;
        return mul(
                sub(pref_hash[r], pref_hash[l-1]),
                revpow_o[l-1]);
    };
    function<ll(ll, ll)> rhash = [&] (ll l, ll r) {
        l += 1;
        r += 1;
        return mul(
                sub(pref_hash2[r], pref_hash2[l-1]),
                revpow_o[l-1]);
    };
    s.push_back('\0');
    n = ll(s.size());
    auto start = chrono::high_resolution_clock::now();
    vector<shit> curr(n);
    for (ll i = 0; i < n; i += 1) {
        curr[i].idx = i;
        curr[i].high_priority_class = s[i];
        curr[i].low_priority_class = s[i];
    }
    sort(curr.begin(), curr.end(), comp);
    ll classes_cnt = 1;
    vll c(n);
    for (ll i = 0; i < n; i += 1) {
        if (i > 0 && (curr[i].high_priority_class != curr[i-1].high_priority_class ||
                      curr[i].low_priority_class != curr[i-1].low_priority_class)) {
            classes_cnt += 1;
        }
        c[curr[i].idx] = classes_cnt;
    }
    stop = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(stop-start) << endl;
    for (ll K = 0; classes_cnt < n; K += 1) {
        ll two_pow_k = 1ll << K;
        for (ll i = 0; i < n; i += 1) {
            curr[i].idx = i;
            curr[i].high_priority_class = c[i];
            curr[i].low_priority_class = c[(i+two_pow_k)%n];
        }
        sort(curr.begin(), curr.end(), comp);
        classes_cnt = 1;
        for (ll i = 0; i < n; i += 1) {
            if (i > 0 && (curr[i].high_priority_class != curr[i-1].high_priority_class ||
                          curr[i].low_priority_class != curr[i-1].low_priority_class)) {
                classes_cnt += 1;
            }
            c[curr[i].idx] = classes_cnt;
        }
    }
    vpll clasort(n);
    for (ll i = 0; i <n; i+=1) {
        clasort[i].first = c[i];
        clasort[i].second = i;
    }
    sort(clasort.begin(), clasort.end());
    vll rank(n);
    vll sa(n);
    vll lcp(n-1);
    for (ll i = 0; i < n; i+=1) {
        rank[i] = c[i]-1;
        sa[c[i]-1] = i;
    }
    auto get_first_diff_relative = [&] (ll l1, ll r1, ll l2, ll r2) -> ll {
        ll sz = min(r1-l1+1, r2-l2+1);
        ll first_diff_rel = sz-1;
        ll l = 0, r = sz - 1;
        while (l <= r) {
            ll mid = (l + r) >> 1;
            if (hash(l1, l1 + mid) != hash(l2, l2 + mid)) {
                first_diff_rel = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return first_diff_rel;
    };
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
    stop = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(stop-start) << endl;
    //    for (ll i = 0; i < sz; i += 1) {
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
    stop = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(stop-start) << endl;
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
            ll idx = clasort[mid].second;
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
            ll idx = clasort[mid].second;
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
    ll MAXI = 0;
    for (ll i = 0; i < sz; i += 1) {
        ll each_nech = 0;
        ll l_n = 1, r_n = min(i, sz-i-1);
        while (l_n <= r_n) {
            ll mid = (l_n + r_n) >> 1;
            ll lh = hash(i-mid, i-1);
            ll rh = rhash(sz-(i+mid)-1, sz-(i+1)-1);
            if (lh == rh) {
                l_n = mid+1;
                each_nech = mid;
            } else {
                r_n = mid-1;
            }
        }
        ll l = (i+each_nech)-(i-each_nech)+1;
        ll val = l*query(i-each_nech, i+each_nech);
        MAXI = max(MAXI, val);
    }
    stop = chrono::high_resolution_clock::now();;
    cout << chrono::duration_cast<chrono::milliseconds>(stop-start) << endl;
    for (ll i = 0; i < sz; i += 1) {
        ll each_chet = 0;
        ll l_n = 1, r_n = min(i+1, sz-i-1);
        while (l_n <= r_n) {
            ll mid = (l_n + r_n) >> 1;
            ll lh = hash(i-mid+1, i);
            ll rh = rhash(sz-(i+mid)-1, sz-(i+1)-1);
            if (lh == rh) {
                l_n = mid+1;
                each_chet = mid;
            } else {
                r_n = mid-1;
            }
        }
        if (each_chet == 0) continue;
        ll l = each_chet*2;
        ll val = l*query(i-each_chet+1, i+each_chet);
        MAXI = max(MAXI, val);
    }
    stop = chrono::high_resolution_clock::now();;
    cout << chrono::duration_cast<chrono::milliseconds>(stop-start) << endl;
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
