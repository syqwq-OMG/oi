// Problem: D. Quartet Swapping
// URL: https://codeforces.com/contest/2102/problem/D

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

const int N = 1e5 + 5;

int n;
int odd[N], even[N];
int ans[N << 1];

int mgsort(int q[], int l, int r) {
    if (l >= r)
        return 0;
    int mid = (l + r) >> 1;
    int ret = (mgsort(q, l, mid) + mgsort(q, mid + 1, r)) & 1;
    int cnt = 0, tmp[N];
    int i = l, j = mid + 1;
    while (i <= mid && j <= r)
        if (q[i] <= q[j])
            tmp[++cnt] = q[i++];
        else
            tmp[++cnt] = q[j++], ret += mid - i + 1;
    while (i <= mid)
        tmp[++cnt] = q[i++];
    while (j <= r)
        tmp[++cnt] = q[j++];
    for (i = 1, j = l; j <= r; i++, j++)
        q[j] = tmp[i];

    return ret & 1;
}

void solve() {
    cin >> n;
    rep(i, 1, n) {
        int t;
        cin >> t;
        if (i & 1)
            odd[(i >> 1) + 1] = t;
        else
            even[i >> 1] = t;
    }

    int iv1 = mgsort(odd, 1, (n + 1) >> 1);
    int iv2 = mgsort(even, 1, n >> 1);

    rep(i, 1, n) {
        if (i & 1)
            ans[i] = odd[(i >> 1) + 1];
        else
            ans[i] = even[i >> 1];
    }

    if (iv1 != iv2)
        swap(ans[n], ans[n - 2]);

    rep(i, 1, n) cout << ans[i] << " ";
    cout << endl;
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
