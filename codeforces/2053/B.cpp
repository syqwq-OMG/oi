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
vector<PII> a;
unordered_map<int, int> cnt;

void solve() {
    a.clear();
    cnt.clear();
    cnt.reserve(n << 3);

    cin >> n;
    rep(i, 1, n) {
        int l, r;
        cin >> l >> r;
        a.push_back({l, r});
        if (r == l)
            cnt[r]++;
    }
    for (auto [l, r] : a) {
        if (l == r) {
            if (cnt[l] < 2)
                cout << 1;
            else
                cout << 0;
        } else {
            int i = l;
            bool flg = 1;
            while (i <= r) {
                if (cnt.count(i) == 0) {
                    flg = 0;
                    break;
                }
                i++;
            }
            if (flg)
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
