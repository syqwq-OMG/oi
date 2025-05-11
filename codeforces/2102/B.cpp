// Problem: B. The Picky Cat
// URL: https://codeforces.com/contest/2102/problem/B

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

const int N = 1e5 + 5;

int n;
int a[N];

void solve() {
    cin >> n;
    int cnt = 0;
    cin >> a[1];
    rep(i, 2, n) {
        cin >> a[i];
        cnt += abs(a[i]) > abs(a[1]);
    }
    if (n == 1 || n == 2) {
        cout << "YES" << endl;
        return;
    }
    if (n % 2 == 0) {
        if (cnt < n / 2 - 1)
            cout << "NO" << endl;
        else
            cout << "YES" << endl;
    } else {
        if (cnt < n / 2)
            cout << "NO" << endl;
        else
            cout << "YES" << endl;
    }
}

int main() {
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
