#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;
// #define int long long
#define cint const int
#define cdouble const double
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> PII;
typedef vector<ll> vi;
typedef vector<PII> vpii;
template <class T>
using vc = vector<T>;
template <class T>
using vvc = vc<vc<T>>;
cint inf = 0x7f7f7f7f;
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
#define mset(f, z) memset(f, z, sizeof(f))
#define len(x) x.size()
#define all(x, n) x + 1, x + 1 + n
#define edd(x, n) x + 1 + n
#define MIN(v, n) *min_element(all(v, n))
#define MAX(v, n) *max_element(all(v, n))
#define LB(c, n, x) distance(c, lower_bound(all(c, n), (x)))
#define UB(c, n, x) distance(c, upper_bound(all(c, n), (x)))
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
void print() { cout << endl; }
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
// Problem: F. Igor and Mountain
// URL: https://codeforces.com/contest/2091/problem/F
// ===========================================================

cint N = 2005;
cint mod = 998244353;

int n, m, d;
bool a[N][N];
ll f[N][N][2];
ll sum[N];

ll add(ll x, ll y) { return (x + y) % mod; }
ll sub(ll x, ll y) { return (x - y + mod) % mod; }

void solve() {
    cin >> n >> m >> d;
    rep(i, n) rep(j, m) {
        char t;
        cin >> t;
        a[i][j] = t == 'X';
        f[i][j][0] = f[i][j][1] = sum[j] = 0;
    }

    // f[n,...,0] is processed
    rep(i, m) f[n][i][0] = a[n][i];

    per(i, n) {
        rep(j, m) sum[j] = add(sum[j - 1], f[i][j][0]);

        ll t = d;
        rep(j, m) if (a[i][j]) {
            ll l = max(1ll, j - t), r = min(ll(m), j + t);
            auto &ff = f[i][j][1];
            ff = sub(sum[r], sum[l - 1]);
            ff = sub(ff, f[i][j][0]);
        }

        rep(j, m) sum[j] = add(sum[j - 1], f[i][j][0]), sum[j] = add(sum[j], f[i][j][1]);

        t = d - 1;
        rep(j, m) if (a[i - 1][j]) {
            ll l = max(1ll, j - t), r = min(ll(m), j + t);
            auto &ff = f[i - 1][j][0];
            ff = sub(sum[r], sum[l - 1]);
        }
    }

    print(sum[m]);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    int T;
    cin >> T;
    rep(T) solve();
    // ================================================
    return 0;
}
