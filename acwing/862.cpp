// Problem: 染色法判定二分图
// URL: https://www.acwing.com/problem/content/862/

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

const int N = 1e5 + 5;

int n, m;
vector<int> h[N];
int col[N];

void add(int u, int v) { h[u].pb(v); }

bool dfs(int p, int c) {
    if (col[p] != -1)
        return col[p] == c;
    col[p] = c;
    for (auto x : h[p]) {
        if (!dfs(x, !c))
            return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    memset(col, 0xff, sizeof col);
    cin >> n >> m;
    rep(i, 1, m) {
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    bool t = 1;
    rep(i, 1, n) {
        if (col[i] == -1)
            if (!dfs(i, 0)) {
                t = 0;
                break;
            }
    }
    if (t)
        cout << "Yes";
    else
        cout << "No";
    // ================================================
    return 0;
}
