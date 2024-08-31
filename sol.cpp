#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(value) value.begin(), value.end()
#define endl '\n'
#ifdef LOCAL
#include <algo/debug.h>
#else
#define debug(...) 68
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif

const int N = 3e5+10;
const int MAXN = 1e3; // Adjust based on your needs

// 2D Segment Tree Node
struct node {
    ll val;
    ll idx_x, idx_y;
    node() : val(0), idx_x(0), idx_y(0) {}
    node(ll _val, ll _idx_x, ll _idx_y) : val(_val), idx_x(_idx_x), idx_y(_idx_y) {}
};

// 2D Segment Tree Arrays
array<array<node, 4*MAXN>, 4*MAXN> tree;
vector<vector<ll>> matrix(MAXN, vector<ll>(MAXN));
vector<vector<ll>> pref_xor(MAXN, vector<ll>(MAXN));

node merge(node a, node b) {
    return (a.val > b.val) ? a : b;
}

// Build segment tree for a single dimension (1D)
void build_1D(array<node, 4*MAXN> &ST, vector<ll> &array, ll v, ll tl, ll tr) {
    if (tl == tr) {
        ST[v] = node(array[tl], tl, 0);
    } else {
        ll tm = (tl + tr) >> 1;
        build_1D(ST, array, v*2, tl, tm);
        build_1D(ST, array, v*2+1, tm+1, tr);
        ST[v] = merge(ST[v*2], ST[v*2+1]);
    }
}

// Build 2D segment tree
void build_2D(array<array<node, 4*MAXN>, 4*MAXN> &ST, vector<vector<ll>> &matrix, ll v, ll tl, ll tr, ll l, ll r) {
    if (tl == tr) {
        vector<ll> row(matrix[0].size());
        for (ll j = 0; j < matrix[0].size(); j++) {
            row[j] = matrix[tl][j];
        }
        build_1D(ST[tl], row, 1, 0, matrix[0].size() - 1);
    } else {
        ll tm = (tl + tr) >> 1;
        build_2D(ST, matrix, v*2, tl, tm, l, r);
        build_2D(ST, matrix, v*2+1, tm+1, tr, l, r);
        // For each row in this segment
        for (ll i = l; i <= r; i++) {
            ST[v][i] = merge(ST[v*2][i], ST[v*2+1][i]);
        }
    }
}

// Query 1D segment tree
node query_1D(array<node, 4*MAXN> &ST, ll l, ll r, ll v, ll tl, ll tr) {
    if (tl == l && tr == r) return ST[v];
    ll tm = (tl + tr) >> 1;
    if (r <= tm) {
        return query_1D(ST, l, r, v*2, tl, tm);
    } else if (l > tm) {
        return query_1D(ST, l, r, v*2+1, tm+1, tr);
    } else {
        return merge(query_1D(ST, l, tm, v*2, tl, tm), query_1D(ST, tm+1, r, v*2+1, tm+1, tr));
    }
}

// Query 2D segment tree
node query_2D(array<array<node, 4*MAXN>, 4*MAXN> &ST, ll x1, ll x2, ll y1, ll y2, ll v, ll tl, ll tr, ll l, ll r) {
    if (tl == x1 && tr == x2) {
        return query_1D(ST[v], y1, y2, 1, l, r);
    }
    ll tm = (tl + tr) >> 1;
    if (x2 <= tm) {
        return query_2D(ST, x1, x2, y1, y2, v*2, tl, tm, l, r);
    } else if (x1 > tm) {
        return query_2D(ST, x1, x2, y1, y2, v*2+1, tm+1, tr, l, r);
    } else {
        return merge(query_2D(ST, x1, tm, y1, y2, v*2, tl, tm, l, r),
                     query_2D(ST, tm+1, x2, y1, y2, v*2+1, tm+1, tr, l, r));
    }
}

void solve() {
    ll n, m;
    cin >> n >> m;
    matrix.resize(n+1, vector<ll>(m+1));
    pref_xor.resize(n+1, vector<ll>(m+1));

    // Read matrix and compute prefix XOR
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= m; j++) {
            cin >> matrix[i][j];
            pref_xor[i][j] = matrix[i][j] ^ pref_xor[i-1][j] ^ pref_xor[i][j-1] ^ pref_xor[i-1][j-1];
        }
    }

    // Build 2D segment tree
    build_2D(tree, matrix, 1, 1, n, 1, m);

    // Example Query
    ll x1, x2, y1, y2;
    cin >> x1 >> x2 >> y1 >> y2;
    node result = query_2D(tree, x1, x2, y1, y2, 1, 1, n, 1, m);
    cout << "Maximum value: " << result.val << " at position (" << result.idx_x << ", " << result.idx_y << ")" << endl;
}

int32_t main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cerr.tie(nullptr);
    clog.tie(nullptr);

    ll tt = 1;
    while (tt--) solve();
    return 0;
}
