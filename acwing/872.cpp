// Problem: 约数个数
// URL: https://www.acwing.com/problem/content/872/

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

const int mod = 1e9 + 7;

int n;
unordered_map<int, int> d;

void count(int x) {
    for (int i = 2; i <= x / i; i++) {
        if (x % i != 0)
            continue;
        while (x % i == 0)
            x /= i, d[i]++;
    }
    if (x > 1)
        d[x]++;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    cin >> n;
    rep(i, 1, n) {
        int t;
        cin >> t;
        count(t);
    }

    ll ans = 1;
    for (auto [a, c] : d) {
        ans = (ll)(ans * (c + 1)) % mod;
    }
    cout << ans;
    // ================================================
    return 0;
}
