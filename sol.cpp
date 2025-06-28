//#include "testlib.h"
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
template <typename T> using ordered_set =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define int long long
#define YES(x) cout << (x?"YES\n":"NO\n")
#define NO(x) cout << (x?"NO\n":"YES\n")
#ifdef LO
#pragma GCC optimize("trapv")
#endif
#ifndef LO
#pragma GCC optimize("Ofast,unroll-loops")
#endif
//constexpr int MOD = (119<<23)+1;
//constexpr int MOD = 967276608647009887ll;
//constexpr int MOD = 1e9+7;
constexpr int INF = 1e18;
signed main() {
#ifndef LO
    clog << "FIO\n";
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
#ifdef LO
    cout << unitbuf;
#endif
    ifstream fin("nice.txt");
    vector<int> dp(2);
    vector<pair<int,int>> ch(2);
    vector<int> palka(2);
    for (int i = 2; ; i += 1) {
        string s;
        if (!getline(fin, s)) {
            break;
        }
        dp.push_back({});
        ch.push_back({});
        palka.push_back({});
        stringstream ss(s);
        getline(ss, s, '(');
        getline(ss, s, ',');
        assert(stoi(s) == i);
        getline(ss, s, ' ');
        getline(ss, s, ' ');
        dp[i] = stoi(s);
        getline(ss, s, '|');
        ch[i].first = stoi(s);
        getline(ss, s, ' ');
        getline(ss, s, '|');
        ch[i].second = stoi(s);
        getline(ss, s, ' ');
        getline(ss, s);
        palka[i] = stoi(s);
//        cout << i << " " << dp[i] << " " << palka[i] << " " << ch[i].first << " " << ch[i].second << "\n";
        assert(ss.eof());
    }
    cout << "MAX n: " << dp.size()-1 << "\n";
    int curr = 1;
    auto print = [&] (auto f, const int x) -> int {
        assert(x < dp.size());
        if (!x) {
            return -1;
        }
        int U = curr++;
        int u = U;
        for (int i = 0; i < palka[x]-1; i += 1) {
            int v = curr++;
            cout << u << " " << v << "\n";
            u = v;
        }
        int v1 = f(f, ch[x].first), v2 = f(f, ch[x].second);
        if (v1 != -1) {
            cout << u << " " << v1 << "\n";
        }
        if (v2 != -1) {
            cout << u << " " << v2 << "\n";
        }
        return U;
    };
    int n;
    while (cin >> n) {
        cout << dp[n] << ":\n";
        print(print, n);
    }
}