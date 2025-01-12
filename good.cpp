#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>

using namespace std;

class Edge {
public:
    const int from;
    const int to;

    Edge(int from, int to) : from(from), to(to) {}
};

vector<int>* adj = nullptr;
vector<int> answers;

void dfs(int a, int time) {
    if (answers[a] == 0) {
        answers[a] = time;
        for (int b : adj[a]) {
            dfs(b, time);
        }
    }
}

int main() {
    int n, q;
    cin >> n >> q;
    adj = new vector<int>[n + 1];
    answers.resize(n + 1, 0);
    vector<Edge*> added;
    vector<Edge*> removed(q, nullptr);
    vector<int> deactivated(q, 0);
    set<int> alwaysActive;

    for (int a = 1; a <= n; a++) {
        alwaysActive.insert(a);
    }

    for (int j = 0; j < q; j++) {
        char type;
        cin >> type;
        if (type == 'D') {
            int a;
            cin >> a;
            deactivated[j] = a;
            alwaysActive.erase(a);
        } else if (type == 'A') {
            int a, b;
            cin >> a >> b;
            added.push_back(new Edge(a, b));
        } else {
            int k;
            cin >> k;
            removed[j] = added[k - 1];
            added[k - 1] = nullptr;
        }
    }

    for (Edge* edge : added) {
        if (edge != nullptr) {
            adj[edge->from].push_back(edge->to);
            adj[edge->to].push_back(edge->from);
        }
    }

    for (int a : alwaysActive) {
        dfs(a, q);
    }

    for (int j = q - 1; j > 0; j--) {
        if (deactivated[j] != 0) {
            dfs(deactivated[j], j);
        } else if (removed[j] != nullptr) {
            int a = removed[j]->from;
            int b = removed[j]->to;
            adj[a].push_back(b);
            adj[b].push_back(a);
            if (answers[a] != 0 || answers[b] != 0) {
                dfs(a, j);
                dfs(b, j);
            }
        }
    }

    for (int a = 1; a <= n; a++) {
        cout << answers[a] << '\n';
    }

    delete[] adj;
    for (Edge* edge : added) {
        delete edge;
    }

    return 0;
}

