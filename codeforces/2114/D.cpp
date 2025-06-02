// Problem: D. Come a Little Closer
// URL: https://codeforces.com/contest/2114/problem/D

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
// using ll = long long;
#define int long long
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
const int inf = 0x7fffffff;

int n;
PII a[N];
int mnx[3], mxx[3], mny[3], mxy[3];

void solve() {
    mnx[0] = mny[0] = mxx[0] = mxy[0] = 0;
    mnx[1] = mnx[2] = mny[2] = mny[1] = inf;
    mxx[1] = mxx[2] = mxy[1] = mxy[2] = -inf;

    cin >> n;
    rep(i, 1, n) {
        int x, y;
        cin >> x >> y;
        a[i] = {x, y};
        if (x < mnx[1])
            mnx[2] = mnx[1], mnx[1] = x, mnx[0] = 1;
        else if (x == mnx[1])
            mnx[0]++;
        else if (x < mnx[2])
            mnx[2] = x;

        if (x > mxx[1])
            mxx[2] = mxx[1], mxx[1] = x, mxx[0] = 1;
        else if (x == mxx[1])
            mxx[0]++;
        else if (x > mxx[2])
            mxx[2] = x;

        if (y < mny[1])
            mny[2] = mny[1], mny[1] = y, mny[0] = 1;
        else if (y == mny[1])
            mny[0]++;
        else if (y < mny[2])
            mny[2] = y;

        if (y > mxy[1])
            mxy[2] = mxy[1], mxy[1] = y, mxy[0] = 1;
        else if (y == mxy[1])
            mxy[0]++;
        else if (y > mxy[2])
            mxy[2] = y;
    }
    if (n == 1) {
        cout << 1 << endl;
        return;
    }

    int ans = (mxx[1] - mnx[1] + 1) * (mxy[1] - mny[1] + 1);

    rep(i, 1, n) {
        int qwqx = mnx[1];
        if (a[i].first == mnx[1] && mnx[0] == 1)
            qwqx = mnx[2];
        int qwqy = mny[1];
        if (a[i].second == mny[1] && mny[0] == 1)
            qwqy = mny[2];
        int awax = mxx[1];
        if (a[i].first == mxx[1] && mxx[0] == 1)
            awax = mxx[2];
        int away = mxy[1];
        if (a[i].second == mxy[1] && mxy[0] == 1)
            away = mxy[2];
        int wwwx = awax - qwqx + 1;
        int wwwy = away - qwqy + 1;
        int www = wwwx * wwwy;

        if (www > n - 1) {
            chmin(ans, www);
        } else {
            chmin(ans, wwwx * (wwwy + 1));
            chmin(ans, (wwwx + 1) * wwwy);
        }
    }
    cout << ans << endl;
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
