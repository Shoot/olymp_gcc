#include <bits/stdc++.h>
using namespace std;
__int128 su(__int128 l, __int128 r) {
    return ((r-l)*(r+l)+r+l)/2;
}
std::ostream& operator<<(std::ostream& s, __int128_t value){
    string digits;
    do {
        digits.push_back("0123456789"[value % 10]);
        value /= 10;
    } while (value != 0);
    reverse(digits.begin(), digits.end());
    s << digits;
    return s;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    vector<pair<__int128, __int128>> ask;
    for (__int128 i = 0; i < T; i += 1) {
        int n;
        cin >> n;
        ask.push_back({n, i});
    }
    sort(ask.begin(), ask.end());
    __int128 last = 0;
    __int128 second = 0;
    __int128 it = 0;
    vector<pair<__int128, __int128>> ans(T);
    for (__int128 i = 0; i <= 2'100'000; i += 1) {
        __int128 l = last + 1;
        __int128 r = l + 2 * i;
        while (it < T && ask[it].first == i) {
            ans[ask[it].second] = {second, su(l, r) - second};
            it += 1;
        }
        second = su(l, r) - second;
        last = r;
    }
    for (const auto &[a, b] : ans) {
        cout << a << " " << b << "\n";
    }
}