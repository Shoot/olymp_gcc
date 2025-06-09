#include <bits/stdc++.h>
using namespace std;
#define int long long
#define YES(x) cout << (x?"YES\n":"NO\n")
#define NO(x) cout << (x?"NO\n":"YES\n")
#ifdef LO
#pragma GCC optimize("trapv")
#endif
#ifndef LO
#pragma GCC optimize("Ofast,unroll-loops")
#endif
constexpr int MOD = (119<<23)+1;
//constexpr int MOD = 967276608647009887ll;
//constexpr int MOD = 1e9+7;
signed main() {
#ifndef LO
    clog << "FIO\n";
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
    int n=1e9;
    vector<int> X(12);
    for (int i = 0; i < 12; i += 1) {
        X[i] = n%10;
        n /= 10;
    }
    int curr = 0;
    vector<pair<string, int>> saved;
    auto save = [&] () -> void {
        saved.push_back({to_string(curr)+to_string(curr+1), curr});
        sort(saved.back().first.begin(), saved.back().first.end());
    };
    auto cnt = [&] (auto f, int pos, int prev, bool less, bool first, bool second, bool break9s) -> void {
        if (pos == 0) {
            if (break9s) {
                curr *= 10;
                curr += 9;
                save();
                curr /= 10;
                return;
            }
            if (less) {
                for (int i = !first; i <= 9; i += 1) {
                    curr *= 10;
                    curr += i;
                    save();
                    curr /= 10;
                }
                return;
            }
            for (int i = !first; i <= min(9ll, less?9ll:X[pos]); i += 1) {
                curr *= 10;
                curr += i;
                save();
                curr /= 10;
            }
            return;
        }
        int ret = 0;
        if (first&&!second) { // zeros after first non-zero
            curr *= 10;
            curr += 0;
            f(f, pos - 1, prev, less || (0 < X[pos]), true, false, break9s);
            curr /= 10;
        }
        if (!break9s) {
            for (int i = first&&!second; i < prev; i += 1) { // create small char before nines
                curr *= 10;
                curr += i;
                f(f, pos-1, i, less||(i<X[pos]), first||i, second||(first&&i), true);
                curr /= 10;
            }
        }
        if (break9s) {
            if (less || 9<=X[pos]) {
                curr *= 10;
                curr += 9;
                f(f, pos-1, 9, less||(9<X[pos]), true, second||9, true);
                curr /= 10;
            }
            return;
        }
        if (first) {
            for (int i = max(prev, 1ll); i <= min(9ll, less?9ll:X[pos]); i += 1) {
                curr *= 10;
                curr += i;
                f(f, pos-1, i, less||(i<X[pos]), true, true, break9s);
                curr /= 10;
            }
        } else {
            for (int i = prev; i <= min(9ll, less?9ll:X[pos]); i += 1) {
                curr *= 10;
                curr += i;
                f(f, pos-1, i, less||(i<X[pos]), i>0, false, break9s);
                curr /= 10;
            }
        }
        return;
    };
    cnt(cnt, 11, 0, false, false, false, false);
    vector<int> nw;
    sort(saved.begin(), saved.end());
    nw.push_back(saved.front().second);
    for (int i = 1; i < saved.size(); i += 1) {
        if (saved[i].first != saved[i-1].first) {
            nw.push_back(saved[i].second);
        }
    }
    sort(nw.begin(), nw.end());
    int T = 1;
    cin >> T;
    for (int tt = 0; tt < T; tt += 1) {
        int N;
        cin >> N;
        cout << upper_bound(nw.begin(), nw.end(), N)-nw.begin() << "\n";
    }
}