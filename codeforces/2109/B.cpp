#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
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
using namespace std;

const int inf = 0x7f7f7f7f;

int f(int x) {
    if (x == 1)
        return 0;
    return (int)ceil(log2(x));
}

void solve() {
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    if (n == 1 && m == 1) {
        cout << 0 << endl;
        return;
    }
    int a1 = min(a, n - a + 1);
    int b1 = min(b, m - b + 1);
    int ans = inf;
    if (n > 1)
        ans = min(ans, 1 + f(a1) + f(m));
    if (m > 1)
        ans = min(ans, 1 + f(b1) + f(n));

    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--)
        solve();

    return 0;
}
