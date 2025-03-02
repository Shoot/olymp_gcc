#include <bits/stdc++.h>
using namespace std;
signed main() {
    long long btsz;
    cin >> btsz;
    long long N = 1LL << btsz;
    vector<long long> P(N), F(N);
    for (long long i = 0; i < N; i++) {
        cin >> P[i];
        F[i] = P[i];
    }
    for (long long bt = 0; bt < btsz; bt += 1)
    for (long long i = 0; i < N; i += 1) {
        if (i&(1LL << bt)) {
            F[i] -= F[i-(1LL << bt)];
        }
    }
    for (const auto &x : F) {
        cout << x << " ";
    }cout << "\n";
}
