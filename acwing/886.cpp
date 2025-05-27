// Problem: 高斯消元解异或线性方程组
// URL: https://www.acwing.com/problem/content/886/

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

const int N = 105;

int n;
int a[N][N];

int gauss() {
    // 0 no solution
    // 1 one solution
    // 2 inf solution
    int c, r;
    for (c = 1, r = 1; c <= n; c++) {
        int t = -1;
        rep(i, r, n) if (a[i][c]) {
            t = i;
            break;
        }
        if (t == -1)
            continue;
        rep(i, 1, n + 1) swap(a[r][i], a[t][i]);
        rep(i, r + 1, n) if (a[i][c]) per(j, n + 1, c) a[i][j] ^= a[r][j];

        r++;
    }
    if (r <= n) {
        rep(i, r, n) if (a[i][n + 1]) return 0;
        return 2;
    }
    per(i, n, 1) rep(j, i + 1, n + 1) if (a[i][j]) a[i][n + 1] ^= a[j][n + 1];
    return 1;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    cin >> n;
    rep(i, 1, n) rep(j, 1, n + 1) cin >> a[i][j];
    int t = gauss();
    if (t == 0)
        cout << "No solution";
    else if (t == 2)
        cout << "Multiple sets of solutions";
    else
        rep(i, 1, n) cout << a[i][n + 1] << endl;
    // ================================================
    return 0;
}
