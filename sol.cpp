#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }
    vector<map<int,int>> cnt(n);
    cnt[0][a[0]] = 1;
    for (int i = 1; i < n; i += 1) {
        cnt[i][a[i]] = 1;
        for (const auto &[x, y] : cnt[i-1]) {
            cnt[i][__gcd(a[i], x)] += y;
        }
    }
    map<int,int> mp;
    for (const auto &x : cnt) {
        for (const auto &[v, c] : x) {
            mp[v] += c;
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i += 1) {
        int x;
        cin >> x;
        cout << mp[x] << "\n";
    }
}