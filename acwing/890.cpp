// Problem: 求组合数 IV
// URL: https://www.acwing.com/problem/content/890/

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

const int N = 5005;

vector<int> primes;
vector<int> cnt;
bitset<N> st;
vector<int> res;
int a, b;

void eular(int n) {
    for (int i = 2; i <= n; i++) {
        if (!st[i])
            primes.push_back(i);
        for (auto x : primes) {
            if (x > n / i)
                break;
            st[i * x] = 1;
            if (i % x == 0)
                break;
        }
    }
}

int get(int x, int p) {
    int res = 0;
    while (x)
        res += x / p, x /= p;
    return res;
}

vector<int> mul(vector<int> m, int n) {
    vector<int> ans;
    int h = 0;
    for (auto x : m) {
        int t = x * n + h;
        ans.push_back(t % 10);
        h = t / 10;
    }
    while (h)
        ans.push_back(h % 10), h /= 10;
    return ans;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    cin >> a >> b;
    eular(a);
    for (auto p : primes)
        cnt.push_back(get(a, p) - get(b, p) - get(a - b, p));

    res.push_back(1);
    for (int i = 0; i < primes.size(); i++) {
        for (int j = 0; j < cnt[i]; j++) {
            res = mul(res, primes[i]);
        }
    }

    for_each(res.rbegin(), res.rend(), [](int x) { cout << x; });
    // ================================================
    return 0;
}
