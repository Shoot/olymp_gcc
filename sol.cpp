#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
#define all(value) value.begin(), value.end()
#define endl '\n'
using namespace std;
#ifdef LOCAL
#include <algo/debug.h>
#else
#define debug(...) 68
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
constexpr int N = (int)(2e5*1.2);
void solve() {
    int n; cin >> n;
    string s; cin >> s;
    vector<int> count(n+1, 0);
    for (int i = n - 1; i >= 0; --i) {
        if (s[i] == 'F') {
            count[i] = count[i + 1] + 1;
        } else {
            count[i] = 0;
        }
    }
    int cur_orientation = 1;
    set<int> se;
    int base_or = 1;
    int base = 0;
    for (char i : s) {
        if (i == 'L') {
            base_or = -1;
        } else if (i == 'F') {
            base += base_or;
        } else {
            base_or = 1;
        }
    }
    for (int i=0; i<s.size(); i++) {
        if (s[i] == 'L') {
            se.insert(base + 2*count[i+1]); // L -> R
            se.insert(base + cur_orientation + (cur_orientation == 1?2*count[i+1]:0)); // L -> F
            cur_orientation = -1;
        } else if (s[i] == 'F') {
            se.insert(base - cur_orientation + (cur_orientation == -1?2*count[i+1]:0)); // F -> R
            se.insert(base - cur_orientation - (cur_orientation == 1?2*count[i+1]:0)); // F -> L
        } else {
            se.insert(base - 2*count[i+1]); // R -> L
            se.insert(base + cur_orientation - (cur_orientation == -1?2*count[i+1]:0)); // R -> F
            cur_orientation = 1;
        }
    }
    cout << se.size() << endl;
}
int32_t main (int argc, char* argv[]) {
    bool use_fast_io = true;
    for (int i = 1; i < argc; ++i)
        if (string(argv[i]) == "-local-no-fast-io") {
            use_fast_io = false;
            break;
        }
    if (use_fast_io) {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cerr.tie(nullptr);
    }
    ll tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}