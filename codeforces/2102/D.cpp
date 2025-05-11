// Problem: D. Quartet Swapping
// URL: https://codeforces.com/contest/2102/problem/D

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

const int N = 2e5 + 5;

int n;
int a[N];
int pos[N];
int ans[N];

void solve() {
    memset(ans, 0, sizeof ans);
    cin >> n;
    rep(i, 1, n) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    int op = 1, ep = 2;
    rep(i, 1, n - 4) {
        if (pos[i] % 2 == 1)
            ans[op] = i, op += 2;
        else
            ans[ep] = i, ep += 2;
    }
    int tmp[5];

    rep(i, 1, 4) ans[n - 4 + i] = tmp[i];

    rep(i, 1, n) cout << ans[i] << " ";
    cout << endl;
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
