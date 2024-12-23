#include <bits/stdc++.h>
using namespace std;
int32_t main () {
    const int INF = 1e9;
    int n;
    cin >> n;
    vector<int> pref(n);
    for (int i = 0; i < n; i += 1) {
        cin >> pref[i];
        if (i != 0) pref[i] += pref[i-1];
    }
    int MAX_SU = 1.5e3+10;
    int MAX_VAL = pref.back()/n+n+10;
    MAX_VAL = min(MAX_VAL, MAX_SU);
    vector<vector<int>> dp(MAX_SU+2, vector<int>(MAX_VAL+2, INF));
    auto nw_dp = dp;
    for (int last = 0; last <= MAX_VAL; last += 1) {
        dp[last][last] = abs(pref[0]-last);
    }
    for (int i = 1; i < n; i += 1) {
        for (int su = 0; su <= MAX_SU; su += 1) {
            for (int last = 0; last <= MAX_VAL; last += 1) {
                if (su >= last) {
                    int diff = abs(su-pref[i]);
                    nw_dp[su][last] = dp[su-last][last+1];
                    nw_dp[su][last] = min(nw_dp[su][last], dp[su-last][last]);
                    if (last != 0) nw_dp[su][last] = min(nw_dp[su][last], dp[su-last][last-1]);
                    nw_dp[su][last] += diff;
                }
            }
        }
        swap(dp,nw_dp);
    }
    cout << *min_element(dp[pref.back()].begin(), dp[pref.back()].end()) << "\n";
    return 0;
}