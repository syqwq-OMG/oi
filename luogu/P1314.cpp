#include <bits/stdc++.h>
using namespace std;
#define cint const int
#define cdouble const double
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> PII;
typedef vector<ll> vi;
typedef vector<PII> vpii;
template <class T>
using vc = vector<T>;
template <class T>
using vvc = vc<vc<T>>;
template <class T>
constexpr T inf = 0;
template <>
constexpr int inf<int> = 1'010'000'000;
template <>
constexpr ll inf<ll> = 2'020'000'000'000'000'000;
template <>
constexpr double inf<double> = inf<ll>;
#define fi first
#define se second
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
auto chmax = [](auto &_a, const auto &_b) -> bool { return _a < _b ? _a = _b, 1 : 0; };
auto chmin = [](auto &_a, const auto &_b) -> bool { return _a > _b ? _a = _b, 1 : 0; };
template <class T>
void wt(const T _x) { cout << _x << " "; }
void print() { cout << endl; }
template <class T>
void print(const T _x) { cout << _x << endl; }
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
#define int long long
// ===========================================================
// Problem: P1314 [NOIP 2011 提高组] 聪明的质监员
// URL: https://www.luogu.com.cn/problem/P1314
// ===========================================================
cint N = 2e5 + 5;

int l = inf<int>, r = 0;
int ans = inf<int>;
int n, m, s;
int w[N], v[N];
int sw[N], sv[N];
PII a[N];

int qwq(int x) {
    rep(i, n) {
        if (w[i] >= x) sw[i] = sw[i - 1] + 1, sv[i] = sv[i - 1] + v[i];
        else sw[i] = sw[i - 1], sv[i] = sv[i - 1];
    }
    int ret = 0;
    rep(i, m) {
        int tl = a[i].fi, tr = a[i].se;
        ret += (sw[tr] - sw[tl - 1]) * (sv[tr] - sv[tl - 1]);
    }
    return ret;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    cin >> n >> m >> s;
    rep(i, n) cin >> w[i] >> v[i], chmin(l, w[i]), chmax(r, w[i]);
    rep(i, m) cin >> a[i].fi >> a[i].se;

    while (l <= r) {
        int mid = (l + r) >> 1;
        int t = qwq(mid);
        if (t > s) l = mid + 1;
        else r = mid - 1;
        chmin(ans, abs(t - s));
    }
    print(ans);
    // ================================================
    return 0;
}
