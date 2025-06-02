// Problem: 台阶-Nim游戏
// URL: https://www.acwing.com/problem/content/894/

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
#define rep(i, a, b) for (int i = a; i < b; i++)
#define repp(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i > b; i--)
#define perr(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
using ll = long long;
using ull = unsigned long long;
using PII = pair<int, int>;
template <class T, class S>
inline bool chmax(T &a, const S &b) {
    return (a < b ? a = b, 1 : 0);
}
template <class T, class S>
inline bool chmin(T &a, const S &b) {
    return (a > b ? a = b, 1 : 0);
}
void YES(bool t = 1) { cout << (t ? "YES" : "NO") << endl; }
void NO(bool t = 1) { YES(!t); }
void Yes(bool t = 1) { cout << (t ? "Yes" : "No") << endl; }
void No(bool t = 1) { Yes(!t); }
void yes(bool t = 1) { cout << (t ? "yes" : "no") << endl; }
void no(bool t = 1) { yes(!t); }
// ===========================================================
// ===========================================================

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    int n;
    cin >> n;
    int res = 0;
    repp(i, 1, n) {
        int t;
        cin >> t;
        if (i & 1) res ^= t;
    }
    if (res) Yes();
    else No();
    // ================================================
    return 0;
}
