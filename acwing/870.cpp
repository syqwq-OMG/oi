// Problem: 筛质数
// URL: https://www.acwing.com/problem/content/870/

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
bitset<N> st;

void solve() {
    st.set();
    rep(i, 2, n) {
        if (!st[i])
            continue;
        st[i] = 1;
        primes.push_back(i);
        for (int j = i * 2; j <= n; j += i)
            st[j] = 0;
    }
}

void eular() {
    st.set();
    rep(i, 2, n) {
        if (st[i])
            primes.push_back(i);
        for (auto p : primes) {
            if (p > n / i)
                break;
            st[i * p] = 0;
            // should break here cuz we should not exclude p*p
            if (i % p == 0)
                break;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    cin >> n;
    // solve();
    eular();
    cout << primes.size();
    // ================================================
    return 0;
}
