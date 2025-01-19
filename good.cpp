#include <bits/stdc++.h>
using namespace std;
long long MOD = 1e9+7;
inline long long powm(long long n, int k) {
    long long res = 1;
    while (k > 0) {
        if (k % 2) {
            res *= n;
            res %= MOD;
        }
        n *= n;
        n %= MOD;
        k /= 2;
    }
    return res;
}
signed main() {
    long long words, strings, length_of_each;
    cin >> words >> strings >> length_of_each;
    struct Word {
        long long len;
        long long type;
    };
    vector<Word> wrds(words);
    for (long long i = 0; i < words; i += 1) {
        cin >> wrds[i].len >> wrds[i].type;
    }
    vector<long long> last(words+1);
    vector<long long> ways_by_len(length_of_each+1);
    ways_by_len[0] = 1;
    for (long long i = 0; i <= length_of_each; i += 1) {
        for (const auto &[len, type] : wrds) {
            if (i + len <= length_of_each) {
                ways_by_len[i + len] = (ways_by_len[i + len] + ways_by_len[i]) % MOD;
                if (i + len == length_of_each) {
                    last[type] = (last[type] + ways_by_len[i]) % MOD;
                }
            }
        }
    }
    vector<long long> cnt(26);
    for (long long i = 0; i < strings; i += 1) {
        char c;
        cin >> c;
        cnt[c-'A'] += 1;
    }
    long long tot = 1;
    for (int i : cnt) {
        if (!i) continue;
        long long cnt = 0;
        for (int j: last) {
            if (!j) continue;
            cnt += powm(j, i);
            cnt %= MOD;
        }
        tot *= cnt;
        tot %= MOD;
    }
    cout << tot << "\n";
}