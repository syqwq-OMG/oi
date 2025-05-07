// Problem: Kruskal算法求最小生成树
// URL: https://www.acwing.com/problem/content/861/

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

struct Edge {
    int u, v, w;
    Edge() {}
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
    bool operator<(Edge e) const { return w < e.w; }
};

const int N = 1e5 + 5;
const int inf = 0x7fffffff;

int n, m;
Edge e[N << 1];
int fa[N];

int get(int x) {
    if (fa[x] == x)
        return x;
    return fa[x] = get(fa[x]);
}

void merge(int x, int y) { fa[get(x)] = get(y); }

int kruskal() {
    int cnt = 0;
    int ret = 0;
    sort(e + 1, e + 1 + m);
    rep(i, 1, m) {
        int fv = get(e[i].v), fu = get(e[i].u);
        int w = e[i].w;
        if (fv == fu)
            continue;
        merge(fu, fv);
        ret += w;
        cnt++;
    }
    if (cnt == n - 1)
        return ret;
    return inf;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    cin >> n >> m;
    rep(i, 1, n) fa[i] = i;
    rep(i, 1, m) { cin >> e[i].u >> e[i].v >> e[i].w; }

    int t = kruskal();
    if (t == inf)
        cout << "impossible";
    else
        cout << t;

    // ================================================
    return 0;
}
