#include <bits/stdc++.h>
 using namespace std;
typedef unsigned long long ull;
int main()
{
    int P;
    cin >> P;
    int max_mod = 1;
    for (int i = 1; i <= P; i++) {
        max_mod = max_mod * i / gcd(max_mod, i); // = LCM of fact(P)
    }
    cout << max_mod << endl;
    assert(max_mod <= 720720);
    vector<int> r(P);
    for (int &i : r) {
        cin >> i;
    }
    vector<vector<__int128>> dp(2, vector<__int128>(max_mod, 0));
    for (int i = 1; i < P; i++) {
        dp[0][i] = 1;
    }
    int cur_layer = 0;
    for (int i = 1; i < P; i++) {
        cur_layer ^= 1;
        for (int j = 0; j < max_mod; j++){
            dp[cur_layer][j] = 0;
        }
        for (int origin = 0; origin < max_mod; origin++) {
            if (origin % i == r[i - 1]) {
                int destL = (origin * P) % max_mod;
                int destR = (origin * P) % max_mod + P - 1;
                dp[cur_layer][destL] += dp[cur_layer ^ 1][origin]; // dp[cur_layer][destL] - НАЧАЛО отрезка
                if (destR + 1 < max_mod) { // если нужно отмечать конец отрезка
                    dp[cur_layer][destR + 1] -= dp[cur_layer ^ 1][origin]; // dp[cur_layer][destR] - конец отрезка
                } else if (destR >= max_mod) {
                    dp[cur_layer][0] += dp[cur_layer ^ 1][origin]; // продолжаем отрезок (вышли за модуль и поэтому обнулились)
                    destR %= max_mod;
                    if (destR + 1 < max_mod) { // если нужно отмечать конец отрезка
                        dp[cur_layer][destR + 1] -= dp[cur_layer ^ 1][origin]; // dp[cur_layer][destR] - конец отрезка
                    }
                }
            }
        }
        for (int j = 1; j < max_mod; j++) {
            dp[cur_layer][j] += dp[cur_layer][j - 1];
        }
    }
    __int128 result = 0;
    for (int i = 0; i < max_mod; i++) {
        if (i % P == r[P - 1]) { // ensuring last P_i
            result += dp[cur_layer][i];
        }
    }
    cout << (unsigned long long)result;
    return 0;
}