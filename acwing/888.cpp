// Problem: 求组合数 II
// URL: https://www.acwing.com/problem/content/888/

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
#define ll long long
#define int long long
using ull = unsigned long long;
using PII = pair<int, int>;

const int p = 1e9 + 7;
const int N = 1e5 + 5;

int fac[N];
int inv[N];

ll qpow(int a, int b) {
    ll res = 1;
    for (ll t = a; b; b >>= 1, t = (t * t) % p)
        if (b & 1)
            res = res * t % p;
    return res % p;
}

void prework() {
    inv[0] = fac[0] = 1;
    rep(i, 1, 1e5) {
        fac[i] = fac[i - 1] * i % p;
        inv[i] = inv[i - 1] * qpow(i, p - 2) % p;
    }
}

int mod(int x) { return (x % p + p) % p; }

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    prework();
    int n;
    cin >> n;
    while (n--) {
        int a, b;
        cin >> a >> b;
        cout << mod(fac[a] * inv[b] % p * inv[a - b]) << endl;
    }
    // ================================================
    return 0;
}
