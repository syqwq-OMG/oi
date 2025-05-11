// Problem: A. Dinner Time
// URL: https://codeforces.com/contest/2102/problem/0

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
    int n, m, p, q;
    cin >> n >> m >> p >> q;
    if (n % p == 0) {
        if (n * q / p == m)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;
}

int main() {
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
