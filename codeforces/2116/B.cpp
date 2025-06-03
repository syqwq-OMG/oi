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
// #define int long long
#define CF
// ===========================================================
// Problem: B. Gellyfish and Baby's Breath
// URL: https://codeforces.com/contest/2116/problem/B
// ===========================================================
ll mod = 998244353;
cint N = 1e5 + 5;

int n;
int p[N], q[N];
int mxp[N], mxq[N];

ll add(ll x, ll y) { return (x + y) % mod; }
ll mul(ll x, ll y) { return x * y % mod; }
ll qpow(int a, int b) {
    ll res = 1;
    for (ll t = a; b; b >>= 1, t = t * t % mod)
        if (b & 1) res = mul(res, t);
    return res;
}

void solve() {
    cin >> n;
    mxp[0] = mxq[0] = 1;
    rep(i, n) {
        cin >> p[i];
        if (p[i] >= p[mxp[i - 1]]) mxp[i] = i;
        else mxp[i] = mxp[i - 1];
    }

    rep(i, n) {
        cin >> q[i];
        if (q[i] >= q[mxq[i - 1]]) mxq[i] = i;
        else mxq[i] = mxq[i - 1];
    }

    rep(i, n) {
        ll ans = -1;
        ll pp1 = p[mxp[i]], qq1 = q[i + 1 - mxp[i]];
        ll qq2 = q[mxq[i]], pp2 = p[i + 1 - mxq[i]];

        if (max(pp1, qq1) > max(pp2, qq2)) ans = add(qpow(2, pp1), qpow(2, qq1));
        else if (max(pp1, qq1) < max(pp2, qq2)) ans = add(qpow(2, pp2), qpow(2, qq2));
        else if (pp1 + qq1 >= pp2 + qq2) ans = add(qpow(2, pp1), qpow(2, qq1));
        else ans = add(qpow(2, pp2), qpow(2, qq2));
        wt(ans);
    }
    print();
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
