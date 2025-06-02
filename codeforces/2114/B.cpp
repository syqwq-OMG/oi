// Problem: B. Not Quite a Palindromic String
// URL: https://codeforces.com/contest/2114/problem/B

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
//
void solve() {
    int n, k;
    string s;
    cin >> n >> k >> s;
    int cnt1 = 0;
    for (char ch : s)
        if (ch == '1')
            cnt1++;
    int cnt0 = n - cnt1;
    int p = n / 2;
    int dp = p - k;
    if (cnt0 < dp || cnt1 < dp) {
        cout << "NO" << endl;
        return;
    }
    cnt0 -= dp, cnt1 -= dp;
    if (cnt0 / 2 + cnt1 / 2 == k)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
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
