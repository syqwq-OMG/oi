// Problem: B. Outstanding Impressionist
// URL: https://codeforces.com/contest/2053/problem/B

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

const int N = 2e5 + 5;

int n;
int l[N], r[N];
int cnt[N << 1];
int st[N << 1];
int sum[N << 1];

void solve() {
    rep(i, 1, n * 2) cnt[i] = 0, sum[i] = 0, st[i] = 0;
    cin >> n;
    rep(i, 1, n) {
        cin >> l[i] >> r[i];
        // a.push_back({l, r});
        if (l[i] == r[i])
            cnt[l[i]]++, st[l[i]] = 1;
    }
    rep(i, 1, n * 2) sum[i] = sum[i - 1] + st[i];
    rep(i, 1, n) {
        if (l[i] == r[i]) {
            if (cnt[l[i]] >= 2)
                cout << 0;
            else
                cout << 1;
        } else {
            if (sum[r[i]] - sum[l[i] - 1] == r[i] - l[i] + 1)
                cout << 0;
            else
                cout << 1;
        }
    }
    cout << endl;
}

signed main() {
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
