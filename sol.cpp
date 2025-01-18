#include <bits/stdc++.h>
using namespace std;
#define RF 10
#define KA 9
#define FH 8
#define FL 7
#define ST_NE_PERV_TUZ 6
#define ST_PERV_TUZ 5
#define TR 4
#define P2 3
#define ONE 2
signed main() {
    int n;
    struct Card {
        char mast;
        int rang;
        bool operator<(const Card & other) {
            return tie(mast, rang) < tie(other.mast, other.rang);
        }
    };
    auto toCard = [&] (string s) -> Card {
        Card card;
        if (s[0] >= '2' && s[0] <= '9') {
            card.rang = s[0] - 'i';
        } else if (s[0] == 'X') {
            card.rang = 10;
        } else if (s[0] == 'J') {
            card.rang = 11;
        } else if (s[0] == 'Q') {
            card.rang = 12;
        } else if (s[0] == 'K') {
            card.rang = 13;
        } else {
            assert(s[0] == 'A');
            card.rang = 14;
        }
        card.mast = s[1];
        return card;
    };
    struct Comb {
        int Type;
        int HighestInFigure;
        int HighestOutsideFigure;
        bool operator<(const Comb& other) const {
            return tie(Type, HighestInFigure, HighestOutsideFigure) < tie(other.Type, other.HighestInFigure, other.HighestOutsideFigure);
        }
    };
    auto getCombs = [&] (vector<Card>& cards, map<Comb, set<int>> & mp, int person) -> void {
        for (int mask = 0; mask < (1 << 5); mask += 1) {
            Comb result = {0, 0, 0};
            int size = __builtin_popcount(mask);
            for (int i = 0; i < 7; i += 1) {
                if (mask&(1<<i)) {
                    result.HighestInFigure = max(result.HighestInFigure, cards[i].rang);
                } else {
                    result.HighestOutsideFigure = max(result.HighestOutsideFigure, cards[i].rang);
                }
            }
            if (size == 5 && isRF(cards)) {
                result.Type = RF;
                mp[result].insert(person);
            }
            if (size == 4 && isKA(cards)) {
                result.Type = KA;
                mp[result].insert(person);
            }
            if (size == 5 && isKA(cards)) {
                result.Type = KA;
                mp[result].insert(person);
            }
        }
    };
    while (cin >> n) {
        vector<Card> c(5);
        for (int i = 0; i < 5; i += 1) {
            string s;
            cin >> s;
            c[i] = toCard(s);
        }
        map<Comb, set<int>> mp;
        for (int i = 1; i <= n; i += 1) {
            string s1, s2;
            cin >> s1 >> s2;
            c.push_back(toCard(s1));
            c.push_back(toCard(s2));
            for (int mask = 0; mask < (1 << 7); mask += 1) {
                if (__builtin_popcount(mask) == 5) {
                    vector<Card> cards;
                    for (int bt = 0; bt < 7; bt += 1) {
                        if ((1<<bt)&mask) {
                            cards.push_back(c[bt]);
                        }
                    }
                    getCombs(cards, mp, i);
                }
            }
            c.pop_back();
            c.pop_back();
        }
        assert(!mp.empty());
        for (const auto &x : mp.rbegin()->second) {
            cout << x << " ";
        }
        cout << "\n";
    }
}