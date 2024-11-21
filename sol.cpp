#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Field {
    long long x, y;
};

// Сравнение для сортировки: сначала по x по убыванию, затем по y по убыванию
bool compareFields(const Field& a, const Field& b) {
    if (a.x == b.x) return a.y > b.y;
    return a.x > b.x;
}

int main() {
    long long n, k;
    cin >> n >> k;

    vector<Field> fields(n);

    // Считываем поля
    for (long long i = 0; i < n; ++i) {
        cin >> fields[i].x >> fields[i].y;
    }

    // Сортируем поля по убыванию x и y
    sort(fields.begin(), fields.end(), compareFields);

    // Приоритетная очередь для хранения минимальных значений y
    priority_queue<long long, vector<long long>, greater<long long>> minHeap;

    // Инициализируем кучу первыми k полями
    for (long long i = 0; i < k; ++i) {
        minHeap.push(fields[i].y);
    }

    // Ответ на основе первых k полей
    long long answer = fields[k - 1].x * minHeap.top();

    // Проходим по оставшимся полям
    for (long long i = k; i < n; ++i) {
        // Если текущее поле имеет большую высоту, чем минимальная в куче, обновляем кучу
        if (fields[i].y > minHeap.top()) {
            minHeap.pop();  // Убираем минимальный элемент
            minHeap.push(fields[i].y);  // Добавляем новый элемент
        }

        // Обновляем ответ
        answer = max(answer, fields[i].x * minHeap.top());
    }

    // Выводим результат
    cout << answer << endl;

    return 0;
}
