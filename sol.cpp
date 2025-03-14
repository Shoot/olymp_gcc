#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
        x %= MOD;
    }
    vector<int> fact(n+1), ifact(n+1);
    auto powm = [&] (int a, int b) -> int {
        int ret = 1;
        while (b) {
            if (b&1) {
                (ret *= a) %= MOD;
            }
            b >>= 1;
            (a *= a) %= MOD;
        }
        return ret;
    };
    fact[0] = 1;
    for (int i = 1; i <= n; i += 1) {
        (fact[i] = fact[i-1] * i) %= MOD;
    }
    ifact.back() = powm(fact.back(), MOD-2);
    for (int i = n-1; i >= 0; i -= 1) {
        (ifact[i] = ifact[i+1] * (i+1)) %= MOD;
    }
    sort(a.begin(), a.end());
    auto C = [&] (int n, int k) -> int {
        if (k > n) {
            return 0;
        }
        int ret = (fact[n]*ifact[n-k])%MOD*ifact[k]%MOD;
        return ret;
    };
    int ans = 0;
    for (int i = 0; i < n; i += 1) {
        int less = i;
        int more = n-i-1;
        (ans += a[i]%MOD*C(less, k-1)) %= MOD;
        (ans += (MOD-a[i])*C(more, k-1)) %= MOD;
    }
    cout << ans << "\n";
}