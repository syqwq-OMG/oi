// Problem: C1. Hacking Numbers (Easy Version)
// URL: https://codeforces.com/contest/2109/problem/C1

#include <algorithm>
#include <array>
#include <bitset>
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

void solve() {
    int n;
    cin >> n;
    int x;
    cout << "digit" << endl;
    cin >> x;

    cout << "digit" << endl;
    cin >> x;

    cout << "add -8" << endl;
    cin >> x;
    cout << "add -4" << endl;
    cin >> x;
    cout << "add -2" << endl;
    cin >> x;
    cout << "add -1" << endl;
    cin >> x;
    cout << "add " << n - 1 << endl;
    cin >> x;

    cout << "!" << endl;
    cin >> x;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================

    int T;
    cin >> T;
    while (T--)
        solve();

    // ================================================
    return 0;
}
