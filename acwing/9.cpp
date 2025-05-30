#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;
// #define int long long
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> PII;
typedef vector<ll> vi;
typedef vector<PII> vpii;
template <class T>
using vc = vector<T>;
template <class T>
using vvc = vc<vc<T>>;
// https://trap.jp/post/1224/
#define rep1(a) for (ll _ = 0; _ < ll(a); _++)
#define rep2(i, a) for (ll i = 1; i <= ll(a); i++)
#define rep3(i, a, b) for (ll i = (a); i <= ll(b); i++)
#define rep4(i, a, b, d) for (ll i = (a); i <= ll(b); i += (d))
#define per2(i, a) for (ll i = (a); i >= 1; i--)
#define per3(i, a, b) for (ll i = (a); i >= ll(b); i--)
#define per4(i, a, b, d) for (ll i = (a); i >= ll(b); i -= (d))
#define overload4(a, b, c, d, e, ...) e
#define rep(...) overload4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)
#define per(...) overload4(__VA_ARGS__, per4, per3, per2)(__VA_ARGS__)
#define cint const int
#define cdouble const double
#define mset(f, z) memset(f, z, sizeof(f))
#define all(x) x.begin(), x.end()
#define len(x) ll(x.size())
#define MIN(v) *min_element(all(v))
#define MAX(v) *max_element(all(v))
template <class T, class S>
inline bool chmax(T &_a, const S &_b) {
    return (_a < _b ? _a = _b, 1 : 0);
}
template <class T, class S>
inline bool chmin(T &_a, const S &_b) {
    return (_a > _b ? _a = _b, 1 : 0);
}
template <class T>
void wt(T _x) { cout << _x << " "; }
template <class T>
void print(T _x) { cout << _x << endl; }
template <class T>
void print(const T *_arr, int _l, int _r) {
    if (_l <= _r) rep(i, _l, _r) cout << _arr[i] << " \n"[i == _r];
    else per(i, _l, _r) cout << _arr[i] << " \n"[i == _r];
}
void YES(bool t = 1) { cout << (t ? "YES" : "NO") << endl; }
void NO(bool t = 1) { YES(!t); }
void Yes(bool t = 1) { cout << (t ? "Yes" : "No") << endl; }
void No(bool t = 1) { Yes(!t); }
void yes(bool t = 1) { cout << (t ? "yes" : "no") << endl; }
void no(bool t = 1) { yes(!t); }
// ===========================================================
// Problem: 分组背包问题
// URL: https://www.acwing.com/problem/content/9/
// ===========================================================

cint N = 101;

int n, m;
int s[N];
int v[N][N], w[N][N];
int f[N][N][N];

void solve() {
    cin >> n >> m;
    rep(i, n) {
        cin >> s[i];
        rep(j, s[i]) cin >> v[i][j] >> w[i][j];
    }
    rep(i, n) {
        rep(j, s[i]) {
            rep(k, m) {
                f[i][j][k] = max(f[i][j - 1][k], f[i - 1][s[i - 1]][k]);
                if (v[i][j] <= k) chmax(f[i][j][k], f[i - 1][s[i - 1]][k - v[i][j]] + w[i][j]);
            }
        }
    }
    print(f[n][s[n]][m]);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    solve();
    // ================================================
    return 0;
}
