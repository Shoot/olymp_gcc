#include <bits/stdc++.h>

using namespace std;
#define endl "\n"
using ll = long long;
const ll INF = 1e18;
mt19937 mt(time(0));

void solve() {
    ll q;
    cin >> q;
    multiset<pair<long long, long long>> b_segments; // non-intersecting !!!
    ll b_length = 0;
    auto nvm_black = [&](ll &l, ll &r) -> void {
        while (1) { // fully inside || sprava
            auto it = b_segments.lower_bound({l, -INF});
            if (it == b_segments.end()) {
                break;
            }
            if (it->second > r) { // sprava
                if (it->first <= r + 1) {
                    l = min(l, it->first);
                    r = max(r, it->second);
                    ll prev_l = it->second - it->first + 1;
                    b_length -= prev_l;
                    b_segments.erase(it);
                }
                break;
            }
            // fully inside
            b_length -= it->second - it->first + 1;
            b_segments.erase(it);
        }
        auto it = b_segments.lower_bound({l, -INF});
        if (it != b_segments.begin()) { // sleva
            it = prev(it);
            if (it->second >= l - 1) {
                l = min(l, it->first);
                r = max(r, it->second);
                ll prev_l = it->second - it->first + 1;
                b_length -= prev_l;
                b_segments.erase(it);
            }
        }
    };
    while (q--) {
        char c;
        cin >> c;
        ll l, d;
        cin >> l >> d;
        ll r = l + d - 1;
        if (c == 'W') {
            while (1) { // fully inside || sprava
                auto it = b_segments.lower_bound({l, -INF});
                if (it == b_segments.end()) {
                    break;
                }
                if (it->second > r) { // sprava
                    if (it->first <= r) {
                        pair<ll, ll> nw = {r + 1, it->second};
                        ll prev_l = it->second - it->first + 1;
                        ll nw_l = nw.second - nw.first + 1;
                        assert(nw_l < prev_l);
                        assert(nw_l > 0);
                        b_segments.erase(it);
                        b_segments.insert(nw);
                        b_length -= prev_l;
                        b_length += nw_l;
                    }
                    break;
                }
                // fully inside
                b_length -= it->second - it->first + 1;
                b_segments.erase(it);
            }
            auto it = b_segments.lower_bound({l, -INF});
            if (it != b_segments.begin()) { // sleva
                it = prev(it);
                if (it->second >= l) {
                    if (it->second > r) {
                        // BBBwwBBB
                        //    !!
                        pair<ll, ll> nw1 = {it->first, l - 1};
                        pair<ll, ll> nw2 = {r+1, it->second};
                        ll prev_l = it->second - it->first + 1;
                        ll nw1_l = nw1.second - nw1.first + 1;
                        ll nw2_l = nw2.second - nw2.first + 1;
                        assert(nw1_l < prev_l);
                        assert(nw1_l > 0);
                        assert(nw2_l > 0);
                        b_segments.erase(it);
                        b_segments.insert(nw1);
                        b_segments.insert(nw2);
                        b_length -= prev_l;
                        b_length += nw1_l;
                        b_length += nw2_l;
                    } else {
                        pair<ll, ll> nw = {it->first, l - 1};
                        ll prev_l = it->second - it->first + 1;
                        ll nw_l = nw.second - nw.first + 1;
                        assert(nw_l < prev_l);
                        assert(nw_l > 0);
                        b_segments.erase(it);
                        b_segments.insert(nw);
                        b_length -= prev_l;
                        b_length += nw_l;
                    }
                }
            }
        } else {
            nvm_black(l, r);
            b_segments.insert({l, r});
            b_length += r - l + 1;
        }
        cout << b_segments.size() << " " << b_length << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll tt = 1;
    while (tt--)
        solve();
    return 0;
}