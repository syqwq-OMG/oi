// Problem: 最大公约数
// URL: https://www.acwing.com/problem/content/874/

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

int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    int n;
    cin >> n;
    while (n--) {
        int x, y;
        cin >> x >> y;
        cout << gcd(x, y) << endl;
    }
    // ================================================
    return 0;
}
