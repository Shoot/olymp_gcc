#include <bits/stdc++.h>
using namespace std;
#define int long long
using Single = pair<vector<int>*, int>;
using Multi = vector<Single>;
using PolyM = vector<Multi>;
map<Multi, PolyM> Eq;
int LAST_IDX_SET = -1e9;
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
int query_fast(vector<vector<int>> Matrix, const int n, const vector<vector<int>>& base,
               const vector<Multi>& list, vector<int>* f) {
    if (n <= LAST_IDX_SET) {
        return f->at(n);
    }
    Matrix ^= n - LAST_IDX_SET;
    Matrix *= base;
    for (int i = 0; i < Matrix.size(); i += 1) {
        if (list[i] == Multi{{f, 0}}) {
            return Matrix[i][0];
        }
    }
    assert(false);
}
int query_slow(const int n, const map<Multi, PolyM>& slow_eq, vector<int>* f) {
    // better run twice, first return value shouldn't be considered
    if (n <= LAST_IDX_SET) {
        return f->at(n);
    }
    int curr = LAST_IDX_SET+1;
    for (const auto &[a, b] : slow_eq) {
        for (const auto &S : a) {
            S.first->resize(n+1);
        }
        for (const auto &M : b) {
            for (const auto &S : M) {
                if (!(curr+S.second >= 0)) {
                    throw invalid_argument("Недостаточно начальных значений");
                }
            }
        }
    }
    while (curr <= n) {
        for (const auto &[a, b] : slow_eq) {
            assert(a.size() == 1);
            int su = 0;
            for (const auto &M : b) {
                int mul = 1;
                for (const auto &S : M) {
                    (mul *= S.first->at(curr+S.second)) %= MOD;
                }
                (su += mul) %= MOD;
            }
            assert(a.front().second == 0);
            a.front().first->at(curr) = su;
        }
        curr += 1;
    }
    return f->at(n);
}
signed main() {
    vector<int> f(200), r(200), sz(200), fib(200), nech(200), I2(200), P(200), Q(200), R(200), I(200);
    vector<int> none(200, 0), one(200, 1);
    Eq[{{&none, 0}}] = {
            {{&none, -1},},
    };
    Eq[{{&one, 0}}] = {
            {{&one, -1},},
    };
    auto test_on_fibonacci_trees = [&] () -> void {
        f[0] = 0;
        f[1] = 0;
        r[0] = 0;
        r[1] = 0;
        sz[0] = 1;
        sz[1] = 1;
        LAST_IDX_SET = 1;
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
    };
    auto test_on_fibonacci = [&] () -> void {
        f[0] = 0;
        f[1] = 1;
        LAST_IDX_SET = 1;
        Eq[{{&f, 0}}] = {
                {{&f, -1}},
                {{&f, -2}},
        };
    };
    auto another_test = [&] () -> void {
        // f[i] = (fib[i] * fib[i-1] + f[i-1]) % MOD;
        fib[0] = 0;
        fib[1] = 1;
        f[0] = 0;
        f[1] = 0;
        LAST_IDX_SET = 1;
        Eq[{{&fib, 0}}] = {
                {{&fib, -1}},
                {{&fib, -2}},
        };
        Eq[{{&f, 0}}] = {
                {{&fib, 0}, {&fib, -1}},
                {{&f, -1}},
        };
    };
    int QUERY_TEMP;
    auto go = [&] () -> void {
        int n;
        cin >> n >> QUERY_TEMP;
        for (int i = 0; i < n; i += 1) {
            cin >> f[i];
        }
        for (int i = 0; i < n; i += 1) {
            int x;
            cin >> x;
            for (int j = 0; j < x; j += 1) {
                Eq[{{&f, 0}}].push_back({{&f, -i-1}});
            }
        }
        LAST_IDX_SET = n-1;
        for (int i = 0; i < n; i += 1) {
            nech[i] = ((2*i-1)%MOD+MOD)%MOD;
            I2[i] = i*i;
        }
        Eq[{{&nech, 0}}] = {
                {{&nech, -1}},
                {{&one, -1}},
                {{&one, -1}},
        };
        iota(I.begin(), I.end(), 0);
        Eq[{{&I, 0}}] = {
                {{&I, -1}},
                {{&one, -1}},
        };
        Eq[{{&I2, 0}}] = {
                {{&I2, -1}},
                {{&nech, 0}},
        };
        int p, q, r;
        cin >> p >> q >> r;
        fill(P.begin(), P.end(), p); Eq[{{&P, 0}}] = {{{&P, -1}}};
        fill(Q.begin(), Q.end(), q); Eq[{{&Q, 0}}] = {{{&Q, -1}}};
        fill(R.begin(), R.end(), r); Eq[{{&R, 0}}] = {{{&R, -1}}};
        Eq[{{&f, 0}}].push_back({{&P, -1}});
        Eq[{{&f, 0}}].push_back({{&Q, -1}, {&I, 0}});
        Eq[{{&f, 0}}].push_back({{&R, -1}, {&I2, 0}});
    };
//    test_on_fibonacci();
//    test_on_fibonacci_trees();
//    another_test();
    go();
    if (Eq.empty()) {
        throw invalid_argument("No recursive formulas given (Не даны рекуррентные уравнения)");
    }
    auto slow_Eq = Eq;
    map<vector<int>*, string> mp;
    mp[&none] = "NULL";
    mp[&one] = "ONE";
    mp[&sz] = "sz";
    mp[&r] = "r";
    mp[&f] = "f";
    mp[&I] = "I";
    mp[&I2] = "I2";
    mp[&nech] = "nech";
    mp[&P] = "P";
    mp[&Q] = "Q";
    mp[&R] = "R";
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
                bool got_one = false;
                for (const auto &S : M) {
                    if (S.first != &one) {
                        nw_m.push_back(S);
                    } else {
                        got_one = true;
                    }
                    bad |= S.first == &none;
                }
                if (!bad) {
                    if(!nw_m.size() && got_one) {
                        nw_m.push_back({&one, -1});
                    }
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
//    auto print = [&] () -> void {
//        for (const auto &[a, b] : Eq) {
//            for (const auto &S : a) {
//                clog << mp[S.first] << "[" << S.second << "]";
//            }
//            clog << " = ";
//            for (int i = 0; i < b.size(); i += 1) {
//                for (const auto &S : b[i]) {
//                    clog << mp[S.first] << "[" << S.second << "]";
//                }
//                if (i+1 != b.size()) {
//                    clog << " + ";
//                }
//            } clog << "\n";
//        }
//        clog << "--------\n";
//    };
    while (true) {
        check();
//        print();
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
    for (const auto &[a, b] : Eq) {
        assert(order.count(a));
        for (const auto &S : a) {
            if (!(LAST_IDX_SET >= -S.second)) {
                throw invalid_argument("Недостаточно начальных значений");
            }
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
    vector<vector<int>> base;
    for (const auto &S : list) {
        int tot = 1;
        for (const auto &[ptr, diff] : S) {
            (tot *= ptr->at(LAST_IDX_SET+diff)) %= MOD;
        }
        base.push_back({tot});
    }
    int q = 1e3;
//    q = 1;
    mt19937_64 mt(chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> distrib(1, 1e4);
    for (int ii = 0; ii < q; ii += 1) {
        int n = distrib(mt);
//        n = QUERY_TEMP;
//        cout << query_fast(Matrix, n, base, list, &f) << "\n";
        clog << "f[" << n << "]: ";
        clog << query_fast(Matrix, n, base, list, &f) << ", "
             << query_slow(n, slow_Eq, &f) << "\n";
        assert(query_fast(Matrix, n, base, list, &f) == query_slow(n, slow_Eq, &f));
    }
}