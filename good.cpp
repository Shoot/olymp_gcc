#include <bits/stdc++.h>
using namespace std;

int main () {
    int n;
    cin >> n;

    vector<int> a(n);
    int s = 0;
    vector<int> pref(n, 0);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        s += a[i];
        pref[i] = s;
    }

    int maxn = min(2*s/n+10, s+1);

    vector<vector<vector<int>>> dp(2, vector<vector<int>>(s + 1, vector<int>(maxn, 1e9)));

    for (int su = 0; su < maxn - 1; su++) {
        dp[0][su][su] = abs(pref[0] - su);
    }

    for (int i = 1; i < n; i++) {
        for (int su = 0; su <= s; su++) {
            for (int last = 0; last < maxn - 1; last++) {
                if (su - last >= 0) {
                    if (last - 1 >= 0) {
                        dp[i % 2][su][last] = min({
                                                          dp[(i + 1) % 2][su - last][last + 1],
                                                          dp[(i + 1) % 2][su - last][last - 1],
                                                          dp[(i + 1) % 2][su - last][last]
                                                  }) + abs(su - pref[i]);
                    } else {
                        dp[i % 2][su][last] = min({
                                                          dp[(i + 1) % 2][su - last][last + 1],
                                                          dp[(i + 1) % 2][su - last][last]
                                                  }) + abs(su - pref[i]);
                    }
                }
            }
        }
    }

    int ans = 1e9;
    for (int i = 0; i < maxn - 1; i++) {
        ans = min(ans, dp[(n - 1) % 2][s][i]);
    }

    cout << ans;

    return 0;
}