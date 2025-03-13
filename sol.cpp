#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(1<<k);
    for (int i = 0; i < n; i += 1) {
        string s;
        cin >> s;
        int su = 0;
        for (int j = 0; j < k; j += 1) {
            if (s[j] == '+') {
                su += 1 << j;
            }
        }
        a[su] += 1;
    }
    auto b = a;
    for (int bt = 0; bt < k; bt += 1) {
        for (int i = 0; i < (1 << k); i += 1) {
            if (!(i&(1<<bt))) continue;
            a[i] += a[i^(1<<bt)];
        }
    }
    int su = 0;
    for (int i = 0; i < (1 << k); i += 1) {
        if (b[i]) {
            su += (a[i] - b[i])*b[i];
        }
    }
    cout << su << "\n";
}