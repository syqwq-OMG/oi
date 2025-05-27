// Problem: 能被整除的数
// URL: https://www.acwing.com/problem/content/892/

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

const int N = 20;

int n, m;
int p[N];
ll ans = 0;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    cin >> n >> m;
    rep(i, 0, m - 1) cin >> p[i];

    rep(i, 1, (1 << m) - 1) {
        ll t = 1;
        int s = 0;
        rep(j, 0, m - 1) {
            if (i >> j & 1) {
                t *= p[j];
                if (t > n) {
                    t = -1;
                    break;
                }
                s++;
            }
        }
        if (t == -1)
            continue;
        if (s & 1)
            ans += n / t;
        else
            ans -= n / t;
    }

    cout << ans;
    // ================================================
    return 0;
}
