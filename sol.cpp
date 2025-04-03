#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    struct Event {
        bool tp;
        int inc;
        int32_t pos;
    };
    vector<Event> events, events2;
    events2.reserve(5e6);
    events.reserve(3e6);
    vector<int32_t> a(n);
    for (auto &x : a) {
        cin >> x;
    }
    int q;
    cin >> q;
    for (int ii = 0; ii < q; ii += 1) {
        int l, r, d;
        cin >> l >> r >> d;
        l -= 1;
        r -= 1;
        events.push_back({0, d, (int32_t)l});
        events.push_back({0, -d, (int32_t)r+1});
        events2.push_back({0, -(r-l+1)*d, (int32_t)r+1});
//        events.push_back({0, (r-l+1)*d, (int32_t)r+1+1});
    }
    vector<int> nw(n);
    for (int32_t i = 0; i < n; i += 1) {
        events.push_back({1, 0, i});
    }
    sort(events.begin(), events.end(), [](const Event & one, const Event& other) {
        return tie(one.pos, one.tp) < tie(other.pos, other.tp);
    });
    int curr = 0;
    for (const auto &[tp, inc, pos] : events) {
        if (tp == 0) {
            curr += inc;
        } else {
            nw[pos] = curr;
        }
    }
    events.clear();
    for (int32_t i = 0; i < n; i += 1) {
        events2.push_back({0, nw[i], i});
    }
    for (int32_t i = 0; i < n; i += 1) {
        events2.push_back({1, 0, i});
    }
    for (int32_t i = 0; i < n; i += 1) {
        events2.push_back({0, a[i], i});
        events2.push_back({0, -a[i], i+1});
    }
    sort(events2.begin(), events2.end(), [](const Event & one, const Event& other) {
        return tie(one.pos, one.tp) < tie(other.pos, other.tp);
    });
    curr = 0;
    for (const auto &[tp, inc, pos] : events2) {
        if (tp == 0) {
            curr += inc;
        } else {
            cout << curr << " ";
        }
    }cout << "\n";
}