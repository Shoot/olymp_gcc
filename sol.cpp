#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;
#ifdef LOCAL
#include <algo/debug.h>
#else
#define debug(...) 69
#endif
const int N = 1e5+5;

void solve () {
    int n;
    cin >> n;
    vector<int> a(n+1);
    int su = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        su += a[i];
    }
    bitset<N> shit;
    shit[0] = 1;
    for (int i = 1; i <= n; ++i) {
        shit |= shit << a[i];
    }
    int maxi = a[0];
    for (int i=0; i<=N-1000; i++) {
        if (not shit[i]) continue;
        maxi = max(i*(su-i), maxi);
    }
    cout << maxi << endl;
}

int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
//    int tt;
//    cin >> tt;
//    while (tt--)
        solve();
    return 0;
}