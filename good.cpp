#include <bits/stdc++.h>
using namespace std;

#define ll long long

inline int read() {
    int x = 0; char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) x = 10 * x + ch - '0', ch = getchar();
    return x;
}

const int N = 400005;

int f[N], sz[N];
int row[N], col[N], tot;
int n, m, q;

ll ans;

int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}
ll calc(int x) {
    if (x == 1) return 0;
    else return 1ll * x * x;
}
void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) {
        return ;
    }
    ans -= calc(sz[x]) + calc(sz[y]);
    f[x] = y, sz[y] += sz[x];
    ans += calc(sz[y]);
}

vector<int> adj[N], event[N];
stack<int> stk;
bool instk[N];
int dfn[N], low[N], dtot, scc[N], stot;
void tarjan(int u) {
    dfn[u] = low[u] = ++dtot;
    stk.push(u), instk[u] = 1;
    for (auto v: adj[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (instk[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        int y;
        ++stot;
        do {
            y = stk.top(); stk.pop();
            instk[y] = 0, scc[y] = stot;
        } while (y != u);
    }
}

bool vis[N];
void solve(int L, int R, vector<array<int, 3>> queries) {
    int mid = L + R >> 1;
    vector<int> nodes;
    for (auto [u, v, id]: queries) {
        if (!vis[u]) vis[u] = 1, dfn[u] = 0, adj[u].clear(), nodes.push_back(u);
        if (!vis[v]) vis[v] = 1, dfn[v] = 0, adj[v].clear(), nodes.push_back(v);
        if (id <= mid) {
            adj[u].push_back(v);
        }
    }
    dtot = stot = 0;
    for (auto u: nodes) {
        if (!dfn[u]) tarjan(u);
        vis[u] = 0;
    }

    // printf("solve [%d, %d], ", L, R);
    // for (auto [u, v, id]: queries) printf("(%d, %d) ", u, v);
    // puts("");
    // for (auto u: nodes) {
    //     printf("dfn[%d] = %d, ", u, dfn[u]);
    // }

    vector<array<int, 3>> qL, qR;
    for (auto [u, v, id]: queries) {
        if (scc[u] == scc[v]) {
            if (id <= mid)
                event[mid].push_back(id), qL.push_back({u, v, id});
        } else {
            qR.push_back({scc[u], scc[v], id});
        }
    }
    if (L == R) return ;
    solve(L, mid, qL), solve(mid + 1, R, qR);
}

int main() {
    n = read(), m = read(), q = read();
    for (int i = 1; i <= n; i++) row[i] = ++tot;
    for (int i = 1; i <= m; i++) col[i] = ++tot;
    vector<array<int, 3>> queries;
    for (int i = 1; i <= q; i++) {
        int x = read(), y = read();
        char c;
        c = getchar();
        while (c != 'R' && c != 'B') c = getchar();
        if (c == 'B') queries.push_back({row[x], col[y], i});
        else queries.push_back({col[y], row[x], i});
    }
    solve(1, q, queries);

    for (int i = 1; i <= tot; i++) f[i] = i, sz[i] = 1;
    for (int i = 1; i <= q; i++) {
        cout << i << ": ";
        for (auto t: event[i])
            cout << t << " ", merge(queries[t - 1][0], queries[t - 1][1]);
        cout << "\n";
        printf("%lld\n", ans);
    }
    return 0;
}