// Problem: 求组合数 III
// URL: https://www.acwing.com/problem/content/889/

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

ull qpow(ull a, ull b, ull p) {
    ull res = 1;
    for (ull t = a; b; b >>= 1, t = t * t % p)
        if (b & 1)
            res = res * t % p;
    return res;
}

ull C(ull a, ull b, ull p) {
    ull res = 1;
    for (ull i = a, j = b; j >= 1; i--, j--) {
        res = res * i % p;
        res = res * qpow(j, p - 2, p) % p;
    }
    return res;
}

ull lucas(ull a, ull b, ull p) {
    if (a < p && b < p)
        return C(a, b, p);
    else
        return C(a % p, b % p, p) * lucas(a / p, b / p, p) % p;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    int n;
    cin >> n;
    while (n--) {
        ull a, b, p;
        cin >> a >> b >> p;
        cout << lucas(a, b, p) << endl;
    }
    // ================================================
    return 0;
}
