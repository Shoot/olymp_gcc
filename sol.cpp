#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
#define all(value) value.begin(), value.end()
#define endl '\n'
using namespace std;
#ifdef LOCAL
#include <algo/debug.h>
#else
#define debug(...) 68
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
const ll N = (ll)(2.2e5);
ll n, k;
ll dp[N], b[N];
bool check(ll med, const ll a[]) {
    for (int i = 0; i < n; i++) {
        if (a[i] >= med) {
            b[i] = 1;
        } else {
            b[i] = -1;
        }
    }

    dp[0] = b[0];
    for (ll i=1; i<k; i++) {
        dp[i] = dp[i-1] + b[i]; // нечего удалять пока что
    }
    for (ll i = k; i < n; i+=k) {
        dp[i] = max(dp[i-k], b[i]);
    }
    for (ll i = k; i < n; i++) { // MAX SUM OF b AFTER DELETIONS OF SEGMENTS of length k until |b| <= k
        // ВВОДИМ НОВЫЙ ЭЛЕМЕНТ И ОБНОВЛЯЕМ dp
        if (i%k != 0) {
            dp[i] = max(
                    dp[i-1] + b[i], // без удаления
                    dp[i-k] // с удалением
            );
        }
    }

    return dp[n-1] > 0;
}
void solve() {
    cin >> n >> k;
    ll a[n];
    vector<ll> a_s(n);
    ll i=-1;
    for (ll &j: a_s) {
        cin >> a[++i];
        j = a[i];
    }
    sort(all(a_s), [](ll x, ll y) {return x<y;});
    if (n<=k) {
        cout << a[(n+1)/2-1] << endl;
    } else {
        ll l=0, r=n-1;
        ll good = -1;
        while (l <= r) {
            ll mid = (l+r) >> 1;
            if (check(a_s[mid], a)) {
                good = a_s[mid];
                l = mid+1;
            } else {
                r = mid-1;
            }
        }
        cout << good << endl;
    }
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
    }
    ll tt = 1;
    cin >> tt;
    while (tt--) solve();
    return 0;
}