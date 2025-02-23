#include <bits/stdc++.h>
using namespace std;
signed main() {
    string s;
    cin >> s;
    int n = int(s.size());
    int k;
    cin >> k;
    // [dist][0=to_right/1=to_left][rest]
    bool dp[201][2][51];
    memset(dp, 0, sizeof(dp));
    dp[100][0][k] = 1;
    bool nwdp[201][2][51];
    for (int i = 0; i < n; i += 1) {
        memset(nwdp, 0, sizeof(nwdp));
        for (int d = -100; d <= 100; d += 1) {
            for (int lr = 0; lr < 2; lr += 1) {
                for (int rest = 0; rest <= 50; rest += 1) {
                    if (dp[d+100][lr][rest]) {
                        if (rest >= 1) {
                            int nd = d;
                            int nlr = lr;
                            if (s[i] == 'T') {
                                if (lr) {
                                    nd -= 1;
                                } else {
                                    nd += 1;
                                }
                            } else {
                                nlr = 1 - lr;
                            }
                            if (nd+100 >= 0 && nd+100 <= 200)
                                for (int j = rest-1; j >= 0; j -= 2) {
                                    nwdp[nd+100][nlr][j] = true;
                                }
                        }
                        int nd = d;
                        int nlr = lr;
                        if (s[i] == 'T') {
                            nlr = 1 - lr;
                        }
                        if (s[i] == 'F') {
                            if (lr) {
                                nd -= 1;
                            } else {
                                nd += 1;
                            }
                        }
                        if (nd+100 >= 0 && nd+100 <= 200)
                            for (int j = rest; j >= 0; j -= 2) {
                                nwdp[nd+100][nlr][j] = true;
                            }
                    }
                }
            }
        }
        swap(dp, nwdp);
    }
    int maxi = -1e9;
    for (int d = -100; d <= 100; d += 1) {
        for (int lr = 0; lr < 2; lr += 1) {
            if (dp[d+100][lr][0]) {
                maxi = max(maxi, abs(d));
            }
        }
    }
    cout << maxi << "\n";
}