// Problem: A. Tender Carpenter
// URL: https://codeforces.com/contest/2053/problem/A

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

const int N = 205;

int n;
int a[N];

void solve() {
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n - 1) {
        int mx = max(a[i + 1], a[i]);
        int mn = min(a[i + 1], a[i]);
        if (mx < mn * 2) {
            cout << "YES" << endl;
            return;
        }
    }
    cout << "NO" << endl;
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
