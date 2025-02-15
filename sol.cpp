#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 53161247837439787ll;
const int base = 101;
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
    int32_t n;
    cin >> n;
    vector<string> strings(n);
    for (auto &x : strings) {
        cin >> x;
    }
    while (strings.size() != 5) {
        strings.push_back(strings.back());
    }
    n = 5;
    assert(n == strings.size());
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
            (hash[w][i] += mul(strings[w][i-1]-'A'+1, basepow[i-1])) %= MOD;
        }
    }
    auto get_hash = [&] (int w, int l, int r) -> int {
        if (l <= r) {
            return mul((hash[w][r]-hash[w][l-1]+MOD)%MOD, ibasepow[l-1]);
        }
        assert(false);
        return 0ll;
    };
    vector<vector<int>> got(5);
    for (int i = 1; i < 5; i += 1) {
        got[i].reserve(3000*3001/2);
    }
    for (int w = 1; w < n; w += 1)
        for (int l = 1; l <= strings[w].size(); l += 1) {
            for (int r = l; r <= strings[w].size(); r += 1) {
                got[w].push_back(get_hash(w, l, r));
            }
        }
    for (auto &x : got) {
        sort(x.begin(), x.end());
    }
    vector<pair<int,int32_t>> check;
    check.reserve(3000*3001/2);
    for (int l = 1; l <= strings[0].size(); l += 1) {
        for (int r = l; r <= strings[0].size(); r += 1) {
            check.push_back({get_hash(0, l, r), r-l+1});
        }
    }
    sort(check.begin(), check.end());
    int32_t maxi = 0;
    int it1 = 0, it2 = 0, it3 = 0, it4 = 0;
    for (const auto &[x, len] : check) {
        while (it1 < got[1].size() && got[1][it1] < x) {
            it1 += 1;
        }
        while (it2 < got[2].size() && got[2][it2] < x) {
            it2 += 1;
        }
        while (it3 < got[3].size() && got[3][it3] < x) {
            it3 += 1;
        }
        while (it4 < got[4].size() && got[4][it4] < x) {
            it4 += 1;
        }
        if (it1 == got[1].size() || it2 == got[2].size() || it3 == got[3].size() || it4 == got[4].size()) {
            break;
        }
        if (got[1][it1] == x && got[2][it2] == x && got[3][it3] == x && got[4][it4] == x) {
            maxi = max(maxi, len);
        }
    }
    cout << maxi << "\n";
}