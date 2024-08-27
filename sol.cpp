#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define all(value) value.begin(), value.end()
#define fo(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x < fi; x++)
#define forr(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x <= fi; x++)
#define rrof(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x >= fi; x--)
#define roff(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x >= fi; x--)
#define of(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x > fi; x--)
#define ro(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x > fi; x--)
#define yes(x) (x ? "YES" : "NO")
#define endl '\n'
#ifdef LOCAL
#include <algo/debug.h>
#else
#define debug(...) 68
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//uniform_int_distribution<ll> distrib(100, 900);
constexpr ll N = (ll)(2e5+1);
//constexpr ll MOD = 998244353;
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; fo(i, 0, n) cin >> a[i];
    vector<ll> a(n); fo(i, 0, n) cin >> a[i];
}
*/
pair<ll, ll> ans[N];
ll dfs_ind_by_val [N];
ll lfs_ind_by_val [N];
ll dfs[N];
ll lfs[N];
struct shit {
    ll l, r, root;
};
void solve () {
    ll n; cin >> n;
    fo(i, 0, n) cin >> dfs[i];
    fo(i, 0, n) cin >> lfs[i];
    fo (i, 0, n) {
        dfs_ind_by_val[dfs[i]] = i;
    }
    fo (i, 0, n) {
        lfs_ind_by_val[lfs[i]] = i;
    }
    if (dfs[0] != 1) {
        cout << -1 << endl;
        return;
    }
    queue<shit> q;
    q.push({0, n-1, dfs[0]});
    ll tot = 0;
//    set<pair<ll, ll>> b;
    while (!q.empty()) {
        ll l = q.front().l;
        ll r = q.front().r;
//        assert(!b.contains(make_pair(l, r)));
//        b.insert(make_pair(l, r));
        ll root = q.front().root;
        clog << "l = " << l << ", r = " << r << "; root = " << root << endl;
        q.pop();
        tot += 1;
//        if (tot > (ll)1e7) {
//            cout << -1 << endl;
//            return;
//        }
        ll left_size = lfs_ind_by_val[root]-l;
        ll right_size = r-l+1-left_size-1;
//        clog << "left size = " << left_size << endl;
//        clog << "right size = " << right_size << endl;
        ll left_value, right_value;
        if (left_size >= 1) {
            left_value = dfs[dfs_ind_by_val[root]+1];
            ans[root].first = left_value;
        } else {
            ans[root].first = 0;
        }
        if (right_size >= 1) {
            right_value = dfs[dfs_ind_by_val[root]+left_size+1];
            ans[root].second = right_value;
        } else {
            ans[root].second = 0;
        }
        if (left_size < 0 || right_size < 0) {
            cout << -1 << endl;
            return;
        }
        if (left_size > 1) {
            q.push({l, l+left_size-1, left_value});
//            clog << l << " " << l+left_size-1 << " " << left_value << endl;
        };
        if (right_size > 1) {
            q.push({l + left_size + 1, r, right_value});
//            clog << l + left_size + 1 << " " << r << " " << right_value << endl;
        };
    }
    forr(i, 1, n) {
        cout << ans[i].first << " " << ans[i].second << endl;
    }
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
//    fo(i, 0, 1) skip.insert(distrib(rng));
//    cin >> tt;
    while (tt--) solve();
    return 0;
}