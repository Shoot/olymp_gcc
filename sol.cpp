#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define all(value) value.begin(), value.end()
#define fo(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x < fi; x++)
#define forr(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x <= fi; x++)
#define rrof(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x >= fi; x--)
#define roff(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x >= fi; x--)
#define of(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x > fi; x--)
#define ro(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x > fi; x--)
#define yes(x) (x ? "YES" : "NO")
#define endl '\n'
#define WHITE_PAWN 11
#define WHITE_KNIGHT 12
#define WHITE_BISHOP 13
#define WHITE_ROOK 14
#define WHITE_QUEEN 15
#define WHITE_KING 16
#define BLACK_PAWN 21
#define BLACK_KNIGHT 22
#define BLACK_BISHOP 23
#define BLACK_ROOK 24
#define BLACK_QUEEN 25
#define BLACK_KING 26
#define endl '\n'
#ifdef LOCAL
#include <algo/debug.h>
#else
#define debug(...) 68
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math,trapv")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//uniform_int_distribution<ll> distrib(1ll, 4ll);
/*\
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; fo(i, 0, n) cin >> a[i];
    vector<ll> a(n); fo(i, 0, n) cin >> a[i];
}
*/
string my_move;
string new_move;
vector<vector<ll>> field (8, vector<ll> (8, 0));
bool nash_hod = false;
ll my_last_move_i = -1;
ll my_last_move_j = -1;
bool isCellPossible (ll i, ll j) {
    return i < 8 && i >= 0 && j < 8 && j >= 0;
}
void process () {
    if (new_move == "O-O-O") {
        assert(!nash_hod); // !! мы не рокируемся
        field['8'-'1']['c'-'a'] = field['8'-'1']['e'-'a'];
        field['8'-'1']['e'-'a'] = 0;
        field['8'-'1']['d'-'a'] = field['8'-'1']['a'-'a'];
        field['8'-'1']['a'-'a'] = 0;
        return;
    }
    if (new_move == "O-O") {
        assert(!nash_hod); // !! мы не рокируемся
        field['8'-'1']['g'-'a'] = field['8'-'1']['e'-'a'];
        field['8'-'1']['e'-'a'] = 0;
        field['8'-'1']['f'-'a'] = field['8'-'1']['h'-'a'];
        field['8'-'1']['h'-'a'] = 0;
        return;
    }
    ll n = new_move.size();
    if (n == 6 && new_move[n-1] == 'Q' && nash_hod) { // !! проводим только Q
        ll origin_j = new_move[0]-'a';
        ll origin_i = new_move[1]-'1';
        assert(isCellPossible(origin_i, origin_j));
        field[origin_i][origin_j] = 0;
        ll destination_j = new_move[3]-'a';
        ll destination_i = new_move[4]-'1';
        assert(isCellPossible(destination_i, destination_j));
        field[destination_i][destination_j] = WHITE_QUEEN;
        return;
    }
    if (n == 5) { // ход пешкой без превращения
        ll origin_j = new_move[0]-'a';
        ll origin_i = new_move[1]-'1';
        ll destination_j = new_move[3]-'a';
        ll destination_i = new_move[4]-'1';
        assert(isCellPossible(origin_i, origin_j));
        assert(isCellPossible(destination_i, destination_j));
        if (new_move[2] == 'x') {
            assert(field[destination_i][destination_j] < 20 || nash_hod); // !! это значило бы что противник или я сбил на проходе
        }
        field[destination_i][destination_j] = field[origin_i][origin_j];
        field[origin_i][origin_j] = 0;
        return;
    }
    if (n == 6) { // ход фигурой или пешкой с превращением
        assert(new_move[n-1] != 'B' && new_move[n-1] != 'Q' && new_move[n-1] != 'R' && new_move[n-1] != 'N'); // !! это значило бы что противник провел пешку
        ll origin_j = new_move[1]-'a';
        ll origin_i = new_move[2]-'1';
        ll destination_j = new_move[4]-'a';
        ll destination_i = new_move[5]-'1';
        assert(isCellPossible(origin_i, origin_j));
        assert(isCellPossible(destination_i, destination_j));
        if (new_move[2] == 'x') {
            assert(field[destination_i][destination_j] < 20 || nash_hod);
        }
        field[destination_i][destination_j] = field[origin_i][origin_j];
        field[origin_i][origin_j] = 0;
        return;
    }
    assert(false);
}
struct Move {
    ll origin_i, origin_j, destination_i, destination_j;
    ll priority;
};

bool isOurKingUnderAttack (vector<vector<ll>> & deriv_field) {
    ll myKingI = -1;
    ll myKingJ = -1;
    fo(i, 0, 8) {
        fo(j, 0, 8) {
            assert(isCellPossible(i, j));
            if (deriv_field[i][j] == WHITE_KING) {
                myKingI = i;
                myKingJ = j;
            }
        }
    }
    assert(myKingI != -1 && myKingJ != -1);
    fo(i, 0, 8) {
        fo(j, 0, 8) {
            assert(isCellPossible(i, j));
            if (deriv_field[i][j] == BLACK_PAWN) {
                if (i-1 == myKingI && abs(j-myKingJ) <= 1) {
                    return true;
                }
            }
            if (deriv_field[i][j] == BLACK_KING) {
                if (abs(i-myKingI) <= 1 && abs(j-myKingJ) <= 1) {
                    return true;
                }
            }
            if (deriv_field[i][j] == BLACK_KNIGHT) {
                if (i-1 == myKingI && j-2 == myKingJ) return true;
                if (i-2 == myKingI && j-1 == myKingJ) return true;
                if (i+1 == myKingI && j+2 == myKingJ) return true;
                if (i+2 == myKingI && j+1 == myKingJ) return true;

                if (i+2 == myKingI && j-1 == myKingJ) return true;
                if (i+1 == myKingI && j-2 == myKingJ) return true;
                if (i-1 == myKingI && j+2 == myKingJ) return true;
                if (i-2 == myKingI && j+1 == myKingJ) return true;
            }
            if (deriv_field[i][j] == BLACK_ROOK || deriv_field[i][j] == BLACK_QUEEN) {
                ll temp_i = i+1;
                while (isCellPossible(temp_i, j)) {
                    if (deriv_field[temp_i][j] != 0) {
                        if (deriv_field[temp_i][j] == WHITE_KING) {
                            return true;
                        }
                        break;
                    }
                    temp_i += 1;
                }
                temp_i = i-1;
                while (isCellPossible(temp_i, j)) {
                    if (deriv_field[temp_i][j] != 0) {
                        if (deriv_field[temp_i][j] == WHITE_KING) {
                            return true;
                        }
                        break;
                    }
                    temp_i -= 1;
                }
                ll temp_j = j+1;
                while (isCellPossible(i, temp_j)) {
                    if (deriv_field[i][temp_j] != 0) {
                        if (deriv_field[i][temp_j] == WHITE_KING) {
                            return true;
                        }
                        break;
                    }
                    temp_j += 1;
                }
                temp_j = j-1;
                while (isCellPossible(i, temp_j)) {
                    if (deriv_field[i][temp_j] != 0) {
                        if (deriv_field[i][temp_j] == WHITE_KING) {
                            return true;
                        }
                        break;
                    }
                    temp_j -= 1;
                }
            }
            assert(isCellPossible(i, j));
            if (deriv_field[i][j] == BLACK_BISHOP || deriv_field[i][j] == BLACK_QUEEN) {
                ll temp_i = i+1;
                ll temp_j = j+1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (deriv_field[temp_i][temp_j] != 0) {
                        if (deriv_field[temp_i][temp_j] == WHITE_KING) {
                            return true;
                        }
                        break;
                    }
                    temp_i += 1;
                    temp_j += 1;
                }
                temp_i = i-1;
                temp_j = j-1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (deriv_field[temp_i][temp_j] != 0) {
                        if (deriv_field[temp_i][temp_j] == WHITE_KING) {
                            return true;
                        }
                        break;
                    }
                    temp_i -= 1;
                    temp_j -= 1;
                }
                temp_i = i+1;
                temp_j = j-1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (deriv_field[temp_i][temp_j] != 0) {
                        if (deriv_field[temp_i][temp_j] == WHITE_KING) {
                            return true;
                        }
                        break;
                    }
                    temp_i += 1;
                    temp_j -= 1;
                }
                temp_i = i-1;
                temp_j = j+1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (deriv_field[temp_i][temp_j] != 0) {
                        if (deriv_field[temp_i][temp_j] == WHITE_KING) {
                            return true;
                        }
                        break;
                    }
                    temp_i -= 1;
                    temp_j += 1;
                }
            }
        }
    }
    return false;
}
bool isHisMoveImpossible (vector<vector<ll>> deriv_field, Move move) {
    auto goddamn_copy = deriv_field;
    assert(isCellPossible(move.destination_i, move.destination_j));
    assert(isCellPossible(move.origin_i, move.origin_j));
    goddamn_copy[move.destination_i][move.destination_j] = goddamn_copy[move.origin_i][move.origin_j];
    goddamn_copy[move.origin_i][move.origin_j] = 0;
    ll hisKingI = -1;
    ll hisKingJ = -1;
    fo(i, 0, 8) {
        fo(j, 0, 8) {
            assert(isCellPossible(i, j));
            if (goddamn_copy[i][j] == BLACK_KING) {
                hisKingI = i;
                hisKingJ = j;
            }
        }
    }
    assert(hisKingI != -1 && hisKingJ != -1);
    fo(i, 0, 8) {
        fo(j, 0, 8) {
            assert(isCellPossible(i, j));
            if (goddamn_copy[i][j] == WHITE_PAWN) {
                if (i-1 == hisKingI && abs(j-hisKingJ) <= 1) {
                    return true;
                }
            }
            if (goddamn_copy[i][j] == WHITE_KING) {
                if (abs(i-hisKingI) <= 1 && abs(j-hisKingJ) <= 1) {
                    return true;
                }
            }
            if (goddamn_copy[i][j] == WHITE_KNIGHT) {
                if (i-1 == hisKingI && j-2 == hisKingJ) return true;
                if (i-2 == hisKingI && j-1 == hisKingJ) return true;
                if (i+1 == hisKingI && j+2 == hisKingJ) return true;
                if (i+2 == hisKingI && j+1 == hisKingJ) return true;

                if (i+2 == hisKingI && j-1 == hisKingJ) return true;
                if (i+1 == hisKingI && j-2 == hisKingJ) return true;
                if (i-1 == hisKingI && j+2 == hisKingJ) return true;
                if (i-2 == hisKingI && j+1 == hisKingJ) return true;
            }
            if (goddamn_copy[i][j] == WHITE_ROOK || goddamn_copy[i][j] == WHITE_QUEEN) {
                ll temp_i = i+1;
                while (isCellPossible(temp_i, j)) {
                    if (goddamn_copy[temp_i][j] != 0) {
                        if (goddamn_copy[temp_i][j] == BLACK_KING) {
                            return true;
                        }
                        break;
                    }
                    temp_i += 1;
                }
                temp_i = i-1;
                while (isCellPossible(temp_i, j)) {
                    if (goddamn_copy[temp_i][j] != 0) {
                        if (goddamn_copy[temp_i][j] == BLACK_KING) {
                            return true;
                        }
                        break;
                    }
                    temp_i -= 1;
                }
                ll temp_j = j+1;
                while (isCellPossible(i, temp_j)) {
                    if (goddamn_copy[i][temp_j] != 0) {
                        if (goddamn_copy[i][temp_j] == BLACK_KING) {
                            return true;
                        }
                        break;
                    }
                    temp_j += 1;
                }
                temp_j = j-1;
                while (isCellPossible(i, temp_j)) {
                    if (goddamn_copy[i][temp_j] != 0) {
                        if (goddamn_copy[i][temp_j] == BLACK_KING) {
                            return true;
                        }
                        break;
                    }
                    temp_j -= 1;
                }
            }
            assert(isCellPossible(i, j));
            if (goddamn_copy[i][j] == WHITE_BISHOP || goddamn_copy[i][j] == WHITE_QUEEN) {
                ll temp_i = i+1;
                ll temp_j = j+1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (goddamn_copy[temp_i][temp_j] != 0) {
                        if (goddamn_copy[temp_i][temp_j] == BLACK_KING) {
                            return true;
                        }
                        break;
                    }
                    temp_i += 1;
                    temp_j += 1;
                }
                temp_i = i-1;
                temp_j = j-1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (goddamn_copy[temp_i][temp_j] != 0) {
                        if (goddamn_copy[temp_i][temp_j] == BLACK_KING) {
                            return true;
                        }
                        break;
                    }
                    temp_i -= 1;
                    temp_j -= 1;
                }
                temp_i = i+1;
                temp_j = j-1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (goddamn_copy[temp_i][temp_j] != 0) {
                        if (goddamn_copy[temp_i][temp_j] == BLACK_KING) {
                            return true;
                        }
                        break;
                    }
                    temp_i += 1;
                    temp_j -= 1;
                }
                temp_i = i-1;
                temp_j = j+1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (goddamn_copy[temp_i][temp_j] != 0) {
                        if (goddamn_copy[temp_i][temp_j] == BLACK_KING) {
                            return true;
                        }
                        break;
                    }
                    temp_i -= 1;
                    temp_j += 1;
                }
            }
        }
    }
    return false;
}
bool isMovePossible (Move move) {
    auto copy = field;
    assert(isCellPossible(move.destination_i, move.destination_j));
    assert(isCellPossible(move.origin_i, move.origin_j));
    copy[move.destination_i][move.destination_j] = copy[move.origin_i][move.origin_j];
    copy[move.origin_i][move.origin_j] = 0;
    return !isOurKingUnderAttack(copy);
}
bool isStalementAfterMove (Move move) {
    auto copy = field;
    assert(isCellPossible(move.destination_i, move.destination_j));
    assert(isCellPossible(move.origin_i, move.origin_j));
    copy[move.destination_i][move.destination_j] = copy[move.origin_i][move.origin_j];
    copy[move.origin_i][move.origin_j] = 0;

    ll hisKingI = -1;
    ll hisKingJ = -1;
    fo(i, 0, 8) {
        fo(j, 0, 8) {
            if (copy[i][j] == BLACK_KING) {
                hisKingI = i;
                hisKingJ = j;
                break;
            }
        }
    }
    assert(hisKingI != -1);
    assert(hisKingJ != -1);
    forr(ii, hisKingI-1, hisKingI+1) {
        forr(jj, hisKingJ-1, hisKingJ+1) {
            if (!isCellPossible(ii, jj)) continue;
            if (ii == hisKingI && jj == hisKingJ) continue;
            if (!isHisMoveImpossible(copy, Move{hisKingI, hisKingJ, ii, jj, -666})) return false;
        }
    }
    return true;
}
void calc () {
    // ПРИОРИТЕТЫ СРЕДИ ДОСТУПНЫХ ХОДОВ
    // 0. проводим пешки
    // 1. кушаем фигуры (в приоритете минимальной фигурой и так что нас не собьют одним ходом и мы не даем шах)
    // 2. нападаем на фигуры так что нас не собьют одним ходом и мы не даем шах
    //// !!! Не ставим пат
    //// если у соперника ноль фигур {
    ////      (у нас должно быть два ферзя)
    ////      ограничиваем вражеского короля одним ферзем (допустим всегда возможно) и даем шах параллельно линии ограничения другим ферзем
    ////
    //// (И ТАК СОЙДЕТ)
    //// }
    vector<Move> moves;
    fo(i, 0, 8) {
        fo(j, 0, 8) {
            if (field[i][j] == WHITE_KING) {
                forr(ii, i-1, i+1) {
                    forr (jj, j-1, j+1) {
                        if (!isCellPossible(ii, jj)) continue;
                        if (ii == i && jj == j || field[ii][jj] < 20 && field[ii][jj] != 0) continue;
                        if (isCellPossible(ii, jj)) moves.push_back(Move{i, j, ii, jj, -1}); // ходим королем только от шаха
                    }
                }
            }
            if (field[i][j] == WHITE_PAWN && i == 1) {
                if (field[i+2][j] == 0 && field[i+1][j] == 0) {
                    moves.push_back(Move{i, j, i+2, j, i+2}); // проводим пешки
                }
            }
            if (field[i][j] == WHITE_PAWN) {
                if (isCellPossible(i+1, j) && field[i+1][j] == 0) {
                    moves.push_back(Move{i, j, i+1, j, i+1}); // проводим пешки
                }
                if (isCellPossible(i+1, j+1) && field[i+1][j+1] > 20) {
                    moves.push_back(Move{i, j, i+1, j+1, 20-(i+1)}); // проводим пешки
                }
                if (isCellPossible(i+1, j-1) && field[i+1][j-1] > 20) {
                    moves.push_back(Move{i, j, i+1, j-1, 20-(i+1)}); // проводим пешки
                }
            }
            if (field[i][j] == WHITE_KNIGHT) {
                if (isCellPossible(i+2, j+1) && field[i+2][j+1] > 20) {
                    moves.push_back(Move{i, j, i+2, j+1, 20-(i+2)});
                }
                if (isCellPossible(i+1, j+2) && field[i+1][j+2] > 20) {
                    moves.push_back(Move{i, j, i+1, j+2, 20-(i+1)});
                }
                if (isCellPossible(i-1, j-2) && field[i-1][j-2] > 20) {
                    moves.push_back(Move{i, j, i-1, j-2, 20-(i-1)});
                }
                if (isCellPossible(i-1, j+2) && field[i-1][j+2] > 20) {
                    moves.push_back(Move{i, j, i-1, j+2, 20-(i-1)});
                }
                if (isCellPossible(i-2, j+1) && field[i-2][j+1] > 20) {
                    moves.push_back(Move{i, j, i-2, j+1, 20-(i-2)});
                }
                if (isCellPossible(i+2, j-1) && field[i+2][j-1] > 20) {
                    moves.push_back(Move{i, j, i+2, j-1, 20-(i+2)});
                }
                if (isCellPossible(i+1, j-2) && field[i+1][j-2] > 20) {
                    moves.push_back(Move{i, j, i+1, j-2, 20-(i+1)});
                }
                if (isCellPossible(i-2, j-1) && field[i-2][j-1] > 20) {
                    moves.push_back(Move{i, j, i-2, j-1, 20-(i-2)});
                }
            }
            if (field[i][j] == WHITE_QUEEN) {
                ll temp_i = i-1;
                ll temp_j = j+1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (field[temp_i][temp_j] == 0) {
                        moves.push_back(Move{i, j, temp_i, temp_j, i-temp_i});
                    }
                    if (field[temp_i][temp_j] != 0) {
                        break;
                    }
                    temp_i -= 1;
                    temp_j += 1;
                }
                temp_i = i-1;
                temp_j = j-1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (field[temp_i][temp_j] == 0) {
                        moves.push_back(Move{i, j, temp_i, temp_j, i-temp_i});
                    }
                    if (field[temp_i][temp_j] != 0) {
                        break;
                    }
                    temp_i -= 1;
                    temp_j -= 1;
                }
            }
            if (field[i][j] == WHITE_ROOK || field[i][j] == WHITE_QUEEN) {
                ll temp_j = j+1;
                while (isCellPossible(i, temp_j)) {
                    if (field[i][temp_j] != 0) {
                        if (field[i][temp_j] > 20) {
                            moves.push_back(Move{i, j, i, temp_j, 20-(i)-(field[i][j] == WHITE_QUEEN)});
                        }
                        break;
                    }
                    temp_j += 1;
                }
                temp_j = j-1;
                while (isCellPossible(i, temp_j)) {
                    if (field[i][temp_j] != 0) {
                        if (field[i][temp_j] > 20) {
                            moves.push_back(Move{i, j, i, temp_j, 20-(i)-(field[i][j] == WHITE_QUEEN)});
                        }
                        break;
                    }
                    temp_j -= 1;
                }
                ll temp_i = i+1;
                while (isCellPossible(temp_i, j)) {
                    if (field[temp_i][j] != 0) {
                        if (field[temp_i][j] > 20) {
                            moves.push_back(Move{i, j, temp_i, j, 20-(temp_i)-(field[i][j] == WHITE_QUEEN)});
                        }
                        break;
                    }
                    temp_i += 1;
                }
                temp_i = i-1;
                while (isCellPossible(temp_i, j)) {
                    if (field[temp_i][j] != 0) {
                        if (field[temp_i][j] > 20) {
                            moves.push_back(Move{i, j, temp_i, j, 20-(temp_i)-(field[i][j] == WHITE_QUEEN)});
                        }
                        break;
                    }
                    temp_i -= 1;
                }
            }
        }
    }
    sort(all(moves), [] (Move a, Move b) {
        return a.priority > b.priority;
    });
    for (Move hod: moves) {
        assert(isCellPossible(hod.origin_i, hod.origin_j));
        assert(hod.origin_i != hod.destination_i || hod.origin_j != hod.destination_j);
        assert(isCellPossible(hod.destination_i, hod.destination_j));
        if (isMovePossible(hod) && !isStalementAfterMove(hod)) {
            char first_ch = (char)('a'+hod.origin_j);
            char third_ch = (char)('a'+hod.destination_j);
            char second_ch = (char)('1'+hod.origin_i);
            char fourth_ch = (char)('1'+hod.destination_i);
            assert(field[hod.origin_i][hod.origin_j] != 0);
            if (field[hod.origin_i][hod.origin_j] == WHITE_KING) my_move += 'K';
            if (field[hod.origin_i][hod.origin_j] == WHITE_QUEEN) my_move += 'Q';
            if (field[hod.origin_i][hod.origin_j] == WHITE_ROOK) my_move += 'R';
            if (field[hod.origin_i][hod.origin_j] == WHITE_KNIGHT) my_move += 'N';
            if (field[hod.origin_i][hod.origin_j] == WHITE_BISHOP) my_move += 'B';
            if (field[hod.destination_i][hod.destination_j] != 0) {
                my_move += first_ch;
                my_move += second_ch;
                my_move += 'x';
                my_move += third_ch;
                my_move += fourth_ch;
            } else {
                my_move += first_ch;
                my_move += second_ch;
                my_move += '-';
                my_move += third_ch;
                my_move += fourth_ch;
            }
            if (hod.destination_i == 7 && field[hod.origin_i][hod.origin_j] == WHITE_PAWN) my_move += "Q"; // !! проводим только Q
            return;
        }
    }
    assert(false);
}
void calc_linear () {
    // шахи королю (горизонтальные приоритет)
    vector<Move> moves;
    ll hisKingI = -1;
    ll hisKingJ = -1;
    fo(i, 0, 8) {
        fo(j, 0, 8) {
            if (field[i][j] == BLACK_KING) {
                hisKingI = i;
                hisKingJ = j;
                break;
            }
        }
    }
    assert(hisKingI != -1);
    assert(hisKingJ != -1);
    fo(i, 0, 8) {
        fo(j, 0, 8) {
            if (field[i][j] == WHITE_ROOK || field[i][j] == WHITE_QUEEN) {
                ll temp_i = i+1;
                while (isCellPossible(temp_i, j)) {
                    if (field[temp_i][j] == 0 && temp_i == hisKingI) {
                        moves.push_back(Move{i, j, temp_i, j, (i != my_last_move_i || j != my_last_move_j)});
                    }
                    if (field[temp_i][j] != 0) {
                        break;
                    }
                    temp_i += 1;
                }
                temp_i = i-1;
                while (isCellPossible(temp_i, j)) {
                    if (field[temp_i][j] == 0 && temp_i == hisKingI) {
                        moves.push_back(Move{i, j, temp_i, j, (i != my_last_move_i || j != my_last_move_j)});
                    }
                    if (field[temp_i][j] != 0) {
                        break;
                    }
                    temp_i -= 1;
                }
            }
            if (field[i][j] == WHITE_QUEEN) {
                ll temp_i = i-1;
                ll temp_j = j+1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (field[temp_i][temp_j] == 0 && temp_i == hisKingI) {
                        moves.push_back(Move{i, j, temp_i, temp_j, i-temp_i});
                    }
                    if (field[temp_i][temp_j] != 0) {
                        break;
                    }
                    temp_i -= 1;
                    temp_j += 1;
                }
                temp_i = i-1;
                temp_j = j-1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (field[temp_i][temp_j] == 0 && temp_i == hisKingI) {
                        moves.push_back(Move{i, j, temp_i, temp_j, i-temp_i});
                    }
                    if (field[temp_i][temp_j] != 0) {
                        break;
                    }
                    temp_i -= 1;
                    temp_j -= 1;
                }
            }
        }
    }
    sort(all(moves), [] (Move a, Move b) {
        return a.priority > b.priority;
    });
    for (Move hod: moves) {
        assert(isCellPossible(hod.origin_i, hod.origin_j));
        assert(hod.origin_i != hod.destination_i || hod.origin_j != hod.destination_j);
        assert(isCellPossible(hod.destination_i, hod.destination_j));
        if (isMovePossible(hod) && !isStalementAfterMove(hod)) {
            my_last_move_i = hod.destination_i;
            my_last_move_j = hod.destination_j;
            char first_ch = (char)('a'+hod.origin_j);
            char third_ch = (char)('a'+hod.destination_j);
            char second_ch = (char)('1'+hod.origin_i);
            char fourth_ch = (char)('1'+hod.destination_i);
            assert(field[hod.origin_i][hod.origin_j] != 0);
            if (field[hod.origin_i][hod.origin_j] == WHITE_KING) my_move += 'K';
            if (field[hod.origin_i][hod.origin_j] == WHITE_QUEEN) my_move += 'Q';
            if (field[hod.origin_i][hod.origin_j] == WHITE_ROOK) my_move += 'R';
            if (field[hod.origin_i][hod.origin_j] == WHITE_KNIGHT) my_move += 'N';
            if (field[hod.origin_i][hod.origin_j] == WHITE_BISHOP) my_move += 'B';
            if (field[hod.destination_i][hod.destination_j] != 0) {
                my_move += first_ch;
                my_move += second_ch;
                my_move += 'x';
                my_move += third_ch;
                my_move += fourth_ch;
            } else {
                my_move += first_ch;
                my_move += second_ch;
                my_move += '-';
                my_move += third_ch;
                my_move += fourth_ch;
            }
            if (hod.destination_i == 7 && field[hod.origin_i][hod.origin_j] == WHITE_PAWN) my_move += "Q"; // !! проводим только Q
            return;
        }
    }
    assert(false);
}
void calc_remove () {
    vector<Move> moves;
    fo(i, 0, 8) {
        fo(j, 0, 8) {
            if (field[i][j] == WHITE_KING) {
                forr(ii, i-1, i+1) {
                    forr (jj, j-1, j+1) {
                        if (!isCellPossible(ii, jj)) continue;
                        if (ii == i && jj == j || field[ii][jj] < 20 && field[ii][jj] != 0) continue;
                        if (isCellPossible(ii, jj)) moves.push_back(Move{i, j, ii, jj, i-ii}); // ходим королем только от шаха
                    }
                }
            }
            if (field[i][j] == WHITE_KNIGHT) {
                if (isCellPossible(i-1, j-2) && field[i-1][j-2] == 0) {
                    moves.push_back(Move{i, j, i-1, j-2, 20-(i-1)});
                }
                if (isCellPossible(i-1, j+2) && field[i-1][j+2] == 0) {
                    moves.push_back(Move{i, j, i-1, j+2, 20-(i-1)});
                }
                if (isCellPossible(i-2, j+1) && field[i-2][j+1] == 0) {
                    moves.push_back(Move{i, j, i-2, j+1, 20-(i-2)});
                }
                if (isCellPossible(i-2, j-1) && field[i-2][j-1] == 0) {
                    moves.push_back(Move{i, j, i-2, j-1, 20-(i-2)});
                }
            }
            if (field[i][j] == WHITE_ROOK || field[i][j] == WHITE_QUEEN) {
                ll temp_i = i-1;
                while (isCellPossible(temp_i, j)) {
                    if (field[temp_i][j] != 0) {
                        if (field[temp_i][j] > 20) {
                            moves.push_back(Move{i, j, temp_i, j, 20-(temp_i)-(field[i][j] == WHITE_QUEEN)});
                        }
                        break;
                    }
                    temp_i -= 1;
                }
            }
            if (field[i][j] == WHITE_QUEEN) {
                ll temp_i = i-1;
                ll temp_j = j-1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (field[temp_i][temp_j] == 0) {
                        moves.push_back(Move{i, j, temp_i, temp_j, i-temp_i});
                    }
                    if (field[temp_i][temp_j] != 0) {
                        break;
                    }
                    temp_i -= 1;
                    temp_j -= 1;
                }
                temp_i = i-1;
                temp_j = j+1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (field[temp_i][temp_j] == 0) {
                        moves.push_back(Move{i, j, temp_i, temp_j, i-temp_i});
                    }
                    if (field[temp_i][temp_j] != 0) {
                        break;
                    }
                    temp_i -= 1;
                    temp_j += 1;
                }
            }
        }
    }
    sort(all(moves), [] (Move a, Move b) {
        return a.priority > b.priority;
    });
    for (Move hod: moves) {
        assert(isCellPossible(hod.origin_i, hod.origin_j));
        assert(hod.origin_i != hod.destination_i || hod.origin_j != hod.destination_j);
        assert(isCellPossible(hod.destination_i, hod.destination_j));
        if (isMovePossible(hod) && !isStalementAfterMove(hod)) {
            char first_ch = (char)('a'+hod.origin_j);
            char third_ch = (char)('a'+hod.destination_j);
            char second_ch = (char)('1'+hod.origin_i);
            char fourth_ch = (char)('1'+hod.destination_i);
            assert(field[hod.origin_i][hod.origin_j] != 0);
            if (field[hod.origin_i][hod.origin_j] == WHITE_KING) my_move += 'K';
            if (field[hod.origin_i][hod.origin_j] == WHITE_QUEEN) my_move += 'Q';
            if (field[hod.origin_i][hod.origin_j] == WHITE_ROOK) my_move += 'R';
            if (field[hod.origin_i][hod.origin_j] == WHITE_KNIGHT) my_move += 'N';
            if (field[hod.origin_i][hod.origin_j] == WHITE_BISHOP) my_move += 'B';
            if (field[hod.destination_i][hod.destination_j] != 0) {
                my_move += first_ch;
                my_move += second_ch;
                my_move += 'x';
                my_move += third_ch;
                my_move += fourth_ch;
            } else {
                my_move += first_ch;
                my_move += second_ch;
                my_move += '-';
                my_move += third_ch;
                my_move += fourth_ch;
            }
            if (hod.destination_i == 7 && field[hod.origin_i][hod.origin_j] == WHITE_PAWN) my_move += "Q"; // !! проводим только Q
            return;
        }
    }
    assert(false);
}
void solve() {
    field[0][0] = WHITE_ROOK;   field[7][0] = BLACK_ROOK;
    field[0][1] = WHITE_KNIGHT; field[7][1] = BLACK_KNIGHT;
    field[0][2] = WHITE_BISHOP; field[7][2] = BLACK_BISHOP;
    field[0][3] = WHITE_QUEEN;  field[7][3] = BLACK_QUEEN;
    field[0][4] = WHITE_KING;   field[7][4] = BLACK_KING;
    field[0][5] = WHITE_BISHOP; field[7][5] = BLACK_BISHOP;
    field[0][6] = WHITE_KNIGHT; field[7][6] = BLACK_KNIGHT;
    field[0][7] = WHITE_ROOK;   field[7][7] = BLACK_ROOK;

    field[1][0] = WHITE_PAWN;   field[6][0] = BLACK_PAWN;
    field[1][1] = WHITE_PAWN;   field[6][1] = BLACK_PAWN;
    field[1][2] = WHITE_PAWN;   field[6][2] = BLACK_PAWN;
    field[1][3] = WHITE_PAWN;   field[6][3] = BLACK_PAWN;
    field[1][4] = WHITE_PAWN;   field[6][4] = BLACK_PAWN;
    field[1][5] = WHITE_PAWN;   field[6][5] = BLACK_PAWN;
    field[1][6] = WHITE_PAWN;   field[6][6] = BLACK_PAWN;
    field[1][7] = WHITE_PAWN;   field[6][7] = BLACK_PAWN;
    ll his_material = 11111;
    while (true) {
        ll hisKingI = -1;
        ll hisKingJ = -1;
        fo(i, 0, 8) {
            fo(j, 0, 8) {
                if (field[i][j] == BLACK_KING) {
                    hisKingI = i;
                    hisKingJ = j;
                    break;
                }
            }
        }
        assert(hisKingI != -1);
        assert(hisKingJ != -1);
        string before_move_status;
        cin >> before_move_status;
        if (before_move_status != "playing") {
            break;
        }
        my_move = "";
        ll our_queens = 0; fo(i, 0, 8) fo(j, 0, 8) if (field[i][j] == WHITE_QUEEN) our_queens += 1;
        ll max_i_white_pawn = 0; fo(i, 0, 8) fo(j, 0, 8) if (field[i][j] == WHITE_PAWN) max_i_white_pawn = i;
        if (his_material > 0 || our_queens < 3 || max_i_white_pawn != 1) {
            calc();
        }
        else {
            ll max_i_white = 0; fo(i, 0, 8) fo(j, 0, 8) if (field[i][j] != 0 && field[i][j] < 20) max_i_white = i;
            if (max_i_white >= hisKingI) {
                calc_remove();
            } else {
                calc_linear();
            }
        }
        assert(!my_move.empty());
        cout << my_move << endl;
        cout.flush();
        new_move = my_move; nash_hod = true; process(); nash_hod = false;
        his_material = 0;
        fo(i, 0, 8) fo(j, 0, 8) if (field[i][j] > 20 && field[i][j] != BLACK_KING) his_material += 1;
        string after_move_status;
        cin >> after_move_status;
        if (after_move_status != "playing") {
            break;
        }
        cin >> new_move;
        assert(!new_move.empty());
        process();
    }
}
int32_t main (int32_t argc, char* argv[]) {
    bool use_fast_io = true;
    for (int32_t i = 1; i < argc; ++i)
        if (string(argv[i]) == "-local-no-fast-io") {
            use_fast_io = false;
//            cout << "No fastIO" << endl;
            break;
        }
    if (use_fast_io) {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        cerr.tie(nullptr);
        clog.tie(nullptr);
    }
    ll tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}