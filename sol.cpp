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
    int n;
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
    vector<vector<vector<int>>> got(5);
    for (int i = 0; i < 5; i += 1) {
        got[i].resize(3001);
        for (int sz = 1; sz <= 3000; sz += 1) {
            got[i][sz].reserve(3000-sz+1);
        }
    }
    for (int w = 0; w < n; w += 1) {
        for (int l = 1; l <= strings[w].size(); l += 1) {
            for (int r = l; r <= strings[w].size(); r += 1) {
                got[w][r - l + 1].push_back(get_hash(w, l, r));
            }
        }
    }
    int l = 1, r = 3000;
    int good = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        for (int i = 0; i < 5; i += 1) {
            sort(got[i][mid].begin(), got[i][mid].end());
        }
        int it1 = 0, it2 = 0, it3 = 0, it4 = 0;
        for (const auto &x : got[0][mid]) {
            while (it1 < got[1][mid].size() && got[1][mid][it1] < x) {
                it1 += 1;
            }
            while (it2 < got[2][mid].size() && got[2][mid][it2] < x) {
                it2 += 1;
            }
            while (it3 < got[3][mid].size() && got[3][mid][it3] < x) {
                it3 += 1;
            }
            while (it4 < got[4][mid].size() && got[4][mid][it4] < x) {
                it4 += 1;
            }
            if (it1 == got[1][mid].size() || it2 == got[2][mid].size() || it3 == got[3][mid].size() || it4 == got[4][mid].size()) {
                break;
            }
            if (got[1][mid][it1] == x && got[2][mid][it2] == x && got[3][mid][it3] == x && got[4][mid][it4] == x) {
                l = mid + 1;
                good = mid;
                break;
            }
        }
        if (good != mid) {
            r = mid - 1;
        }
    }
    cout << good << "\n";
}