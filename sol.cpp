#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using ll = long long;
using namespace std;

signed main () {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
//    int tt;
//    cin >> tt;
//    while (tt--)
//        solve()
    int N = 1e6+3;
    vector<int> p(N+1);
    for (int i=2; i<=N; ++i) {
        if (p[i] != 0) continue;
        for (int j=i; j <= N; j+=i) {
            if (p[j] == 0) p[j] = i;
            else p[j] = min(p[j], i);
        }
    }
    int Q; cin >> Q;
    while (Q--) {
        int q;
        cin >> q;
        if (q <= 1) {
            cout << "No answer" << '\n';
            continue;
        }
        while (q != 1) {
            int v = p[q];
            while (q%v==0) {
                q/=v;
                cout << v << " ";
            }
        }
        cout << '\n';
    }
    return 0;
}