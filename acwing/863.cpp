// Problem: 二分图的最大匹配
// URL: https://www.acwing.com/problem/content/863/

#include <algorithm>
#include <array>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <unordered_map>
#include <vector>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
using ll = long long;
using ull = unsigned long long;
using PII = pair<int, int>;

const int N = 505;
const int M = 1e5 + 5;

int n1, n2, m;
vector<int> h[N];
// ⚠️ Why match alone is not enough
// Imagine you are doing find(x) and you check a neighbor y. You then try
// find(match[y]) recursively. If you revisit y again during recursion (because
// of a cycle), without st[y] guarding it, you'd enter an infinite loop or
// duplicate work.
bitset<N> st;
int match[N];

bool find(int x) {
    for (auto y : h[x]) {
        if (st[y])
            continue;
        st[y] = 1;
        if (match[y] == 0 || find(match[y])) {
            match[y] = x;
            return 1;
        }
    }
    return 0;
}

void add(int u, int v) { h[u].push_back(v); }

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    cin >> n1 >> n2 >> m;
    rep(i, 1, m) {
        int u, v;
        cin >> u >> v;
        add(u, v);
    }

    int res = 0;
    rep(i, 1, n1) {
        st &= 0;
        if (find(i))
            res++;
    }
    cout << res;

    // ================================================
    return 0;
}
