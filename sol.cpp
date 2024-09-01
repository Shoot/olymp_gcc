#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
//#define all(value) value.begin(), value.end() !!!!!!
#define fo(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x < fi; x++)
#define forr(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x <= fi; x++)
#define rrof(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x >= fi; x--)
#define roff(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x >= fi; x--)
#define of(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x > fi; x--)
#define ro(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x > fi; x--)
#define yes(x) (x ? "YES" : "NO")

using pi = pair<int, int>;
#define f first
#define s second
#define tcT template <class T
tcT > using V = vector<T>;
tcT, size_t SZ > using AR = array<T, SZ>;
using vi = V<int>;
using vpi = V<pi>;
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define each(a, x) for (auto &a : x)
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define rsz resize
#define pb push_back
#define ub upper_bound

#define endl '\n'
#ifdef LOCAL
#include <algo/debug.h>
#else
#define debug(...) 68
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distrib(1, 11);
constexpr ll N = (ll)(1 << 3);
constexpr ll MOD99 = 998244353;
constexpr ll MOD7 = 1e9 + 7;
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; fo(i, 0, n) cin >> a[i];
    vector<ll> a(n); fo(i, 0, n) cin >> a[i];
}
*/

template<class T, int SZ> struct OffBIT2D {
    bool mode = 0; // mode = 1 -> initialized
    vpi todo; // locations of updates to process
    int cnt[SZ], st[SZ];
    vi val; vector<T> bit; // store all BITs in single vector
    void init() { assert(!mode); mode = 1;
        int lst[SZ]; F0R(i,SZ) lst[i] = cnt[i] = 0;
        sort(all(todo),[](const pi& a, const pi& b) {
            return a.s < b.s; });
        each(t,todo) for (int x = t.f; x < SZ; x += x&-x)
            if (lst[x] != t.s) lst[x] = t.s, cnt[x] ++;
        int sum = 0; F0R(i,SZ) lst[i] = 0, st[i] = (sum += cnt[i]);
        val.rsz(sum); bit.rsz(sum); reverse(all(todo));
        each(t,todo) for (int x = t.f; x < SZ; x += x&-x)
            if (lst[x] != t.s) lst[x] = t.s, val[--st[x]] = t.s;
    }
    int rank(int y, int l, int r) {
        cout << y << " " << l << " " << r << endl;
        return ub(begin(val)+l,begin(val)+r,y)-begin(val)-l; }
    void UPD(int x, int y, T t) {
        cout << x << " " << y << endl;
        cout << st[x] << endl;
        for (y = rank(y,st[x],st[x]+cnt[x]); y <= cnt[x]; y += y&-y)
            bit[st[x]+y-1] += t; }
    void upd(int x, int y, T t) {
        if (!mode) todo.pb({x,y});
        else for (;x<SZ;x+=x&-x) UPD(x,y,t); }
    int QUERY(int x, int y) { T res = 0;
        for (y = rank(y,st[x],st[x]+cnt[x]); y; y -= y&-y) res += bit[st[x]+y-1];
        return res; }
    T query(int x, int y) { assert(mode);
        T res = 0; for (;x;x-=x&-x) res += QUERY(x,y);
        return res; }
    T query(int xl, int xr, int yl, int yr) {
        return query(xr,yr)-query(xl-1,yr)
               -query(xr,yl-1)+query(xl-1,yl-1); }
};
//ll count(ll l, ll r, const ll a[], const ll b[]) {
//    clog << l << " to " << r << endl;
//    if (l == r) {
//        if (a[l]+b[l] <= x) {
//            clog << l << " to " << r << ": " << 1 << endl;
//            return 1;
//        } else {
//            clog << l << " to " << r << ": " << 0 << endl;
//            return 0;
//        }
//    }
//    ll tot = 0;
//    ll mid = (l+r) >> 1;
//    vector<ll> rs(r-(mid+1)+1);
//    vector<ll> rm(r-(mid+1)+1);
//    vector<ll> ls(r-(mid+1)+1);
//    vector<ll> lm(r-(mid+1)+1);
//    ll cum = 0;
//    ll mini = LLONG_MAX;
//    forr(i, 0, r-(mid+1)) {
//        cum += a[i+mid+1];
//        rs[i] = cum;
//        clog << "rs: " << (ll)(cum%10000) << endl;
//        mini = min(mini, b[i+mid+1]);
//        rm[i] = mini;
//    }
//    cum = 0;
//    mini = LLONG_MAX;
//    forr(i, 0, r-(mid+1)) {
//        clog << i << " " << mid-i << endl;
//        cum += a[mid-i];
//        ls[i] = cum;
//        mini = min(mini, b[mid-i]);
//        lm[i] = mini;
//    }
//    fo(i, 0, r-(mid+1)) {
//        cout << rs[i] << endl;
//        cout << ls[i] << endl;
////        rs_st.insert(rs[i]);
////        ls_st.insert(ls[i]);
//    }
////    fo(i, 0, r-(mid+1)) {
////        tot += rs_st.order_of_key(x-lm[i]-ls[i]);
////    }
////    fo(i, 0, r-(mid+1)) {
////        tot += ls_st.order_of_key(x-rm[i]-rs[i]);
////    }
//    clog << l << " to " << r << ": " << tot << endl;
//    return tot + count(l, mid, a, b)+count(mid+1, r, a, b);
//}
//ll a[N];
//ll b[N];
void solve () {
//    ll n;
//    cin >> n;
    OffBIT2D<int, 10> d;
    d.UPD(2, 2, 1);
    cout << d.query(2, 2);
}
int32_t main (int32_t argc, char* argv[]) {
    bool use_fast_io = true;
    for (int32_t i = 1; i < argc; ++i)
        if (string(argv[i]) == "-local-no-fast-io") {
            use_fast_io = false;
//            cout << "No fastIO" << endl;
            break;
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
    while (tt--) solve();
    return 0;
}