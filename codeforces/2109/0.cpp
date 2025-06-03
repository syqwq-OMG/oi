// Problem: A. It's Time To Duel
// URL: https://codeforces.com/contest/2109/problem/0

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

const int N = 110;
int n;
int a[N];
void solve() {
    bool flg = 1;

    cin >> n;
    rep(i, 1, n) {
        cin >> a[i];
        if (a[i] == 0)
            flg = 0;
    }
    rep(i, 1, n - 1) if (a[i] == 0 && a[i + 1] == 0) {
        cout << "YES" << endl;
        return;
    }
    if (flg)
        cout << "YES" << endl;
    else
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
