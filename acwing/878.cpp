// Problem: 快速幂求逆元
// URL: https://www.acwing.com/problem/content/878/

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
    auto qpow = [=](ll a, ll b, ll p) -> ll {
        ll res = 1;
        for (ll t = a; b; b >>= 1, t = (t * t) % p)
            if (b & 1)
                res = (res * t) % p;
        return res % p;
    };

    ll a, p;
    cin >> a >> p;
    if (a % p == 0)
        cout << "impossible" << endl;
    else
        cout << qpow(a, p - 2, p) << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    int n;
    cin >> n;
    while (n--)
        solve();
    // ================================================
    return 0;
}
