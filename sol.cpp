#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize("O3", "unroll-loops")
//#pragma GCC target("avx2", "popcnt")
signed main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int ans = 0;
    // maximise b
    // aaabbb
    // 123210
    vector<vector<int>> a(300);
    for (int i = 0; i < n; i += 1) {
        a[s[i]].push_back(i);
    }
    for (char one = 'a'; one <= 'z'; one += 1) {
        for (char another = 'a'; another <= 'z'; another += 1) {
            if (one == another) {
                continue;
            }
            int DELM = 0;
            int last = -1;
            int DEL = 0;
            int DELm1 = 0;
            int DELMAX = 0;
            int DELMAXm1 = 0;
            int it1 = 0, it2 = 0;
            for (int j = 0; j < a[one].size()+a[another].size(); j += 1) {
                int i = -1;
                if (it2 == a[another].size() || it1 != a[one].size() && a[one][it1] < a[another][it2]) {
                    i = a[one][it1++];
                } else {
                    i = a[another][it2++];
                }

                DEL = (s[i] == another) - (s[i] == one);
                DEL += DELm1;
                DELm1 = DEL;
                DELMAX = max(DEL, DELMAXm1);
                if (s[i] == another) {
                    if (i) {
                        DELM = DELMAXm1;
                    }
                    last = i;
                }
                if (last == -1) {
                    continue;
                }
                ans = max(ans, -DEL+DELM);
                DELMAXm1 = DELMAX;
            }
        }
    }
    cout << ans << "\n";
}