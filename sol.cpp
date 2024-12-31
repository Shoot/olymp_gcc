#include <bits/stdc++.h>
using namespace std;
double distanceToSegment(double x, double y, double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double px = x - x1;
    double py = y - y1;
    double dotProduct = px * dx + py * dy;
    if (dotProduct < 0) {
        // Ближайшая точка - начало отрезка
        return sqrt(px * px + py * py);
    }
    double sqrLength = dx * dx + dy * dy;
    if (dotProduct > sqrLength) {
        // Ближайшая точка - начало отрезка
        double ex = x - x2;
        double ey = y - y2;
        return sqrt(ex * ex + ey * ey);
    }
    double t = dotProduct / sqrLength;
    double closestX = x1 + t * dx;
    double closestY = y1 + t * dy;
    return sqrt((x - closestX) * (x - closestX) + (y - closestY) * (y - closestY));
}

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> points;
    int left = 1e9;
    int right = -1e9;
    for (int i = 0; i < n; i += 1) {
        int x, y;
        cin >> x >> y;
        left = min(left, x);
        right = max(right, x);
        points.push_back({x, y});
    }
    struct line {
        double k;
        double b;
        double operator()(double x) {
            return k * x + b;
        }
    };
    struct segment {
        int x1;
        int y1;
        int x2;
        int y2;
    };
    vector<segment> polygon;
    vector<line> lines;
    for (int i = 0; i < n; i += 1) {
        polygon.push_back({points[i].first, points[i].second, points[(i+1)%n].first, points[(i+1)%n].second});
        int dx = points[(i+1)%n].first - points[i].first;
        int dy = points[(i+1)%n].second - points[i].second;
        double k = double(dy) / dx;
        double b = double(points[i].second) - k * points[i].first;
        lines.push_back({k, b});
    }
    auto dist = [&] (segment s, double x, double y) -> double {
        return distanceToSegment(x, y, s.x1, s.y1, s.x2, s.y2);
    };
    auto g = [&] (double x, double y) -> double {
        double mini = 1e9;
        for (int i = 0; i < n; i += 1) {
            mini = min(mini, dist(polygon[i], x, y));
        }
        return mini;
    };
    auto f = [&] (double x) -> double {
        double res = 1e9;
        double l = 1e9;
        double r = -1e9;
        for (int i = 0; i < n; i += 1) {
            auto one = points[i];
            auto another = points[(i+1)%n];
            if (one.first > another.first) {
                swap(one, another);
            }
            if (one.first - 1e-7 < x && another.first + 1e-7 > x) {
                l = min(l, lines[i](x));
                r = max(r, lines[i](x));
            }
        }
        while (r-l > 1e-5) {
            double y1 = l + (r - l) / 3;
            double y2 = r - (r - l) / 3;
            double gy1 = g(x, y1);
            double gy2 = g(x, y2);
            if (gy1 < gy2) {
                l = y1;
            } else {
                r = y2;
                res = gy2;
            }
        }
        return res;
    };
    double l = left;
    double r = right;
    double res = 1e9;
    while (r-l > 1e-5) {
        double x1 = l + (r - l) / 3;
        double x2 = r - (r - l) / 3;
        double fx1 = f(x1);
        double fx2 = f(x2);
        if (fx1 < fx2) {
            l = x1;
        } else {
            r = x2;
            res = fx2;
        }
    }
    cout << fixed << setprecision(3);
    cout << res << endl;
    return 0;
}