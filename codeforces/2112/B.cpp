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
#define rp3(i, a, b) for (ll i = (a); i < ll(b); i++)
#define rp4(i, a, b, d) for (ll i = (a); i < ll(b); i += (d))
#define per2(i, a) for (ll i = (a); i >= 1; i--)
#define per3(i, a, b) for (ll i = (a); i >= ll(b); i--)
#define per4(i, a, b, d) for (ll i = (a); i >= ll(b); i -= (d))
#define pr3(i, a, b) for (ll i = (a) - 1; i >= ll(b); i--)
#define pr4(i, a, b, d) for (ll i = (a) - 1; i >= ll(b); i -= (d))
#define overload4(a, b, c, d, e, ...) e
#define rep(...) overload4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)
#define rp(...) overload4(__VA_ARGS__, rp4, rp3)(__VA_ARGS__)
#define per(...) overload4(__VA_ARGS__, per4, per3, per2)(__VA_ARGS__)
#define pr(...) overload4(__VA_ARGS__, pr4, pr3)(__VA_ARGS__)
#define mset(f, z) memset(f, z, sizeof(f))
#define elif else if
#define all(x, n) x + 1, x + 1 + n
#define MIN(v, n) *min_element(all(v, n))
#define MAX(v, n) *max_element(all(v, n))
auto chmax = [](auto &_a, const auto &_b) -> bool { return _a < _b ? _a = _b, 1 : 0; };
auto chmin = [](auto &_a, const auto &_b) -> bool { return _a > _b ? _a = _b, 1 : 0; };
template <class T>
void wt(const T _x) { cout << _x; }
template <>
void wt(const PII _x) { cout << _x.fi << " " << _x.se; }
void print() { cout << endl; }
template <class Head, class... Tail>
void print(Head &&head, Tail &&...tail) {
    wt(head);
    if (sizeof...(Tail)) wt(' ');
    print(std::forward<Tail>(tail)...);
}
template <class T>
void aprint(const T *_arr, int _l, int _r) {
    if (_l <= _r) rep(i, _l, _r) cout << _arr[i] << " \n"[i == _r];
    else per(i, _l, _r) cout << _arr[i] << " \n"[i == _r];
}
ll gcd(ll _x, ll _y) { return _y ? gcd(_y, _x % _y) : _x; }
void YES(bool t = 1) { cout << (t ? "YES" : "NO") << endl; }
void NO(bool t = 1) { YES(!t); }
void Yes(bool t = 1) { cout << (t ? "Yes" : "No") << endl; }
void No(bool t = 1) { Yes(!t); }
void yes(bool t = 1) { cout << (t ? "yes" : "no") << endl; }
void no(bool t = 1) { yes(!t); }
cint PRECISION = 5;
// #define int long long
#define CF
// ===========================================================
// Problem: B. Shrinking Array
// URL: https://codeforces.com/contest/2112/problem/B
// ===========================================================
cint N = 1005;

int n;
int a[N];
int premn[N], premx[N], sufmn[N], sufmx[N];
int idlmn[N], idlmx[N], idrmn[N], idrmx[N];
void solve() {
    cin >> n;
    rep(i, n) cin >> a[i];

    rep(i, 2, n) if (abs(a[i] - a[i - 1]) <= 1) return print(0);

    if (n == 2) return print(-1);

    premn[0] = sufmn[n + 1] = inf<int>, premx[0] = sufmx[n + 1] = -inf<int>;
    rep(i, n) premn[i] = min(premn[i - 1], a[i]), premx[i] = max(premx[i - 1], a[i]),
              idlmn[i] = premn[i] == a[i] ? i : idlmn[i - 1], idlmx[i] = premx[i] == a[i] ? i : idlmx[i - 1];

    per(i, n) sufmn[i] = min(sufmn[i + 1], a[i]), sufmx[i] = max(sufmx[i + 1], a[i]),
              idrmn[i] = sufmn[i] == a[i] ? i : idrmn[i + 1], idrmx[i] = sufmx[i] == a[i] ? i : idrmx[i + 1];

    int ans = inf<int>;
    rep(l, n - 1) rep(r, l + 1, n) {
        int lmn = premn[l], lmx = premx[l], rmx = sufmx[r], rmn = sufmn[r];
        if (lmx >= rmn && lmn <= rmn) chmin(ans, min(idrmx[r], idrmn[r]) - max(idlmn[l], idlmx[l]));
        if (rmx >= lmn && rmn <= lmn) chmin(ans, min(idrmn[r], idrmx[r]) - max(idlmn[l], idlmx[l]));
    }
    if (ans == inf<int>) print(-1);
    else print(1);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.setf(ios::fixed), cout.precision(PRECISION);
    // ================================================
    int T = 1;
#ifdef CF
    cin >> T;
#endif
    rep(T) solve();
    // ================================================
    return 0;
}
