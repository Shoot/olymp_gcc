#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }
    vector<int> gte_right(n);
    vector<int> less_right(n);
    stack<int> st;
    a.push_back(1e9);
    st.push(n);
    for (int i = n-1; i >= 0; i -= 1) {
        while (a[i] > a[st.top()]) {
            st.pop();
        }
        gte_right[i] = st.top();
        st.push(i);
    }
    while (!st.empty()) {
        st.pop();
    }
    st.push(n);
    a.back() = -1e9;
    for (int i = n-1; i >= 0; i -= 1) {
        while (a[i] <= a[st.top()]) {
            st.pop();
        }
        less_right[i] = st.top();
        st.push(i);
    }
    vector<int> res;
    bool ans = true;
    auto is_good = [&] (auto f, int l, int r) -> pair<int,int> {
        pair<int,int> mn_mx = {a[l], a[l]};;
        if (l == r) {
            res.push_back(a[l]);
            return mn_mx;
        }
        if (a[l+1] < a[l]) {
            auto start_of_second_subtree = gte_right[l];
            auto [mn_1, mx_1] = f(f, l+1, min(r, start_of_second_subtree-1));
            ans &= mx_1 < a[l];
            mn_mx.first = min(mn_mx.first, mn_1);
            mn_mx.second = max(mn_mx.second, mx_1);
            if (start_of_second_subtree <= r) {
                auto [mn_2, mx_2] = f(f, start_of_second_subtree, r);
                ans &= mn_2 >= a[l];
                mn_mx.first = min(mn_mx.first, mn_2);
                mn_mx.second = max(mn_mx.second, mx_2);
            }
        } else {
            auto start_of_second_subtree = less_right[l];
            auto [mn_1, mx_1] = f(f, l+1, min(r, start_of_second_subtree-1));
            ans &= mn_1 >= a[l];
            mn_mx.first = min(mn_mx.first, mn_1);
            mn_mx.second = max(mn_mx.second, mx_1);
            if (start_of_second_subtree <= r) {
                auto [mn_2, mx_2] = f(f, start_of_second_subtree, r);
                ans &= mx_2 < a[l];
                mn_mx.first = min(mn_mx.first, mn_2);
                mn_mx.second = max(mn_mx.second, mx_2);
            }
        }
        res.push_back(a[l]);
        return mn_mx;
    };
    is_good(is_good, 0, n-1);
    if (ans) {
        cout << "YES\n";
        for (const auto &x : res) {
            cout << x << " ";
        }
        cout << "\n";
    } else {
        cout << "NO\n";
    }
}