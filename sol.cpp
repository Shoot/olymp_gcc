#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    int N = 1 << n; // Размер массива F (2^n)

    vector<int> F(N), P(N);

    for (int i = 0; i < N; i++) {
        cin >> F[i];
        P[i] = F[i]; // Начнем с того, что P = F
    }

    // Прямое преобразование Мёбиуса
    for (int bit = 0; bit < n; bit++) {
        for (int i = 0; i < N; i++) {
            if (i & (1 << bit)) {
                P[i] += P[i ^ (1 << bit)];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        cout << P[i] << " ";
    }
    cout << endl;

    return 0;
}
