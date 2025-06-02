// Problem: 求组合数 I
// URL: https://www.acwing.com/problem/content/887/

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

const int p = 1e9 + 7;
const int N = 2005;

ll c[N][N];

ll add(ll a, ll b) { return (a + b) % p; }

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    // c[i][0]=1;
    // c[i][j]=c[i-1][j]+c[i-1][j-1];
    rep(i, 0, 2000) {
        rep(j, 0, i) {
            if (!j)
                c[i][j] = 1;
            else
                c[i][j] = add(c[i - 1][j], c[i - 1][j - 1]);
        }
    }
    int n;
    cin >> n;
    while (n--) {
        int a, b;
        cin >> a >> b;
        cout << c[a][b] << endl;
    }
    // ================================================
    return 0;
}
