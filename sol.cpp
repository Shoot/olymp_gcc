//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
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
#define int __int128
using namespace std;
void solve() {
    struct node {
        int capacity_left; // value
        int idx, add;
    };
    struct node2 {
        int dead; // value
        int idx, add;
    };
    ll n, queries; cin >> n >> queries;
    vector<int> BIT_getting_dead_number_on_segment_updating_on_point(n + 1);
    vector<node> ST(4 * n + 9);
    vector<node2> ST2(4 * n + 9);
    vector<ll> kills_right(n + 1), capacity(n + 1), dead_init(n+1, 0);
    for (int i = 1; i <= n; ++i){
        cin >> kills_right[i] >> capacity[i];
        kills_right[i] -= 1;
    }
    function<node(node, node)> merge = [&](node a, node b) {
        return (a.capacity_left < b.capacity_left)?a:b;
    };
    function<node2(node2, node2)> merge2 = [&](node2 a, node2 b) {
        node2 temp{};
        temp.dead = a.dead+b.dead;
        return temp;
    };
    function<void(int, int, int)> build = [&](int current_vertex, int corresp_l, int corresp_r) {
        if (corresp_l == corresp_r) {
            ST[current_vertex] = {capacity[corresp_l], corresp_l, 0};
            return;
        }
        int middle_idx = (corresp_l + corresp_r) >> 1;
        build(current_vertex * 2, corresp_l, middle_idx);
        build(current_vertex * 2 + 1, middle_idx + 1, corresp_r);
        ST[current_vertex] = merge(ST[current_vertex * 2], ST[current_vertex * 2 + 1]);
    };
    function<void(int, int, int)> build2 = [&](int current_vertex, int corresp_l, int corresp_r) {
        if (corresp_l == corresp_r) {
            ST2[current_vertex] = {dead_init[corresp_l], corresp_l, 0};
            return;
        }
        int middle_idx = (corresp_l + corresp_r) >> 1;
        build2(current_vertex * 2, corresp_l, middle_idx);
        build2(current_vertex * 2 + 1, middle_idx + 1, corresp_r);
        ST2[current_vertex] = merge2(ST2[current_vertex * 2], ST2[current_vertex * 2 + 1]);
    };
    function<void(int)> push_down = [&](int current_vertex) {
        int add = ST[current_vertex].add;
        ST[current_vertex * 2].add += add;
        ST[current_vertex * 2 + 1].add += add;
        ST[current_vertex * 2].capacity_left += add;
        ST[current_vertex * 2 + 1].capacity_left += add;
        ST[current_vertex].add = 0;
    };
    function<void(int)> push_down2 = [&](int current_vertex) {
        int add = ST2[current_vertex].add;
        ST2[current_vertex * 2].add += add;
        ST2[current_vertex * 2 + 1].add += add;
        ST2[current_vertex * 2].dead += add;
        ST2[current_vertex * 2 + 1].dead += add;
        ST2[current_vertex].add = 0;
    };
    function<void(int, int, int, int, int, int)> add_on_segment = [&](int current_vertex, int corresp_l, int corresp_r, int l, int r, int x) {
        if (l > r)
            return;
        if (corresp_l == l && corresp_r == r) {
            ST[current_vertex].add += x;
            ST[current_vertex].capacity_left += x;
            return;
        }
        int middle_idx = (corresp_l + corresp_r) >> 1;
        push_down(current_vertex);
        add_on_segment(current_vertex * 2, corresp_l, middle_idx, l, min(r, middle_idx), x);
        add_on_segment(current_vertex * 2 + 1, middle_idx + 1, corresp_r, max(l, middle_idx + 1), r, x);
        ST[current_vertex] = merge(ST[current_vertex * 2], ST[current_vertex * 2 + 1]);
        ST[current_vertex].add = 0;
    };
    function<void(int, int, int, int, int, int)> add_on_segment2 = [&](int current_vertex, int corresp_l, int corresp_r, int l, int r, int x) {
        if (l > r)
            return;
        if (corresp_l == l && corresp_r == r) {
            ST2[current_vertex].add += x;
            ST2[current_vertex].dead += x;
            return;
        }
        int middle_idx = (corresp_l + corresp_r) >> 1;
        push_down2(current_vertex);
        add_on_segment2(current_vertex * 2, corresp_l, middle_idx, l, min(r, middle_idx), x);
        add_on_segment2(current_vertex * 2 + 1, middle_idx + 1, corresp_r, max(l, middle_idx + 1), r, x);
        ST2[current_vertex] = merge2(ST2[current_vertex * 2], ST2[current_vertex * 2 + 1]);
        ST2[current_vertex].add = 0;
    };
    function<node(int, int, int, int, int)> get = [&](int current_vertex, int corresp_l, int corresp_r, int l, int r) {
        if (l > r)
            return node{(int)(1e25), 0, 0};
        if (corresp_l == l && corresp_r == r)
            return ST[current_vertex];
        int middle_idx = (corresp_l + corresp_r) >> 1;
        push_down(current_vertex);
        return merge(
                get(current_vertex * 2, corresp_l, middle_idx, l, min(r, middle_idx)),
                get(current_vertex * 2 + 1, middle_idx + 1, corresp_r, max(l, middle_idx + 1), r)
        );
    };
    function<node2(int, int, int, int, int)> get2 = [&](int current_vertex, int corresp_l, int corresp_r, int l, int r) {
        if (l > r)
            return node2{0, 0};
        if (corresp_l == l && corresp_r == r)
            return ST2[current_vertex];
        int middle_idx = (corresp_l + corresp_r) >> 1;
        push_down2(current_vertex);
        return merge2(
                get2(current_vertex * 2, corresp_l, middle_idx, l, min(r, middle_idx)),
                get2(current_vertex * 2 + 1, middle_idx + 1, corresp_r, max(l, middle_idx + 1), r)
        );
    };
//    function<void(int)> mark_as_dead = [&](int current_vertex) {
//        for (int i = current_vertex; i <= n; i |= i + 1)
//            BIT_getting_dead_number_on_segment_updating_on_point[i]++;
//    };
//    function<int(int)> get_dead_to_the_left = [&](int current_vertex) {
//        int res = 0;
//        for (int i = current_vertex; i >= 1; i = (i & (i + 1)) - 1)
//            res += BIT_getting_dead_number_on_segment_updating_on_point[i];
//        return res;
//    };
    function<void(int)> fall = [&](int killer_idx) {
        deque<int> deq;
        deq.push_back(killer_idx);
        add_on_segment(1, 1, n, killer_idx, killer_idx, 1e25);
        while (!deq.empty()) {
            int current_vertex = deq.front();
            deq.pop_front();
//            mark_as_dead(current_vertex);
            add_on_segment2(1, 1, n, current_vertex, current_vertex, 1);
            while (true) {
                node nxt = get(1, 1, n, current_vertex, min((int)n, current_vertex + kills_right[current_vertex]));
                if (nxt.capacity_left >= (int)1e20) break; // already fallen
                deq.push_back(nxt.idx);
                add_on_segment(1, 1, n, nxt.idx, nxt.idx, 1e25);
            }
        }
    };
    build(1, 1, n);
    build2(1, 1, n);
    while (queries--) {
        long long type; cin >> type;
        long long l, r; cin >> l >> r;
        if (type == 2) {
//            cout << (long long) (r - l + 1 - (get_dead_to_the_left(r) - get_dead_to_the_left(l - 1))) << endl;
//            for (auto j : BIT_getting_dead_number_on_segment_updating_on_point) {
//                cout << (ll) j << ' ';
//            }
//            cout << endl;
//            for (auto j : ST2) {
//                cout << (ll) j.dead << ' ';
//            }
//            cout << endl;
            cout << (long long) (r - l + 1 - get2(1, 1, n, l, r).dead) << endl;
            continue;
        }
        long long x; cin >> x;
        add_on_segment(1, 1, n, l, r, -x);
        while (ST[1].capacity_left <= 0) fall(ST[1].idx); // calling fall() bc min capacity is negative somewhere
    }
}

int32_t main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll tt = 1;
    while (tt--) solve();
    return 0;
}