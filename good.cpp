#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 53161247837439787ll;
const int base = 503;
int mul(int a, int b) {
    return __int128(a)*b%MOD;
}
int powm(int a, int b) {
    int ans = 1;
    while (b) {
        if (b&1) {
            ans = mul(ans, a);
        }
        a = mul(a, a);
        b >>= 1;
    }
    return ans;
}
signed main() {
    int ibase = powm(base, MOD-2);
    const int n = 2;
    vector<string> strings(n);
    for (auto &x : strings) {
        cin >> x;
    }
    int sz = strings[0].size();
    strings[1] += strings[1];
    vector<int> basepow(100000+1);
    vector<int> ibasepow(100000+1);
    basepow[0] = 1;
    ibasepow[0] = 1;
    for (int i = 1; i <= 100000; i += 1) {
        basepow[i] = mul(basepow[i-1], base);
    }
    for (int i = 1; i <= 100000; i += 1) {
        ibasepow[i] = mul(ibasepow[i-1], ibase);
    }
    vector<vector<int>> hash(n);
    for (int w = 0; w < n; w += 1) {
        hash[w].assign(strings[w].size()+1, 0);
        for (int i = 1; i <= strings[w].size(); i += 1) {
            hash[w][i] = hash[w][i-1];
            (hash[w][i] += mul(strings[w][i-1], basepow[i-1])) %= MOD;
        }
    }
    auto get_hash = [&] (int w, int l, int r) -> int {
        if (l <= r) {
            return mul((hash[w][r]-hash[w][l-1]+MOD)%MOD, ibasepow[l-1]);
        }
        return 0ll;
    };
    for (int i = 1; i <= sz; i += 1) {
        if (get_hash(1, i, i+sz-1) == get_hash(0, 1, strings[0].size())) {
            cout << i-1 << "\n";
            return 0;
        }
    }cout << -1 << "\n";
}