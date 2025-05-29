// Problem: 筛法求欧拉函数
// URL: https://www.acwing.com/problem/content/876/

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

const int N = 1e6 + 5;

int n;
vector<int> primes;
ll phi[N];
bitset<N> st; // 0 -> isprime

void eular() {
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
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
        for (auto p : primes) {
            if (p > n / i)
                break;
            st[p * i] = 1;
            if (i % p == 0) {
                phi[i * p] = p * phi[i];
                break;
            }
            phi[i * p] = phi[i] * (p - 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    cin >> n;
    eular();

    ll res = 0;
    rep(i, 1, n) res += phi[i];
    cout << res;
    // ================================================
    return 0;
}
