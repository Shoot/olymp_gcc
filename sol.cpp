#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    constexpr int MOD = 1e9+7;
    string s, t;
    int k;
    cin >> s >> t >> k;
    // сохраняем позиции первой, второй, .. букв строки t которые находятся внутри s.
    // dp[сколько символов из копий s уже полностью позади][колво покрытых символов из строки t] = number_of_ways
    // dp[колво покрытых символов из строки t] = number_of_ways
    vector<vector<int>> where(t.size());
    for (int i = 0; i < s.size(); i += 1) {
        for (int j = 0; j < t.size(); j += 1) {
            if (s[i] == t[j]) {
                where[j].push_back(i);
            }
        }
    }
    vector<int> dp(t.size()+1);
    dp[0] = 1;
    vector<int> nwdp(t.size()+1);
    int ans = 0;
    for (int pozad = 0; pozad < s.size()*k; pozad += 1) {
        fill(nwdp.begin(), nwdp.end(), 0ll);
        for (int pokr = t.size()-1; pokr >= 0; pokr -= 1) if (dp[pokr]) {
            if (s[pozad%s.size()] == t[pokr]) {
                (dp[pokr+1] += dp[pokr]) %= MOD;
            }
        }
    }
    cout << dp.back() << "\n";
}