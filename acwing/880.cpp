// Problem: 线性同余方程
// URL: https://www.acwing.com/problem/content/880/

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
#define int long long
using namespace std;
using ll = long long;
using ull = unsigned long long;
using PII = pair<int, int>;

int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }

int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, x, y);
    int t = y;
    y = x - (a / b) * t;
    x = t;
    return d;
}

void solve() {
    int a, b, m;
    cin >> a >> b >> m;
    int t = gcd(a, m);
    if (b % t != 0) {
        cout << "impossible" << endl;
        return;
    }
    int aa = a * b / t;
    int mm = m * b / t;
    int x, y;
    exgcd(aa, mm, x, y);
    cout << x * b / t % m << endl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    // ax=b(mod m)
    // ax+my=b
    int n;
    cin >> n;
    while (n--) {
        solve();
    }
    // ================================================
    return 0;
}
