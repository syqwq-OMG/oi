// Problem: 分解质因数
// URL: https://www.acwing.com/problem/content/869/

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

void divide(int x) {
    for (int i = 2; i <= x / i && x != 1; i++) {
        if (x % i != 0)
            continue;
        int t = 0;
        while (x % i == 0)
            t++, x /= i;
        cout << i << " " << t << endl;
    }
    if (x > 1)
        cout << x << " 1\n";
    cout << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    int n;
    cin >> n;
    rep(i, 1, n) {
        int x;
        cin >> x;
        divide(x);
    }
    // ================================================
    return 0;
}
