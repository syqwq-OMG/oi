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
#define elif else if
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
ll add(ll _x, ll _y, ll _mod) { return (_x + _y) % _mod; }
ll sub(ll _x, ll _y, ll _mod) { return (_x - _y + _mod) % _mod; }
ll mul(ll _x, ll _y, ll _mod) { return _x * _y % _mod; }
ll gcd(ll _x, ll _y) { return _y ? gcd(_y, _x % _y) : _x; }
ll qpow(ll _x, ll _y, ll _mod) {
    ll _res = 1;
    for (ll _t = _x; _y; _y >>= 1, _t = mul(_t, _t, _mod))
        if (_y & 1) _res = mul(_res, _t, _mod);
    return _res;
}
void YES(bool t = 1) { cout << (t ? "YES" : "NO") << endl; }
void NO(bool t = 1) { YES(!t); }
void Yes(bool t = 1) { cout << (t ? "Yes" : "No") << endl; }
void No(bool t = 1) { Yes(!t); }
void yes(bool t = 1) { cout << (t ? "yes" : "no") << endl; }
void no(bool t = 1) { yes(!t); }
// #define int long long
// #define CF
// ===========================================================
// Problem: 耍杂技的牛
// URL: https://www.acwing.com/problem/content/127/
// ===========================================================
cint N = 5e4 + 4;

int n;
struct node {
    int w;
    int s;
} a[N];

// nice solution: https://www.acwing.com/solution/content/845/
void solve() {
    cin >> n;
    rep(i, n) cin >> a[i].w >> a[i].s;
    sort(all(a, n), [](node n1, node n2) { return n1.w + n1.s <= n2.w + n2.s; });
    int ans = -inf<int>;
    ll sum = 0;
    rep(i, n) chmax(ans, sum - a[i].s), sum += a[i].w;
    print(ans);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    int T = 1;
#ifdef CF
    cin >> T;
#endif
    rep(T) solve();
    // ================================================
    return 0;
}
