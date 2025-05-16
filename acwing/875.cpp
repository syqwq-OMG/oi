// Problem: 欧拉函数
// URL: https://www.acwing.com/problem/content/875/

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
    auto phi = [=](ll x) -> ll {
        ll res = x;
        for (ll i = 2; i <= x / i; i++) {
            if (x % i != 0)
                continue;
            res = res * (i - 1) / i;
            while (x % i == 0)
                x /= i;
        }
        if (x > 1)
            res = res * (x - 1) / x;

        return res;
    };
    ll x;
    cin >> x;
    cout << phi(x) << endl;
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
