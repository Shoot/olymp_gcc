#include <iostream>
#include <vector>
using namespace std;
constexpr long long MOD = 1e9 + 7;
signed main() {
    long long n;
    cin >> n;
    vector<long long> ifact(n+1);
    ifact[0] = 1;
    ifact[1] = 0;
    for (long long i = 2; i <= n; i += 1) {
        ifact[i] = (i-1)*((ifact[i-1]+ifact[i-2])%MOD)%MOD;
    }
    cout << ifact.back() << "\n";
}