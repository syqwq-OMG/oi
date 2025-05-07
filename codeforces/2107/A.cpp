// Problem: A. LRC and VIP
// URL: https://codeforces.com/contest/2107/problem/A

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
using namespace std;
using ll = long long;
using ull = unsigned long long;
using PII = pair<int, int>;

const int N = 105;
const int inf = 0x7fffffff;

int n;
int a[N];

void solve() {
    cin >> n;
    rep(i, 1, n) cin >> a[i];

    int mn = inf, mx = -1;
    rep(i, 1, n) mn = min(mn, a[i]), mx = max(mx, a[i]);

    if (mn == mx) {
        cout << "No" << endl;
        return;
    } else {
        cout << "Yes" << endl;
        rep(i, 1, n) cout << (a[i] == mx ? 2 : 1) << " ";
        cout << endl;
    }
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
