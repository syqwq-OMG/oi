// Problem: A. Square Year
// URL: https://codeforces.com/contest/2114/problem/0

#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
using ll = long long;
using ull = unsigned long long;
using PII = pair<int, int>;
template <class T> bool chmin(T &a, const T &b) {
    if (a > b) {
        a = b;
        return 1;
    } else
        return 0;
}
template <class T> bool chmax(T &a, const T &b) {
    if (a < b) {
        a = b;
        return 1;
    } else
        return 0;
}
// ===========================================================

void solve() {
    string s;
    cin >> s;
    int a = stoi(s);
    int b = sqrt(a);
    if (b * b != a)
        cout << -1 << endl;
    else
        cout << 0 << " " << b << endl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    int t;
    cin >> t;
    while (t--)
        solve();
    // ================================================
    return 0;
}
