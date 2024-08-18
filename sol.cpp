#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define all(value) value.begin(), value.end()
#define endl '\n'
#ifdef LOCAL
#include <algo/debug.h>
#else
#define debug(...) 68
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
const int N = 1e7 + 1;
void solve() {
    ll n; cin >> n;
    ll a[n];
    ll cnt[n+1];
    memset(cnt, 0, sizeof(cnt));
    for (ll i=0; i<n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    ll done[n+1];
    ll dp[n+1];
    for (ll i=n; i>=1; i--) {
        ll s = cnt[i];
        ll числа_кратные_i_дают_нод_кратный_i_а_нам_нужен_только_равный_i = 0;
        for (ll nxt=2*i; nxt<=n; nxt+=i) {
            s += cnt[nxt];
            числа_кратные_i_дают_нод_кратный_i_а_нам_нужен_только_равный_i += dp[nxt];
        }
        dp[i] = s*(s-1)/2 - числа_кратные_i_дают_нод_кратный_i_а_нам_нужен_только_равный_i;
    }
    memset(done, 0, sizeof(done));
    ll tot = 0;
    // Нам нужно просумировать все dp кроме тех что кратны какому-нибудь a_i
    for (ll i=1; i<=n; i++) {
        if (cnt[i] > 0 && (!done[i])) {
            for (ll nxt=i; nxt<=n; nxt+=i) {
                done[nxt] = 1;
            }
        }
    }
    for (ll i=1; i<=n; i++) {
        if (!done[i]) {
            tot += dp[i];
        }
    }
    cout << tot << endl;
}
int32_t main (int argc, char* argv[]) {
    bool use_fast_io = true;
    for (int i = 1; i < argc; ++i)
        if (string(argv[i]) == "-local-no-fast-io") {
            use_fast_io = false;
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
    cin >> tt;
    while (tt--) solve();
    return 0;
}