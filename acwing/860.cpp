// Problem: Prim算法求最小生成树
// URL: https://www.acwing.com/problem/content/860/

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

const int N = 510;
const int inf = 0x3f3f3f3f;

int n, m;
int g[N][N];
int dis[N]; // the distance between vertex and S
bool st[N];

int prim() {
    memset(dis, 0x3f, sizeof dis);
    int res = 0;

    rep(i, 0, n - 1) {
        int t = -1;
        rep(j, 1, n) if (!st[j] && (t == -1 || dis[j] < dis[t])) t = j;

        // if this is not the first node, and cannot find a proper node, then
        // return inf
        if (i && dis[t] == inf)
            return inf;
        if (i)
            res += dis[t];
        st[t] = 1;
        rep(j, 1, n) dis[j] = min(dis[j], g[t][j]);
    }

    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    cin >> n >> m;

    memset(g, 0x3f, sizeof g);
    rep(i, 1, n) g[i][i] = 0;

    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u][v] = g[v][u] = min(g[u][v], w);
    }

    int t = prim();
    if (t == inf)
        cout << "impossible";
    else
        cout << t;
    // ================================================
    return 0;
}
