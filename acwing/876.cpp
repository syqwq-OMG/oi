// Problem: 筛法求欧拉函数
// URL: https://www.acwing.com/problem/content/876/

#include <algorithm>
#include <array>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <unordered_map>
#include <vector>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
using ll = long long;
using ull = unsigned long long;
using PII = pair<int, int>;

const int N = 1e6 + 5;

int n;
vector<int> primes;
bitset<N> st;
ll phi[N];

void eular() {
    phi[1] = 1;
    rep(i, 2, n) {
        if (!st[i]) {
            phi[i] = i - 1;
            primes.push_back(i);
        }
        for (int x : primes) {
            if (x > n / i)
                break;
            phi[x * i] = phi[i] * (x - 1);
            st[x * i] = 1;
            if (i % x == 0) {
                phi[x * i] = phi[i] * x;
                break;
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    cin >> n;
    eular();
    cout << accumulate(phi + 1, phi + 1 + n, 0ll);
    // ================================================
    return 0;
}
