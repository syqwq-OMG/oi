// Problem: 试除法判定质数
// URL: https://www.acwing.com/problem/content/868/

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

bool check(int x) {
    for (int i = 2; i <= x / i; i++)
        if (x % i == 0)
            return 0;
    return 1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    int n;
    cin >> n;
    rep(i, 1, n) {
        int t;
        cin >> t;
        if (t == 1 || !check(t))
            cout << "No\n";
        else
            cout << "Yes\n";
    }
    // ================================================
    return 0;
}
