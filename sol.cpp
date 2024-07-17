#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
#define all(x) x.begin(), x.end()
#define endl '\n';
using namespace std;
#ifdef LOCAL
#include <algo/debug.h>
#else
#define debug(...) 68
#endif
const ll N = 1e5+5;
struct difficulty {
    int value = -1;
};

void solve () {
    int n, m;
    cin >> n >> m;
    vector<string> tasks (n);
    for (string & j: tasks) cin >> j;
    vector<string> course (m);
    for (string & j: course) cin >> j;
    int not_in_course; cin >> not_in_course;
    map<string, difficulty> a;
    for (int i=0; i<m; i++) {
        difficulty x; cin >> x.value;
        a[course[i]] = x;
    }
    int tot=0;
    for (const string& j: tasks) {
        difficulty diff = a[j];
        if (diff.value != -1)
            tot += diff.value;
        else
            tot += not_in_course;
    }
    cout << tot << endl;
}

int32_t main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}