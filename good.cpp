#include <bits/stdc++.h>
using namespace std;
#define int long long
using Single = pair<vector<int>*, int>;
using Multi = vector<Single>;
using PolyM = vector<Multi>;
map<Multi, PolyM> Eq;
constexpr int MOD = 1e9+7;
vector<vector<int>> temp_m(1000, vector<int>(1000));
ostream& operator<<(ostream& out, const vector<vector<int>>& mat) {
    for (const auto &x : mat) {
        for (const auto &y : x) {
            out << y << " ";
        }out << "\n";
    }
    return out;
}
void operator*=(vector<vector<int>> &a, const vector<vector<int>>& b) {
//    cout << a;
//    cout << "XXX\n";
//    cout << b;
    for (const auto &x : a) {
        assert(x.size() == a[0].size());
    }
    for (const auto &y : b) {
        assert(y.size() == b[0].size());
    }
    int skal_size = a[0].size();
    assert(a[0].size() == b.size());
    for (int i = 0; i < a.size(); i += 1) {
        for (int j = 0; j < b[0].size(); j += 1) {
            temp_m[i][j] = 0;
            for (int k = 0; k < skal_size; k += 1) {
                temp_m[i][j] += a[i][k] * b[k][j] % MOD;
            }
            temp_m[i][j] %= MOD;
        }
    }
    for (auto &x : a) {
        x.resize(b[0].size());
    }
    for (int i = 0; i < a.size(); i += 1) {
        for (int j = 0; j < a[i].size(); j += 1) {
            a[i][j] = temp_m[i][j];
        }
    }
}
void operator^=(vector<vector<int>>& mat, int b) {
    assert(b >= 0);
    assert(mat.size() == mat[0].size());
    vector<vector<int>> ret(mat.size(), vector<int>(mat.size()));
    for (int i = 0; i < mat.size(); i += 1) {
        ret[i][i] = 1;
    }
    while (b) {
        if (b&1) {
            ret *= mat;
        }
        mat *= mat;
        b >>= 1;
    }
    mat = ret;
}
signed main() {
    vector<int> f(200), r(200), sz(200), none(200, 0), one(200, 1);
    f[0] = 0;
    f[1] = 0;
    r[0] = 0;
    r[1] = 0;
    sz[0] = 1;
    sz[1] = 1;
    Eq[{{&none, 0}}] = {
            {{&none, -1},},
    };
    Eq[{{&one, 0}}] = {
            {{&one, -1},},
    };
    Eq[{{&sz, 0}}] = {
            {{&sz, -1},},
            {{&sz, -2},},
            {{&one, -1},},
    };
    Eq[{{&r, 0}}] = {
            {{&sz, -1},},
            {{&r, -1},},
            {{&sz, -2},},
            {{&r, -2},},
    };
    Eq[{{&f, 0}}] = {
            {{&f, -1}},
            {{&f, -2}},

            {{&sz, -1}, {&r, -2}},
            {{&sz, -1}, {&sz, -2}},
            {{&r, -2},},
            {{&sz, -2},},

            {{&sz, -2}, {&r, -1}},
            {{&sz, -2}, {&sz, -1}},
            {{&r, -1},},
            {{&sz, -1},},
    };
//    Eq.clear();
//    Eq[{{&none, 0}}] = {
//            {{&none, -1},},
//    };
//    Eq[{{&one, 0}}] = {
//            {{&one, -1},},
//    };
//    Eq[{{&f, 0}}] = {
//            {{&f, -1}},
//            {{&f, -2}},
//    };
    map<vector<int>*, string> mp;
    mp[&none] = "NULL";
    mp[&one] = "ONE";
    mp[&sz] = "sz";
    mp[&r] = "r";
    mp[&f] = "f";
    auto check = [&] () -> void {
        for (auto &[a, b] : Eq) {
            for (auto &M : b) {
                sort(M.begin(), M.end());
            }
            sort(b.begin(), b.end());
            if (a.size() == 1 && (a.front().first == &none || a.front().first == &one)) {
                continue;
            }
            PolyM nw_b;
            for (const auto &M : b) {
                Multi nw_m;
                bool bad = false;
                for (const auto &S : M) {
                    if (S.first != &one) {
                        nw_m.push_back(S);
                    }
                    bad |= S.first == &none;
                }
                if (!bad) {
                    if (nw_m.size()) {
                        nw_b.push_back(nw_m);
                    }
                }
            }
            b = nw_b;
            for (const auto &S : a) {
                assert(S.second <= 0);
            }
            for (const auto &M : b) {
                for (const auto &S : M) {
                    assert(S.second <= 0);
                }
            }
        }
        while (true) {
            set<Multi> add;
            for (const auto &[a, b] : Eq) {
                for (const auto &M : b) {
                    bool good = true;
                    for (const auto &S : M) {
                        good &= S.second < 0;
                    }
                    if (good) {
                        auto nw = M;
                        for (auto &S : nw) {
                            S.second += 1;
                        }
                        if (!Eq.count(nw)) {
                            add.insert(nw);
                        }
                    }
                }
            }
            for (const auto &y : add) {
                Eq[y] = {y};
            }
            if (!add.size()) {
                break;
            }
        }
    };
    auto print = [&] () -> void {
        for (const auto &[a, b] : Eq) {
            for (const auto &S : a) {
                cout << mp[S.first] << "[" << S.second << "]";
            }
            cout << " = ";
            for (int i = 0; i < b.size(); i += 1) {
                for (const auto &S : b[i]) {
                    cout << mp[S.first] << "[" << S.second << "]";
                }
                if (i+1 != b.size()) {
                    cout << " + ";
                }
            } cout << "\n";
        }
        cout << "--------\n";
    };
    while (true) {
        check();
        print();
        bool done = false;
        for (auto &[a, b] : Eq) {
            for (auto &M : b) {
                for (auto &S : M) {
                    if (S.second == 0) {
                        assert(Eq.count({S}));
                        auto replace = Eq[{S}];
                        S.first = &one;
                        S.second = -1;
                        for (const auto &fromM: M) {
                            for (auto &h: replace) {
                                h.push_back(fromM);
                            }
                        }
                        S.first = &none;
                        S.second = -1;
                        for (const auto &x: replace) {
                            b.push_back(x);
                        }
                        done = true;
                        break;
                    }
                } if (done) break;
            } if (done) break;
        }
        if (!done) {
            break;
        }
    }
    map<Multi, int> order;
    vector<Multi> list;
    for (const auto &[a, b] : Eq) {
        assert(!order.count(a));
        order[a] = order.size();
        list.push_back(a);
    }
    vector<vector<int>> Matrix(order.size(), vector<int>(order.size()));
    int mini = 1e9;
    for (const auto &[a, b] : Eq) {
        assert(order.count(a));
        for (const auto &S : a) {
            mini = min(mini, S.second);
        }
        for (const auto &M : b) {
            auto from = M;
            for (auto &x : from) {
                x.second += 1;
            }
            assert(order.count(from));
            Matrix[order[a]][order[from]] += 1;
        }
    }
    cout << "0 is " << -mini << "\n";
    cout << Matrix;
    vector<vector<int>> base;
    for (const auto &S : list) {
        int tot = 1;
        for (const auto &[ptr, diff] : S) {
            (tot *= ptr->at(-mini+diff)) %= MOD;
        }
        base.push_back({tot});
    }
//    cout << base;
    int n;
    cin >> n;
    assert(n >= -mini);
    Matrix ^= n - (-mini);
    Matrix *= base;
    for (int i = 0; i < Matrix.size(); i += 1) {
        if (list[i] == Multi{{&f, 0}}) {
            cout << Matrix[i][0] << ":D\n";
        }
    }
}