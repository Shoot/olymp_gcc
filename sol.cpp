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
#define debug(...) 930
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math,trapv")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distrib2(1ll, 2ll);
set<vector<vector<ll>>> st;
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
bool isCellPossible (ll i, ll j) {
    return i < 8 && i >= 0 && j < 8 && j >= 0;
}
struct Move {
    ll origin_i, origin_j, destination_i, destination_j;
    ll priority;
};
bool ferz_daet_shah (ll i, ll j) {
    ll temp_i = i+1;
    ll temp_j = j+1;
    while (isCellPossible(temp_i, temp_j)) {
        if (field[temp_i][temp_j] != 0) {
            if (field[temp_i][temp_j] == BLACK_KING) return true;
            break;
        }
        temp_i += 1;
        temp_j += 1;
    }
    temp_i = i-1;
    temp_j = j-1;
    while (isCellPossible(temp_i, temp_j)) {
        if (field[temp_i][temp_j] != 0) {
            if (field[temp_i][temp_j] == BLACK_KING) return true;
            break;
        }
        temp_i -= 1;
        temp_j -= 1;
    }
    temp_i = i+1;
    temp_j = j-1;
    while (isCellPossible(temp_i, temp_j)) {
        if (field[temp_i][temp_j] != 0) {
            if (field[temp_i][temp_j] == BLACK_KING) return true;
            break;
        }
        temp_i += 1;
        temp_j -= 1;
    }
    temp_i = i-1;
    temp_j = j+1;
    while (isCellPossible(temp_i, temp_j)) {
        if (field[temp_i][temp_j] != 0) {
            if (field[temp_i][temp_j] == BLACK_KING) return true;
            break;
        }
        temp_i -= 1;
        temp_j += 1;
    }


    temp_i = i+1;
    while (isCellPossible(temp_i, j)) {
        if (field[temp_i][j] != 0) {
            if (field[temp_i][j] == BLACK_KING) return true;
            break;
        }
        temp_i += 1;
    }
    temp_i = i-1;
    while (isCellPossible(temp_i, j)) {
        if (field[temp_i][j] != 0) {
            if (field[temp_i][j] == BLACK_KING) return true;
            break;
        }
        temp_i -= 1;
    }

    temp_j = j+1;
    while (isCellPossible(i, temp_j)) {
        if (field[i][temp_j] != 0) {
            if (field[i][temp_j] == BLACK_KING) return true;
            break;
        }
        temp_j += 1;
    }
    temp_j = j-1;
    while (isCellPossible(i, temp_j)) {
        if (field[i][temp_j] != 0) {
            if (field[i][temp_j] == BLACK_KING) return true;
            break;
        }
        temp_j -= 1;
    }

    return false;
}
bool ferz_napadaet (ll i, ll j) {
    if (distrib2(rng) == 1) {
        return ferz_daet_shah(i, j);
    }
    ll temp_i = i+1;
    ll temp_j = j+1;
    while (isCellPossible(temp_i, temp_j)) {
        if (field[temp_i][temp_j] != 0) {
            if (field[temp_i][temp_j] > 20 && field[temp_i][temp_j] != BLACK_KING) return true;
            break;
        }
        temp_i += 1;
        temp_j += 1;
    }
    temp_i = i-1;
    temp_j = j-1;
    while (isCellPossible(temp_i, temp_j)) {
        if (field[temp_i][temp_j] != 0) {
            if (field[temp_i][temp_j] > 20 && field[temp_i][temp_j] != BLACK_KING) return true;
            break;
        }
        temp_i -= 1;
        temp_j -= 1;
    }
    temp_i = i+1;
    temp_j = j-1;
    while (isCellPossible(temp_i, temp_j)) {
        if (field[temp_i][temp_j] != 0) {
            if (field[temp_i][temp_j] > 20 && field[temp_i][temp_j] != BLACK_KING) return true;
            break;
        }
        temp_i += 1;
        temp_j -= 1;
    }
    temp_i = i-1;
    temp_j = j+1;
    while (isCellPossible(temp_i, temp_j)) {
        if (field[temp_i][temp_j] != 0) {
            if (field[temp_i][temp_j] > 20 && field[temp_i][temp_j] != BLACK_KING) return true;
            break;
        }
        temp_i -= 1;
        temp_j += 1;
    }


    temp_i = i+1;
    while (isCellPossible(temp_i, j)) {
        if (field[temp_i][j] != 0) {
            if (field[temp_i][j] > 20 && field[temp_i][j] != BLACK_KING) return true;
            break;
        }
        temp_i += 1;
    }
    temp_i = i-1;
    while (isCellPossible(temp_i, j)) {
        if (field[temp_i][j] != 0) {
            if (field[temp_i][j] > 20 && field[temp_i][j] != BLACK_KING) return true;
            break;
        }
        temp_i -= 1;
    }

    temp_j = j+1;
    while (isCellPossible(i, temp_j)) {
        if (field[i][temp_j] != 0) {
            if (field[i][temp_j] > 20 && field[i][temp_j] != BLACK_KING) return true;
            break;
        }
        temp_j += 1;
    }
    temp_j = j-1;
    while (isCellPossible(i, temp_j)) {
        if (field[i][temp_j] != 0) {
            if (field[i][temp_j] > 20 && field[i][temp_j] != BLACK_KING) return true;
            break;
        }
        temp_j -= 1;
    }

    return false;
}
void godo (Move move1) {
    char first_ch = (char)('a'+move1.origin_j);
    char third_ch = (char)('a'+move1.destination_j);
    char second_ch = (char)('1'+move1.origin_i);
    char fourth_ch = (char)('1'+move1.destination_i);
    assert(field[move1.origin_i][move1.origin_j] != 0);
    if (field[move1.origin_i][move1.origin_j] == WHITE_KING) my_move += 'K';
    if (field[move1.origin_i][move1.origin_j] == WHITE_QUEEN) my_move += 'Q';
    if (field[move1.origin_i][move1.origin_j] == WHITE_ROOK) my_move += 'R';
    if (field[move1.origin_i][move1.origin_j] == WHITE_KNIGHT) my_move += 'N';
    if (field[move1.origin_i][move1.origin_j] == WHITE_BISHOP) my_move += 'B';
    if (field[move1.destination_i][move1.destination_j] != 0) {
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
    if (move1.destination_i == 7 && field[move1.origin_i][move1.origin_j] == WHITE_PAWN) my_move += "Q"; // !! проводим только Q
}
void godo_black (Move move1) {
    char first_ch = (char)('a'+move1.origin_j);
    char third_ch = (char)('a'+move1.destination_j);
    char second_ch = (char)('1'+move1.origin_i);
    char fourth_ch = (char)('1'+move1.destination_i);
    assert(field[move1.origin_i][move1.origin_j] != 0);
    if (field[move1.origin_i][move1.origin_j] == BLACK_KING) new_move += 'K';
    if (field[move1.origin_i][move1.origin_j] == BLACK_QUEEN) new_move += 'Q';
    if (field[move1.origin_i][move1.origin_j] == BLACK_ROOK) new_move += 'R';
    if (field[move1.origin_i][move1.origin_j] == BLACK_KNIGHT) new_move += 'N';
    if (field[move1.origin_i][move1.origin_j] == BLACK_BISHOP) new_move += 'B';
    if (field[move1.destination_i][move1.destination_j] != 0) {
        new_move += first_ch;
        new_move += second_ch;
        new_move += 'x';
        new_move += third_ch;
        new_move += fourth_ch;
    } else {
        new_move += first_ch;
        new_move += second_ch;
        new_move += '-';
        new_move += third_ch;
        new_move += fourth_ch;
    }
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
    ll n = (ll)new_move.size();
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
bool isOurMovePossible (Move move) {
    auto copy = field;
    assert(isCellPossible(move.destination_i, move.destination_j));
    assert(isCellPossible(move.origin_i, move.origin_j));
    copy[move.destination_i][move.destination_j] = copy[move.origin_i][move.origin_j];
    copy[move.origin_i][move.origin_j] = 0;
    return !isOurKingUnderAttack(copy);
}
bool isBlackKingAliveAfterMove (vector<vector<ll>> temp_f, Move move) {
    temp_f[move.destination_i][move.destination_j] = temp_f[move.origin_i][move.origin_j];
    temp_f[move.origin_i][move.origin_j] = 0;
    ll hisKingI = -1;
    ll hisKingJ = -1;
    fo(i, 0, 8) {
        fo(j, 0, 8) {
            assert(isCellPossible(i, j));
            if (temp_f[i][j] == BLACK_KING) {
                hisKingI = i;
                hisKingJ = j;
            }
        }
    }
    assert(hisKingI != -1 && hisKingJ != -1);
    fo(i, 0, 8) {
        fo(j, 0, 8) {
            if (temp_f[i][j] == WHITE_KING) {
                if (abs(i-hisKingI) <= 1 && abs(j-hisKingJ) <= 1) {
                    return false;
                }
            }
            if (temp_f[i][j] == WHITE_KNIGHT) {
                if (i-1 == hisKingI && j-2 == hisKingJ) return false;
                if (i-2 == hisKingI && j-1 == hisKingJ) return false;
                if (i+1 == hisKingI && j+2 == hisKingJ) return false;
                if (i+2 == hisKingI && j+1 == hisKingJ) return false;

                if (i+2 == hisKingI && j-1 == hisKingJ) return false;
                if (i+1 == hisKingI && j-2 == hisKingJ) return false;
                if (i-1 == hisKingI && j+2 == hisKingJ) return false;
                if (i-2 == hisKingI && j+1 == hisKingJ) return false;
            }
            if (temp_f[i][j] == WHITE_PAWN) {
                if (i+1 == hisKingI && abs(hisKingJ-j) == 1) {
                    return false;
                }
            }
            if (temp_f[i][j] == WHITE_ROOK || temp_f[i][j] == WHITE_QUEEN) {
                ll temp_i = i+1;
                while (isCellPossible(temp_i, j)) {
                    if (temp_f[temp_i][j] != 0) {
                        if (temp_f[temp_i][j] == BLACK_KING) return false;
                        break;
                    }
                    temp_i += 1;
                }
                temp_i = i-1;
                while (isCellPossible(temp_i, j)) {
                    if (temp_f[temp_i][j] != 0) {
                        if (temp_f[temp_i][j] == BLACK_KING) return false;
                        break;
                    }
                    temp_i -= 1;
                }

                ll temp_j = j+1;
                while (isCellPossible(i, temp_j)) {
                    if (temp_f[i][temp_j] != 0) {
                        if (temp_f[i][temp_j] == BLACK_KING) return false;
                        break;
                    }
                    temp_j += 1;
                }

                temp_j = j-1;
                while (isCellPossible(i, temp_j)) {
                    if (temp_f[i][temp_j] != 0) {
                        if (temp_f[i][temp_j] == BLACK_KING) return false;
                        break;
                    }
                    temp_j -= 1;
                }
            }
            if (temp_f[i][j] == WHITE_BISHOP || temp_f[i][j] == WHITE_QUEEN) {
                ll temp_i = i + 1;
                ll temp_j = j + 1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (temp_f[temp_i][temp_j] != 0) {
                        if (temp_f[temp_i][temp_j] == BLACK_KING) return false;
                        break;
                    }
                    temp_i += 1;
                    temp_j += 1;
                }
                temp_i = i - 1;
                temp_j = j - 1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (temp_f[temp_i][temp_j] != 0) {
                        if (temp_f[temp_i][temp_j] == BLACK_KING) return false;
                        break;
                    }
                    temp_i -= 1;
                    temp_j -= 1;
                }
                temp_i = i + 1;
                temp_j = j - 1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (temp_f[temp_i][temp_j] != 0) {
                        if (temp_f[temp_i][temp_j] == BLACK_KING) return false;
                        break;
                    }
                    temp_i += 1;
                    temp_j -= 1;
                }
                temp_i = i - 1;
                temp_j = j + 1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (temp_f[temp_i][temp_j] != 0) {
                        if (temp_f[temp_i][temp_j] == BLACK_KING) return false;
                        break;
                    }
                    temp_i -= 1;
                    temp_j += 1;
                }
            }
        }
    }
    return true;
}
bool MAT_CHERNYM (vector<vector<ll>> f) {
    ll BlackKingI = -1;
    ll BlackKingJ = -1;
    fo(i, 0, 8) {
        fo(j, 0, 8) {
            if (f[i][j] == BLACK_KING) {
                BlackKingI = i;
                BlackKingJ = j;
            }
        }
    }
    assert(BlackKingI != -1 && BlackKingJ != -1);
    vector<Move> moves;
    forr(i, BlackKingI-1, BlackKingI+1) {
        forr(j, BlackKingJ-1, BlackKingJ+1) {
            if (i == BlackKingI && j == BlackKingJ) continue;
            if (isCellPossible(i, j) && f[i][j] < 20 && isBlackKingAliveAfterMove(f, Move{BlackKingI, BlackKingJ, i, j, -666})) {
                return false;
            }
        }
    }
    fo(i, 0, 8) {
        fo(j, 0, 8) {
            if (f[i][j] == WHITE_QUEEN) {
                ll temp_i = i+1;
                ll temp_j = j+1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (f[temp_i][temp_j] != 0) {
                        if (f[temp_i][temp_j] == BLACK_KING) return true;
                        break;
                    }
                    temp_i += 1;
                    temp_j += 1;
                }
                temp_i = i-1;
                temp_j = j-1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (f[temp_i][temp_j] != 0) {
                        if (f[temp_i][temp_j] == BLACK_KING) return true;
                        break;
                    }
                    temp_i -= 1;
                    temp_j -= 1;
                }
                temp_i = i+1;
                temp_j = j-1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (f[temp_i][temp_j] != 0) {
                        if (f[temp_i][temp_j] == BLACK_KING) return true;
                        break;
                    }
                    temp_i += 1;
                    temp_j -= 1;
                }
                temp_i = i-1;
                temp_j = j+1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (f[temp_i][temp_j] != 0) {
                        if (f[temp_i][temp_j] == BLACK_KING) return true;
                        break;
                    }
                    temp_i -= 1;
                    temp_j += 1;
                }


                temp_i = i+1;
                while (isCellPossible(temp_i, j)) {
                    if (f[temp_i][j] != 0) {
                        if (f[temp_i][j] == BLACK_KING) return true;
                        break;
                    }
                    temp_i += 1;
                }
                temp_i = i-1;
                while (isCellPossible(temp_i, j)) {
                    if (f[temp_i][j] != 0) {
                        if (f[temp_i][j] == BLACK_KING) return true;
                        break;
                    }
                    temp_i -= 1;
                }

                temp_j = j+1;
                while (isCellPossible(i, temp_j)) {
                    if (f[i][temp_j] != 0) {
                        if (f[i][temp_j] == BLACK_KING) return true;
                        break;
                    }
                    temp_j += 1;
                }

                temp_j = j-1;
                while (isCellPossible(i, temp_j)) {
                    if (f[i][temp_j] != 0) {
                        if (f[i][temp_j] == BLACK_KING) return true;
                        break;
                    }
                    temp_j -= 1;
                }
            }
        }
    }
    return false;
}
bool isStalementAfterMove (Move move) {
    auto copy = field;
    assert(isCellPossible(move.destination_i, move.destination_j));
    assert(isCellPossible(move.origin_i, move.origin_j));
    if (copy[move.origin_i][move.origin_j] == WHITE_PAWN && move.origin_i == 6) {
        copy[move.origin_i][move.origin_j] = 0;
        copy[move.destination_i][move.destination_j] = WHITE_QUEEN;
    } else {
        copy[move.destination_i][move.destination_j] = copy[move.origin_i][move.origin_j];
        copy[move.origin_i][move.origin_j] = 0;
    }
    if (MAT_CHERNYM(copy)) return false;
    fo(i, 0, 8) {
        fo(j, 0, 8) {
            if (copy[i][j] == BLACK_PAWN && isCellPossible(i-1, j) && copy[i-1][j] == 0 && isBlackKingAliveAfterMove(copy, Move{i, j, i-1, j, -666})) {
                return false;
            }
        }
    }
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
            if (copy[ii][jj] != 0) continue;
            if (isBlackKingAliveAfterMove(copy, Move{hisKingI, hisKingJ, ii, jj, -666})) return false;
        }
    }
    return true;
}
vector<Move> getWhiteQueenMoves (vector<vector<ll>> & f) {
    vector<Move> moves;
    fo(i, 0, 8) {
        fo(j, 0, 8) {
            if (f[i][j] == WHITE_QUEEN) {
                ll temp_i = i+1;
                ll temp_j = j+1;
                while (isCellPossible(temp_i, temp_j) && f[temp_i][temp_j] == 0) {
                    moves.push_back(Move{i, j, temp_i, temp_j, -666});
                    temp_i += 1;
                    temp_j += 1;
                }

                temp_i = i-1;
                temp_j = j+1;
                while (isCellPossible(temp_i, temp_j) && f[temp_i][temp_j] == 0) {
                    moves.push_back(Move{i, j, temp_i, temp_j, -666});
                    temp_i -= 1;
                    temp_j += 1;
                }

                temp_i = i+1;
                temp_j = j-1;
                while (isCellPossible(temp_i, temp_j) && f[temp_i][temp_j] == 0) {
                    moves.push_back(Move{i, j, temp_i, temp_j, -666});
                    temp_i += 1;
                    temp_j -= 1;
                }

                temp_i = i-1;
                temp_j = j-1;
                while (isCellPossible(temp_i, temp_j) && f[temp_i][temp_j] == 0) {
                    moves.push_back(Move{i, j, temp_i, temp_j, -666});
                    temp_i -= 1;
                    temp_j -= 1;
                }
            }
        }
    }
    return moves;
}
vector<Move> getBlackKingMoves (vector<vector<ll>> & f) {
    ll BlackKingI = -1;
    ll BlackKingJ = -1;
    fo(i, 0, 8) {
        fo(j, 0, 8) {
            if (f[i][j] == BLACK_KING) {
                BlackKingI = i;
                BlackKingJ = j;
            }
        }
    }
    assert(BlackKingI != -1 && BlackKingJ != -1);
    vector<Move> moves;
    forr(i, BlackKingI-1, BlackKingI+1) {
        forr(j, BlackKingJ-1, BlackKingJ+1) {
            if (i == BlackKingI && j == BlackKingJ) continue;
            if (isCellPossible(i, j) && f[i][j] == 0 && isBlackKingAliveAfterMove(f, Move{BlackKingI, BlackKingJ, i, j, -666})) {
                moves.push_back(Move{BlackKingI, BlackKingJ, i, j, -666});
            }
        }
    }
    return moves;
}
void calc () {
    vector<Move> moves;
    fo(i, 0, 8) {
        fo(j, 0, 8) {
            if (field[i][j] == WHITE_KING) {
                forr(ii, i-1, i+1) {
                    forr (jj, j-1, j+1) {
                        if (!isCellPossible(ii, jj)) continue;
                        if (ii == i && jj == j || field[ii][jj] < 20 && field[ii][jj] != 0) continue;
                        if (isCellPossible(ii, jj)) moves.push_back(Move{i, j, ii, jj, -2000}); // ходим королем только от шаха
                    }
                }
            }
            if (field[i][j] == WHITE_PAWN && i == 1) {
                if (field[i+2][j] == 0 && field[i+1][j] == 0) {
                    moves.push_back(Move{i, j, i+2, j, i+2+(j != 3 && j != 4 && j != 5)}); // проводим пешки
                }
            }
            if (field[i][j] == WHITE_PAWN) {
                if (isCellPossible(i+1, j) && field[i+1][j] == 0) {
                    moves.push_back(Move{i, j, i+1, j, i+1+(j != 3 && j != 4 && j != 5)}); // проводим пешки
                }
                if (isCellPossible(i+1, j+1) && field[i+1][j+1] > 20) {
                    moves.push_back(Move{i, j, i+1, j+1, 20-(i+1)+(j != 3 && j != 4 && j != 5)}); // проводим пешки
                }
                if (isCellPossible(i+1, j-1) && field[i+1][j-1] > 20) {
                    moves.push_back(Move{i, j, i+1, j-1, 20-(i+1)+(j != 3 && j != 4 && j != 5)}); // проводим пешки
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
            if (field[i][j] == WHITE_BISHOP || field[i][j] == WHITE_QUEEN) {
                ll temp_i = i-1;
                ll temp_j = j+1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (field[temp_i][temp_j] != 0) {
                        if (field[temp_i][temp_j] > 20) {
                            moves.push_back(Move{i, j, temp_i, temp_j, 20-(temp_i)-(field[i][j] == WHITE_QUEEN)});
                        }
                        break;
                    }
                    temp_i -= 1;
                    temp_j += 1;
                }
                temp_i = i-1;
                temp_j = j-1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (field[temp_i][temp_j] != 0) {
                        if (field[temp_i][temp_j] > 20) {
                            moves.push_back(Move{i, j, temp_i, temp_j, 20-(temp_i)-(field[i][j] == WHITE_QUEEN)});
                        }
                        break;
                    }
                    temp_i -= 1;
                    temp_j -= 1;
                }
                temp_i = i+1;
                temp_j = j+1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (field[temp_i][temp_j] != 0) {
                        if (field[temp_i][temp_j] > 20) {
                            moves.push_back(Move{i, j, temp_i, temp_j, 20-(temp_i)-(field[i][j] == WHITE_QUEEN)});
                        }
                        break;
                    }
                    temp_i += 1;
                    temp_j += 1;
                }
                temp_i = i+1;
                temp_j = j-1;
                while (isCellPossible(temp_i, temp_j)) {
                    if (field[temp_i][temp_j] != 0) {
                        if (field[temp_i][temp_j] > 20) {
                            moves.push_back(Move{i, j, temp_i, temp_j, 20-(temp_i)-(field[i][j] == WHITE_QUEEN)});
                        }
                        break;
                    }
                    temp_i += 1;
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
            if (field[i][j] == WHITE_QUEEN) {
                ll temp_i = i-1;
                ll temp_j = j+1;
                while (isCellPossible(temp_i, temp_j) && field[temp_i][temp_j] == 0) {
                    if (ferz_napadaet(temp_i, temp_j)) moves.push_back(Move{i, j, temp_i, temp_j, -100});
                    moves.push_back(Move{i, j, temp_i, temp_j, -1000});
                    temp_i -= 1;
                    temp_j += 1;
                }
                temp_i = i-1;
                temp_j = j-1;
                while (isCellPossible(temp_i, temp_j) && field[temp_i][temp_j] == 0) {
                    if (ferz_napadaet(temp_i, temp_j)) moves.push_back(Move{i, j, temp_i, temp_j, -100});
                    moves.push_back(Move{i, j, temp_i, temp_j, -1000});
                    temp_i -= 1;
                    temp_j -= 1;
                }
                temp_i = i+1;
                temp_j = j+1;
                while (isCellPossible(temp_i, temp_j) && field[temp_i][temp_j] == 0) {
                    if (ferz_napadaet(temp_i, temp_j)) moves.push_back(Move{i, j, temp_i, temp_j, -100});
                    moves.push_back(Move{i, j, temp_i, temp_j, -1000});
                    temp_i += 1;
                    temp_j += 1;
                }
                temp_i = i+1;
                temp_j = j-1;
                while (isCellPossible(temp_i, temp_j) && field[temp_i][temp_j] == 0) {
                    if (ferz_napadaet(temp_i, temp_j)) moves.push_back(Move{i, j, temp_i, temp_j, -100});
                    moves.push_back(Move{i, j, temp_i, temp_j, -1000});
                    temp_i += 1;
                    temp_j -= 1;
                }


                temp_j = j+1;
                while (isCellPossible(i, temp_j) && field[i][temp_j] == 0) {
                    if (ferz_napadaet(i, temp_j)) moves.push_back(Move{i, j, i, temp_j, -100});
                    moves.push_back(Move{i, j, i, temp_j, -1000});
                    temp_j += 1;
                }
                temp_j = j-1;
                while (isCellPossible(i, temp_j) && field[i][temp_j] == 0) {
                    if (ferz_napadaet(i, temp_j)) moves.push_back(Move{i, j, i, temp_j, -100});
                    moves.push_back(Move{i, j, i, temp_j, -1000});
                    temp_j -= 1;
                }
                temp_i = i+1;
                while (isCellPossible(temp_i, j) && field[temp_i][j] == 0) {
                    if (ferz_napadaet(temp_i, j)) moves.push_back(Move{i, j, temp_i, j, -100});
                    moves.push_back(Move{i, j, temp_i, j, -1000});
                    temp_i += 1;
                }
                temp_i = i-1;
                while (isCellPossible(temp_i, j) && field[temp_i][j] == 0) {
                    if (ferz_napadaet(temp_i, j)) moves.push_back(Move{i, j, temp_i, j, -100});
                    moves.push_back(Move{i, j, temp_i, j, -1000});
                    temp_i -= 1;
                }
            }
        }
    }
    shuffle(all(moves), rng);
    sort(all(moves), [] (Move a, Move b) {
        return a.priority > b.priority;
    });
    for (Move hod: moves) {
        assert(isCellPossible(hod.origin_i, hod.origin_j));
        assert(hod.origin_i != hod.destination_i || hod.origin_j != hod.destination_j);
        assert(isCellPossible(hod.destination_i, hod.destination_j));
        if (isStalementAfterMove(hod)) continue;
        if (isOurMovePossible(hod)) {
            auto test = field;
            test[hod.destination_i][hod.destination_j] = test[hod.origin_i][hod.origin_j];
            test[hod.origin_i][hod.origin_j] = 0;
            if (st.contains(test)) continue;
            godo(hod);
            st.insert(test);
            return;
        }
    }
    assert(false);
}
void calc_black () {
    vector<Move> moves;
    fo(i, 0, 8) {
        fo(j, 0, 8) {
            if (field[i][j] == BLACK_KING) {
                forr(ii, i-1, i+1) {
                    forr (jj, j-1, j+1) {
                        if (!isCellPossible(ii, jj)) continue;
                        if (ii == i && jj == j || field[ii][jj] > 20) continue;
                        if (isCellPossible(ii, jj)) moves.push_back(Move{i, j, ii, jj, -500}); // ходим королем только от шаха
                    }
                }
            }
            if (field[i][j] == BLACK_PAWN && i == 6) {
                if (field[i-2][j] == 0 && field[i-1][j] == 0) {
                    moves.push_back(Move{i, j, i-2, j, i+2}); // проводим пешки
                }
            }
            if (field[i][j] == BLACK_PAWN) {
                if (isCellPossible(i-1, j) && field[i-1][j] == 0) {
                    moves.push_back(Move{i, j, i-1, j, i+1}); // проводим пешки
                }
                if (isCellPossible(i-1, j+1) && field[i-1][j+1] < 20 && field[i-1][j+1] != 0) {
                    moves.push_back(Move{i, j, i-1, j+1, 20-(i+1)}); // проводим пешки
                }
                if (isCellPossible(i-1, j-1) && field[i-1][j-1] < 20 && field[i-1][j-1] != 0) {
                    moves.push_back(Move{i, j, i-1, j-1, 20-(i+1)}); // проводим пешки
                }
            }
            if (field[i][j] == BLACK_KNIGHT) {
                if (isCellPossible(i+2, j+1)) {
                    moves.push_back(Move{i, j, i+2, j+1, 20-(i+2)});
                }
                if (isCellPossible(i+1, j+2)) {
                    moves.push_back(Move{i, j, i+1, j+2, 20-(i+1)});
                }
                if (isCellPossible(i-1, j-2)) {
                    moves.push_back(Move{i, j, i-1, j-2, 20-(i-1)});
                }
                if (isCellPossible(i-1, j+2)) {
                    moves.push_back(Move{i, j, i-1, j+2, 20-(i-1)});
                }
                if (isCellPossible(i-2, j+1)) {
                    moves.push_back(Move{i, j, i-2, j+1, 20-(i-2)});
                }
                if (isCellPossible(i+2, j-1)) {
                    moves.push_back(Move{i, j, i+2, j-1, 20-(i+2)});
                }
                if (isCellPossible(i+1, j-2)) {
                    moves.push_back(Move{i, j, i+1, j-2, 20-(i+1)});
                }
                if (isCellPossible(i-2, j-1)) {
                    moves.push_back(Move{i, j, i-2, j-1, 20-(i-2)});
                }
            }
            if (field[i][j] == BLACK_BISHOP || field[i][j] == BLACK_QUEEN) {
                ll temp_i = i-1;
                ll temp_j = j+1;
                while (isCellPossible(temp_i, temp_j)) {
                    moves.push_back(Move{i, j, temp_i, temp_j, 20-(temp_i)-(field[i][j] == BLACK_QUEEN)});
                    if (field[temp_i][temp_j] != 0) {
                        break;
                    }
                    temp_i -= 1;
                    temp_j += 1;
                }
                temp_i = i-1;
                temp_j = j-1;
                while (isCellPossible(temp_i, temp_j)) {
                    moves.push_back(Move{i, j, temp_i, temp_j, 20-(temp_i)-(field[i][j] == BLACK_QUEEN)});
                    if (field[temp_i][temp_j] != 0) {
                        break;
                    }
                    temp_i -= 1;
                    temp_j -= 1;
                }
                temp_i = i+1;
                temp_j = j+1;
                while (isCellPossible(temp_i, temp_j)) {
                    moves.push_back(Move{i, j, temp_i, temp_j, 20-(temp_i)-(field[i][j] == BLACK_QUEEN)});
                    if (field[temp_i][temp_j] != 0) {
                        break;
                    }
                    temp_i += 1;
                    temp_j += 1;
                }
                temp_i = i+1;
                temp_j = j-1;
                while (isCellPossible(temp_i, temp_j)) {
                    moves.push_back(Move{i, j, temp_i, temp_j, 20-(temp_i)-(field[i][j] == BLACK_QUEEN)});
                    if (field[temp_i][temp_j] != 0) {
                        break;
                    }
                    temp_i += 1;
                    temp_j -= 1;
                }
            }
            if (field[i][j] == BLACK_ROOK || field[i][j] == BLACK_QUEEN) {
                ll temp_j = j+1;
                while (isCellPossible(i, temp_j)) {
                    moves.push_back(Move{i, j, i, temp_j, 20-(i)-(field[i][j] == BLACK_QUEEN)});
                    if (field[i][temp_j] != 0) {
                        break;
                    }
                    temp_j += 1;
                }
                temp_j = j-1;
                while (isCellPossible(i, temp_j)) {
                    moves.push_back(Move{i, j, i, temp_j, 20-(i)-(field[i][j] == BLACK_QUEEN)});
                    if (field[i][temp_j] != 0) {
                        break;
                    }
                    temp_j -= 1;
                }
                ll temp_i = i+1;
                while (isCellPossible(temp_i, j)) {
                    moves.push_back(Move{i, j, temp_i, j, 20-(temp_i)-(field[i][j] == BLACK_QUEEN)});
                    if (field[temp_i][j] != 0) {
                        break;
                    }
                    temp_i += 1;
                }
                temp_i = i-1;
                while (isCellPossible(temp_i, j)) {
                    moves.push_back(Move{i, j, temp_i, j, 20-(temp_i)-(field[i][j] == BLACK_QUEEN)});
                    if (field[temp_i][j] != 0) {
                        break;
                    }
                    temp_i -= 1;
                }
            }
        }
    }
    shuffle(all(moves), rng);
    for (Move m: moves) {
        if (field[m.destination_i][m.destination_j] > 20 || !isBlackKingAliveAfterMove(field, m)) {
            continue;
        }
        godo_black(m);
        break;
    }
}
void do_brute () {
    vector<pair<ll, Move>> first_moves;
    for (auto move1: getWhiteQueenMoves(field)) { // white move
        assert(isOurMovePossible(move1));
        bool move1isGood = true;
        ll move1BlackKingCoords = 99999;
        auto field1 = field;
        field1[move1.destination_i][move1.destination_j] = field1[move1.origin_i][move1.origin_j];
        field1[move1.origin_i][move1.origin_j] = 0;
        if (MAT_CHERNYM(field1)) {
            godo(move1);
            return;
        }
        auto black_moves2 = getBlackKingMoves(field1);
        if (black_moves2.empty()) {
            move1isGood = false;
            continue;
        }
        for (auto move2: black_moves2) {
            bool move2isGood = false;
            auto field2 = field1;
            field2[move2.destination_i][move2.destination_j] = field2[move2.origin_i][move2.origin_j];
            field2[move2.origin_i][move2.origin_j] = 0;
            fo (i, 0, 8) {
                fo(j, 0, 8) {
                    if (field2[i][j] == BLACK_KING) {
                        move1BlackKingCoords = min(move1BlackKingCoords, i+j);
                    }
                }
            }
            for (auto move3: getWhiteQueenMoves(field2)) { // white move
                bool move3isGood = true;
                auto field3 = field2;
                field3[move3.destination_i][move3.destination_j] = field3[move3.origin_i][move3.origin_j];
                field3[move3.origin_i][move3.origin_j] = 0;
                if (MAT_CHERNYM(field3)) continue;
                auto black_moves4 = getBlackKingMoves(field3);
                if (black_moves4.empty()) {
                    move3isGood = false;
                    continue;
                }
                for (auto move4: black_moves4) {
                    bool move4isGood = false;
                    auto field4 = field3;
                    field4[move4.destination_i][move4.destination_j] = field4[move4.origin_i][move4.origin_j];
                    field4[move4.origin_i][move4.origin_j] = 0;
                    for (auto move5: getWhiteQueenMoves(field4)) { // white move
                        bool move5isGood = true;
                        auto field5 = field4;
                        field5[move5.destination_i][move5.destination_j] = field5[move5.origin_i][move5.origin_j];
                        field5[move5.origin_i][move5.origin_j] = 0;
                        if (MAT_CHERNYM(field5)) continue;
                        auto black_moves6 = getBlackKingMoves(field5);
                        if (black_moves6.empty()) {
                            move5isGood = false;
                            continue;
                        }
                        for (auto move6: black_moves6) {
                            bool move6isGood = false;
                            auto field6 = field5;
                            field6[move6.destination_i][move6.destination_j] = field6[move6.origin_i][move6.origin_j];
                            field6[move6.origin_i][move6.origin_j] = 0;
                            for (auto move7: getWhiteQueenMoves(field6)) { // white move
                                auto field7 = field6;
                                field7[move7.destination_i][move7.destination_j] = field7[move7.origin_i][move7.origin_j];
                                field7[move7.origin_i][move7.origin_j] = 0;
                                if (MAT_CHERNYM(field7)) {
                                    move6isGood = true;
                                }
                            }
                            if (!move6isGood) move5isGood = false;
                        }
                        if (move5isGood) move4isGood = true;
                    }
                    if (!move4isGood) move3isGood = false;
                }
                if (move3isGood) move2isGood = true;
            }
            if (!move2isGood) {
                move1isGood = false;
            }
        }
        if (move1isGood) {
            godo(move1);
            return;
        }
        assert(move1BlackKingCoords < 1000);
        first_moves.push_back(make_pair(move1BlackKingCoords, move1));
    }
    // случай когда не нашли мат
    sort(all(first_moves), [] (pair<ll, Move> a, pair<ll, Move> b) {
        return a.first > b.first;
    });
    for(auto move1s: first_moves) {
        auto move1 = move1s.second;
        if (isStalementAfterMove(move1)) continue;
        godo(move1);
        return;
//    calc();
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
        string before_move_status = "playing";
        cin >> before_move_status;
        if (before_move_status != "playing") {
            break;
        }
        my_move = "";
        ll my_queens_number = 0; fo(i, 0, 8) fo(j, 0, 8) if (field[i][j] == WHITE_QUEEN) my_queens_number += 1;
        ll his_material = 0;
        fo(i, 0, 8) fo(j, 0, 8) if (field[i][j] > 20 && field[i][j] != BLACK_KING) his_material += 1;
        ll my_pawns_number = 0; fo(i, 0, 8) fo(j, 0, 8) if (field[i][j] == WHITE_PAWN) my_pawns_number += 1;
        calc();
//        if (his_material > 0 || my_queens_number < 3 || my_pawns_number > 0) {
//            calc();
//        }
//        else {
//            assert(false);
//            do_brute();
//            assert(hisKingI > 2);
//        }
        assert(!my_move.empty());
//        cout << "me: ";
        cout << my_move << endl;
        cout.flush();
        new_move = my_move; nash_hod = true; process(); nash_hod = false;
//        if (MAT_CHERNYM(field)) {
//            cout << "MAT!!" << endl;
//            return;
//        }
        string after_move_status = "playing";
        cin >> after_move_status;
        if (after_move_status != "playing") {
            break;
        }
        new_move = "";
//        calc_black();
        cin >> new_move;
        assert(!new_move.empty());
//        cout << "him: " << new_move << endl;
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