#ifndef DEBUG_H
#define DEBUG_H

#include <bits/stdc++.h>
using namespace std;

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cerr << ' ' << H;
    debug_out(T...);
}

template <typename T>
ostream& operator<<(ostream &os, const vector<T> &v) {
    os << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) os << ", ";
        os << v[i];
    }
    return os << "]";
}

template <typename T1, typename T2>
ostream& operator<<(ostream &os, const pair<T1, T2> &p) {
    return os << "(" << p.first << ", " << p.second << ")";
}

template <typename T, size_t N>
ostream& operator<<(ostream &os, const array<T, N> &a) {
    os << "[";
    for (size_t i = 0; i < N; ++i) {
        if (i) os << ", ";
        os << a[i];
    }
    return os << "]";
}

template <typename T>
void debug_array(T* arr, size_t size) {
    cerr << "[";
    for (size_t i = 0; i < size; ++i) {
        if (i) cerr << ", ";
        cerr << arr[i];
    }
    cerr << "]";
}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#define debug_arr(arr, size) cerr << "[" << #arr << "]: ", debug_array(arr, size), cerr << endl

#endif // DEBUG_H
