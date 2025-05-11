// Problem: C. Mex in the Grid
// URL: https://codeforces.com/contest/2102/problem/C

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

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, -1, 0, 1};

int n;
int a[505][505];

bool check(int x, int y) { return 1 <= x && x <= n && y <= n && 1 <= y; }

void solve() {
    memset(a, 0, sizeof(a));
    cin >> n;

    int cnt = n * n;
    int cx = 1, cy = 1;
    a[cx][cy] = cnt--;
    int dir = 0;
    while (cnt > 0) {
        int nx = cx + dx[dir], ny = cy + dy[dir];
        while (check(nx, ny) && a[nx][ny] == 0) {
            a[nx][ny] = cnt--;
            cx = nx, cy = ny;
            nx = cx + dx[dir], ny = cy + dy[dir];
        }
        dir = (dir + 1) % 4;
    }

    rep(k, 1, n) {
        rep(j, 1, n) { cout << a[k][j] - 1 << " "; }
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
