#include <bits/stdc++.h>
using namespace std;
signed main() {
    int btsz;
    cin >> btsz;
    int N = 1LL << btsz;
    vector<int> F(N), P(N);
    for (int i = 0; i < N; i++) {
        cin >> F[i];
        P[i] = F[i];
    }
    for (int bt = 0; bt < btsz; bt += 1)
    for (int i = 0; i < N; i += 1) {
        if (i&(1LL<<bt)) {
            P[i] += P[i-(1LL<<bt)];
        }
    }
    for (const auto &x : P) {
        cout << x << " ";
    }cout << "\n";
}
