// Problem: Floyd求最短路
// URL: https://www.acwing.com/problem/content/860/

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <ratio>
#include <unordered_map>
#include <vector>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
using namespace std;
using ll = long long;
using ull = unsigned long long;
using PII = pair<int, int>;

const int N = 210;
const int inf = 0x3f3f3f3f;

int n, m, k;
int dis[N][N];

void floyd() {
    rep(k, 1, n) {
        rep(i, 1, n) rep(j, 1, n) {
            dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    memset(dis, 0x3f, sizeof dis);
    cin >> n >> m >> k;
    rep(i, 1, n) dis[i][i] = 0;
    rep(i, 1, m) {
        int x, y, z;
        cin >> x >> y >> z;
        dis[x][y] = min(dis[x][y], z);
    }
    floyd();
    rep(i, 1, k) {
        int x, y;
        cin >> x >> y;
        if (dis[x][y] >= inf / 2)
            cout << "impossible" << endl;
        else
            cout << dis[x][y] << endl;
    }

    // ================================================
    return 0;
}
