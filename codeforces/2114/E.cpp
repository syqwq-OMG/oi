// Problem: E. Kirei Attacks the Estate
// URL: https://codeforces.com/contest/2114/problem/E

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
template <class T>
bool chmin(T &a, const T &b) {
    if (a > b) {
        a = b;
        return 1;
    } else
        return 0;
}
template <class T>
bool chmax(T &a, const T &b) {
    if (a < b) {
        a = b;
        return 1;
    } else
        return 0;
}
// ===========================================================

const int N = 2e5 + 5;

int n;
int a[N], p[N];
bitset<N> st;
vector<int> h[N];
int mn[N], mx[N];

void add(int u, int v) { h[u].push_back(v); }

void dfs(int t) {
    st[t] = 1;
    if (p[t]) {
        chmax(mx[t], mx[t] - mn[p[t]]);
        chmin(mn[t], mn[t] - mx[p[t]]);
    }
    for (auto x : h[t]) {
        if (st[x])
            continue;
        st[x] = 1, p[x] = t;
        dfs(x);
    }
}

void solve() {
    st &= 0;
    cin >> n;
    rep(i, 1, n) {
        cin >> a[i];
        h[i].clear();
        mx[i] = a[i];
        mn[i] = a[i];
    }
    rep(i, 1, n - 1) {
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    dfs(1);
    rep(i, 1, n) cout << mx[i] << " ";
    cout << endl;
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
