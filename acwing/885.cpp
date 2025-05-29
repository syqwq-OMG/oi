// Problem: 高斯消元解线性方程组
// URL: https://www.acwing.com/problem/content/885/

#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <ios>
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
const double eps = 1e-8;

int n;
double a[N][N];

int gauss() {
    // 0 no solution
    // 1 one solution
    // 2 inf solution
    int c, r;
    for (c = 1, r = 1; c <= n; c++) {
        int t = r;
        rep(i, r, n) if (fabs(a[i][c]) > fabs(a[t][c])) t = i;

        if (fabs(a[t][c]) < eps)
            continue;

        rep(i, 1, n + 1) swap(a[t][i], a[r][i]);
        per(i, n + 1, c) a[r][i] /= a[r][c];
        rep(i, r + 1, n) {
            if (fabs(a[i][c]) > eps) {
                per(j, n + 1, c) { a[i][j] -= a[r][j] * a[i][c]; }
            }
        }
        r++;
    }
    if (r <= n) {
        rep(i, r, n) if (fabs(a[i][n + 1]) > eps) return 0;
        return 2;
    }
    per(i, n, 1) {
        per(j, i - 1, 1) { a[j][n + 1] -= a[i][n + 1] * a[j][i]; }
    }
    return 1;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    cin >> n;
    rep(i, 1, n) { rep(j, 1, n + 1) cin >> a[i][j]; }

    int t = gauss();
    if (t == 0)
        cout << "No solution";
    else if (t == 2)
        cout << "Infinite group solutions";
    else {
        rep(i, 1, n) cout << setprecision(2) << fixed << a[i][n + 1] << endl;
    }

    // ================================================
    return 0;
}
