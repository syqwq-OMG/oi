// Problem: C. Trip to the Olympiad
// URL: https://codeforces.com/contest/2057/problem/C

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

void solve() {
    auto f = [=](int x, int b) -> int { return x & (1 << b); };

    int l, r;
    cin >> l >> r;
    int res = 0;

    int i = 30;
    while (f(l, i) == f(r, i))
        res |= f(l, i), i--;

    int t = -1; // first same bit
    per(j, i, 0) if (f(l, j) == f(r, j)) {
        t = j;
        break;
    }
    if (t == -1)
        res = l + 1;
    else {
        if (f(l, t) == 0) {
            res |= (1 << t);
            rep(j, t + 1, i) res |= f(l, j);
        } else {
            rep(j, t + 1, i) res |= f(r, j);
        }
        per(j, t - 1, 0) {
            if (f(l, j) == f(r, j) && f(l, j) == 0)
                res |= (1 << j);
        }
    }
    cout << l << " " << r << " " << res << endl;
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
