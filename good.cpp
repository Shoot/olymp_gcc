#include <bits/stdc++.h>
using namespace std;
string A = "A";
string B = "B";
string AB = "AB";
string BA = "BA";
vector<string> go = {A, B, AB, BA};
signed main() {
    int q;
    cin >> q;
    for (int ii = 0; ii < q; ii += 1) {
        string s;
        cin >> s;
        int n = int(s.size());
        int a, b, ab, ba;
        cin >> a >> b >> ab >> ba;
        if (a+b+2*ab+2*ba != n) {
            cout << "NO\n";
            continue;
        }
        bool dp[n+1][a+1][b+1][ab+1][ba+1];
        dp[0][0][0][0][0] = true;
        memset(dp, false, sizeof(dp));
        for (int i = 0; i < n; i += 1) {
            for (int aa = 0; aa < i; aa += 1) {
                for (int bb = 0; bb < i; bb += 1) {
                    for (int aabb = 0; aabb < i; aabb += 1) {
                        for (int bbaa = 0; bbaa < i; bbaa += 1) {

                        }
                    }
                }
            }
            for (const auto &x : go) {
                if (equal(x.begin(), x.end(), s.begin()+i)) {

                }
            }
        }
    }
}