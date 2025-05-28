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
#define rep(i, a, b) for (int i = a; i < b; i++)
#define repp(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = (a) - 1; i >= b; i--)
#define perr(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> PII;
typedef vector<int> vi;
typedef vector<PII> vpii;
template <class T>
using vc = vector<T>;
template <class T>
using vvc = vc<vc<T>>;
template <class T, class S>
inline bool chmax(T &a, const S &b) {
    return (a < b ? a = b, 1 : 0);
}
template <class T, class S>
inline bool chmin(T &a, const S &b) {
    return (a > b ? a = b, 1 : 0);
}
void YES(bool t = 1) { cout << (t ? "YES" : "NO") << endl; }
void NO(bool t = 1) { YES(!t); }
void Yes(bool t = 1) { cout << (t ? "Yes" : "No") << endl; }
void No(bool t = 1) { Yes(!t); }
void yes(bool t = 1) { cout << (t ? "yes" : "no") << endl; }
void no(bool t = 1) { yes(!t); }
// ===========================================================
// Problem: B. Team Training
// URL: https://codeforces.com/contest/2091/problem/B
// ===========================================================

const int N = 2e5 + 5;

int x;
int n;
int a[N];

void solve() {
    cin >> n >> x;
    repp(i, 1, n) cin >> a[i];
    sort(a + 1, a + 1 + n);
    int ans = 0;

    int t = 0;
    perr(i, n, 1) {
        t++;
        if (a[i] * t >= x) t = 0, ans++;
    }

    cout << ans << endl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    int T;
    cin >> T;
    while (T--) solve();
    // ================================================
    return 0;
}
