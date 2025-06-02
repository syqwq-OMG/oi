// Problem: B. Gorilla and the Exam
// URL: https://codeforces.com/contest/2057/problem/B

#include <algorithm>
#include <array>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
using ll = long long;
using ull = unsigned long long;
using PII = pair<int, int>;

unordered_map<int, int> cnt;
vector<int> a;

void solve() {
    cnt.clear();
    a.clear();
    int n, k;
    cnt.reserve(4 * n);
    cin >> n >> k;
    rep(i, 1, n) {
        int t;
        cin >> t;
        cnt[t]++;
    }

    if (n <= k) {
        cout << 1 << endl;
        return;
    }

    for (auto [k, v] : cnt)
        a.push_back(v);
    sort(a.begin(), a.end());
    int t = 0;
    for (auto x : a) {
        if (k >= x)
            k -= x, t++;
        else
            break;
    }
    cout << a.size() - t << endl;
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
