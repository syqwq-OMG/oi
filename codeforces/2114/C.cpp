// Problem: C. Need More Arrays
// URL: https://codeforces.com/contest/2114/problem/C

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
template <class T> bool chmin(T &a, const T &b) {
    if (a > b) {
        a = b;
        return 1;
    } else
        return 0;
}
template <class T> bool chmax(T &a, const T &b) {
    if (a < b) {
        a = b;
        return 1;
    } else
        return 0;
}
// ===========================================================
const int N = 2e5 + 5;

int n;
int a[N];
int cnt = 0;
int s[N];

void solve() {
    cnt = 0;
    s[0] = -8;
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n) {
        if (a[i] > s[cnt] + 1)
            s[++cnt] = a[i];
    }
    cout << cnt << endl;
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
