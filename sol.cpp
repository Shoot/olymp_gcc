#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    struct Edge {
        int w;
        int to;
    };
    vector<vector<Edge>> adj(n+1);
    vector<vector<int>> cost(n+1, vector<int>(n+1));
    vector<int> cost_by_num(m+1);
    vector<vector<int>> num(n+1, vector<int>(n+1));
    for (int i = 0; i < m; i += 1) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
        cost[u][v] = w;
        cost[v][u] = w;
        num[v][u] = i+1;
        num[u][v] = i+1;
        cost_by_num[i+1] = w;
    }
    bitset<2'001> city;
    for (int i = 1; i <= n; i += 1) {
        if (adj[i].size() > 1) {
            city[i] = true;
        }
    }
    auto do_city = [&] (int u, vector<pair<int, vector<int>>> &dp) -> void {
        for (const auto &[w, x] : adj[u]) {
            if (!city[x]) {
                clog << "City = " << u << ", town = " << x << "\n";
                for (int from = n-1; from >= 0; from -= 1) {
                    if (dp[from+1].first > dp[from].first+w) {
                        dp[from+1].first = dp[from].first+w;
                        dp[from+1].second = dp[from].second;
                        dp[from+1].second.push_back(num[u][x]);
                    }
                }
            }
        }
    };
    bitset<2'001> seen;
    bool cycle;
    vector<vector<pair<int, vector<int>>>> dp_parent_uses_me(n+1, vector<pair<int, vector<int>>>(n+1, pair<int, vector<int>>{(int)1e18, {}}));
    vector<vector<pair<int, vector<int>>>> dp_individual(n+1, vector<pair<int, vector<int>>>(n+1, pair<int, vector<int>>{(int)1e18, {}}));
    dp_parent_uses_me.reserve(2001);
    dp_individual.reserve(2001);
    vector<int> order;
    int best_val = 1e18;
    vector<int> ans;
    for (int i = 1; i <= n; i += 1) if (city[i]) {
        if (dp_individual[i][k].first < best_val) {
            best_val = dp_individual[i][k].first;
            ans = dp_individual[i][k].second;
        }
    }
    auto dfs = [&] (auto f, int u, int p) -> void {
        if (seen[u] || !city[u]) {
            return;
        }
        seen[u] = true;
        order.push_back(u);
        dp_individual[u][0].first = 0;
        dp_parent_uses_me[u][1].first = cost[u][p];
        dp_parent_uses_me[u][1].second.push_back(num[u][p]);
        do_city(u, dp_parent_uses_me[u]);
        do_city(u, dp_individual[u]);
        for (const auto &[w, x] : adj[u]) if (x != p) {
            if (city[x]) {
                if (seen[x]) {
                    cycle = true;
                }
                if (cycle) {
                    continue;
                }
                f(f, x, u);
                auto dp_to = dp_parent_uses_me[u];
                for (int done = 1; done <= n; done += 1) {
                    if (dp_parent_uses_me[x][done].first == 1e18) {
                        break;
                    }
                    for (int from = 1; from <= n-done; from += 1) {
                        if (dp_parent_uses_me[u][from].first == 1e18) {
                            break;
                        }
                        if (dp_to[from+done].first > dp_parent_uses_me[u][from].first+dp_parent_uses_me[x][done].first) {
                            dp_to[from+done].second = dp_parent_uses_me[u][from].second;
                            for (const auto &y : dp_parent_uses_me[x][done].second) {
                                dp_to[from+done].second.push_back(y);
                            }
                            dp_to[from+done].first = dp_parent_uses_me[u][from].first+dp_parent_uses_me[x][done].first;
                        }
                    }
                }
                dp_parent_uses_me[u] = dp_to;
                dp_to = dp_individual[u];
                for (int done = 1; done <= n; done += 1) {
                    if (dp_parent_uses_me[x][done].first == 1e18) {
                        break;
                    }
                    for (int from = 0; from <= n-done; from += 1) {
                        if (dp_individual[u][from].first == 1e18) {
                            break;
                        }
                        if (dp_to[from+done].first > dp_individual[u][from].first+dp_parent_uses_me[x][done].first) {
                            dp_to[from+done].second = dp_individual[u][from].second;
                            for (const auto &y : dp_parent_uses_me[x][done].second) {
                                dp_to[from+done].second.push_back(y);
                            }
                            dp_to[from+done].first = dp_individual[u][from].first+dp_parent_uses_me[x][done].first;
                        }
                    }
                }
                dp_individual[u] = dp_to;
                dp_parent_uses_me[x].clear();
            }
        }
        if (dp_individual[u][k].first < best_val) {
            best_val = dp_individual[u][k].first;
            ans = dp_individual[u][k].second;
        }
        dp_individual[u].clear();
    };
    for (int i = 1; i <= n; i += 1) {
        dfs(dfs, i, i);
    }
    assert((n == m) == cycle);
    if (!cycle) {
        clog << "MIN COST (DFS): " << best_val << "\n";
        for (const auto &x : ans) {
            cout << x << "\n";
        }
        return 0;
    }
    dp_individual.assign(n+1, vector<pair<int, vector<int>>>(n+1, pair<int, vector<int>>{(int)1e18, {}}));
    for (const auto &x : order) {
        clog << x << "o";
    }clog << "\n";
    for (const auto &x : order) {
        dp_individual[x][0].first = 0;
        do_city(x, dp_individual[x]);
    }
    vector<pair<int, vector<int>>> curr(n+1, pair<int, vector<int>>{(int)1e18, {}}), dp_to;
    curr.reserve(2001);
    dp_to.reserve(2001);
    for (int l = 0; l < order.size(); l += 1) {
        fill(curr.begin(), curr.end(), pair<int, vector<int>>{(int)1e18, {}});
        curr[0].first = 0;
        int prev = -1;
        int add = 0;
        int cnt_add = 0;
        vector<int> shi;
        int biggest = -1;
        int biggest_val = -1;
        for (int x = l; ;) {
            if (prev != -1) {
                add += cost[order[prev]][order[x]];
                if (cost[order[prev]][order[x]] > biggest_val) {
                    biggest_val = cost[order[prev]][order[x]];
                    biggest = num[order[prev]][order[x]];
                }
                cnt_add += 1;
                shi.push_back(num[order[prev]][order[x]]);
            }
            prev = x;
            dp_to = curr;
            for (int done = 1; done <= n; done += 1) {
                if (dp_individual[order[x]][done].first == 1e18) {
                    break;
                }
                for (int from = 0; from <= n-done; from += 1) {
                    if (curr[from].first == 1e18) {
                        break;
                    }
                    if (dp_to[from+done].first > curr[from].first+dp_individual[order[x]][done].first) {
                        dp_to[from+done].second = curr[from].second;
                        for (const auto &y : dp_individual[order[x]][done].second) {
                            dp_to[from+done].second.push_back(y);
                        }
                        dp_to[from+done].first = curr[from].first+dp_individual[order[x]][done].first;
                    }
                }
            }
            swap(curr, dp_to);
            if ((x+1)%order.size() == l) {
                if (cost[order[x]][order[l]] > biggest_val) {
                    biggest_val = cost[order[x]][order[l]];
                    biggest = num[order[x]][order[l]];
                }
                add += cost[order[x]][order[l]];
                cnt_add += 1;
                shi.push_back(num[order[x]][order[l]]);
            }
            if (k-cnt_add >= 0) {
                if (curr[k-cnt_add].first+add < best_val) {
                    best_val = curr[k-cnt_add].first+add;
                    ans = curr[k-cnt_add].second;
                    for (const auto &sh : shi) {
                        ans.push_back(sh);
                    }
                }
            }
            if (k-(cnt_add-1) >= 0 && (x+1)%order.size() == l) {
                if (curr[k-(cnt_add-1)].first+(add-biggest_val) < best_val) {
                    best_val = curr[k-(cnt_add-1)].first+(add-biggest_val);
                    ans = curr[k-(cnt_add-1)].second;
                    for (const auto &sh : shi) if (sh != biggest) {
                        ans.push_back(sh);
                    }
                }
            }
            if ((x+1)%order.size() == l) {
                break;
            }
            (x += 1) %= order.size();
        }
    }
    clog << "Min cost: " << best_val << "!!\n";
    for (const auto &x : ans) {
        cout << x << "\n";
    }
}
