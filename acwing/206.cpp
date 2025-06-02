// Problem: 表达整数的奇怪方式
// URL: https://www.acwing.com/problem/content/206/

#include <algorithm>
#include <array>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <locale>
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

int n;
ll m1, a1;

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

ll mod(ll a, ll b) { return ((a % b) + b) % b; }

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    cin >> n;
    cin >> a1 >> m1;
    ll x = 0;
    rep(i, 1, n - 1) {
        ll m2, a2;
        cin >> a2 >> m2;
        ll k1, k2;
        ll d = exgcd(a1, a2, k1, k2);
        if ((m2 - m1) % d != 0) {
            cout << -1;
            return 0;
        }
        k1 *= (m2 - m1) / d;
        ll t = a2 / d;
        k1 = mod(k1, t); // find min k1
        x = k1 * a1 + m1;
        m1 = k1 * a1 + m1;
        a1 = abs(a1 / d * a2);
    }
    x = (m1 % a1 + a1) % a1;
    cout << x;

    // ================================================
    return 0;
}
