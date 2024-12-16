#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Функция кодирования данных с использованием кода Хэмминга
vector<int> hammingEncode(const vector<int>& data) {
    int m = data.size(); // Количество бит данных
    int r = 0; // Количество контрольных бит

    // Вычисляем количество контрольных бит
    while (pow(2, r) < (m + r + 1)) {
        r++;
    }

    int totalBits = m + r; // Общее количество бит (данные + контрольные биты)
    vector<int> encoded(totalBits, 0);

    // Распределяем данные по позициям (пропускаем позиции для контрольных бит)
    int j = 0;
    for (int i = 1; i <= totalBits; ++i) {
        if ((i & (i - 1)) == 0) {
            // Позиция степени двойки (контрольный бит)
            continue;
        }
        encoded[i - 1] = data[j++];
    }

    // Устанавливаем значения контрольных бит
    for (int i = 0; i < r; ++i) {
        int position = pow(2, i);
        int parity = 0;
        for (int j = 1; j <= totalBits; ++j) {
            if (j & position) {
                parity ^= encoded[j - 1];
            }
        }
        encoded[position - 1] = parity;
    }

    return encoded;
}

// Функция декодирования и проверки ошибок
vector<int> hammingDecode(vector<int>& received) {
    int totalBits = received.size();
    int r = 0;

    // Вычисляем количество контрольных бит
    while (pow(2, r) < (totalBits + 1)) {
        r++;
    }

    // Проверяем контрольные биты на ошибки
    int errorPosition = 0;
    for (int i = 0; i < r; ++i) {
        int position = pow(2, i);
        int parity = 0;
        for (int j = 1; j <= totalBits; ++j) {
            if (j & position) {
                parity ^= received[j - 1];
            }
        }
        if (parity != 0) {
            errorPosition += position;
        }
    }

    // Исправляем ошибку, если обнаружена
    if (errorPosition > 0) {
        cout << "Ошибка обнаружена в позиции " << errorPosition << ". Исправляем...\n";
        received[errorPosition - 1] ^= 1;
    } else {
        cout << "Ошибок не обнаружено.\n";
    }

    // Извлекаем данные, исключая контрольные биты
    vector<int> data;
    for (int i = 1; i <= totalBits; ++i) {
        if ((i & (i - 1)) != 0) {
            data.push_back(received[i - 1]);
        }
    }

    return data;
}

// Главная функция
int main() {
    // Пример данных для кодирования
    vector<int> data = {1, 0, 1, 1};
    cout << "Исходные данные: ";
    for (int bit : data) cout << bit;
    cout << endl;

    // Кодирование
    vector<int> encoded = hammingEncode(data);
    cout << "Закодированные данные: ";
    for (int bit : encoded) cout << bit;
    cout << endl;

    // Добавляем ошибку для проверки декодирования
    encoded[6] ^= 1; // Инвертируем один бит (вносим ошибку)
    cout << "Принятые данные (с ошибкой): ";
    for (int bit : encoded) cout << bit;
    cout << endl;

    // Декодирование
    vector<int> decoded = hammingDecode(encoded);
    cout << "Декодированные данные: ";
    for (int bit : decoded) cout << bit;
    cout << endl;

    return 0;
}
