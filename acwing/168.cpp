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
#define LB(c, n, x) distance(c, lower_bound(all(c, n), (x)))
#define UB(c, n, x) distance(c, upper_bound(all(c, n), (x)))
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
ll qmi(ll _x, ll _y, ll _mod) {
    ll _res = 1;
    for (ll _t = _x; _y; _y >>= 1, _t = _t * _t % _mod)
        if (_y & 1) _res = _res * _t % _mod;
    return _res;
}
void YES(bool t = 1) { cout << (t ? "YES" : "NO") << endl; }
void NO(bool t = 1) { YES(!t); }
void Yes(bool t = 1) { cout << (t ? "Yes" : "No") << endl; }
void No(bool t = 1) { Yes(!t); }
void yes(bool t = 1) { cout << (t ? "yes" : "no") << endl; }
void no(bool t = 1) { yes(!t); }
cint PRECISION = 5;
// #define int long long
// #define CF
// ===========================================================
// Problem: 数独
// URL: https://www.acwing.com/problem/content/168/
// ===========================================================
cint N = 9, M = 1 << N;

int ones[M], lg[M];
// 1 not used 0 used
int row[N], col[N], cell[3][3];
string s;

int lowbit(int x) { return x & (-x); }

void init() {
    rp(i, 0, N) row[i] = col[i] = (1 << N) - 1;
    rp(i, 0, 3) rp(j, 0, 3) cell[i][j] = (1 << N) - 1;
}

int get(int x, int y) { return row[x] & col[y] & cell[x / 3][y / 3]; }

void draw(int x, int y, int d, bool flg) {
    if (flg) s[x * N + y] = d + '1';
    else s[x * N + y] = '.';
    int t = 1 << d;
    if (!flg) t = -t;
    row[x] -= t, col[y] -= t, cell[x / 3][y / 3] -= t;
}

bool dfs(int cnt) {
    if (cnt == 0) return 1;

    int mn = inf<int>, x, y;
    rp(i, 0, N) rp(j, 0, N) {
        if (s[i * N + j] == '.' && chmin(mn, ones[get(i, j)]))
            x = i, y = j;
    }
    int state = get(x, y);
    for (int i = state; i; i -= lowbit(i)) {
        int t = lowbit(i);
        draw(x, y, lg[t], 1);
        if (dfs(cnt - 1)) return 1;
        draw(x, y, lg[t], 0);
    }
    return 0;
}

void solve() {
    rp(i, 0, N) lg[1 << i] = i;
    rp(i, 0, 1 << N) rp(j, 0, N) ones[i] += i >> j & 1;

    while (cin >> s, s != "end") {
        init();
        int cnt = 0;
        rp(i, 0, N) rp(j, 0, N) {
            int t = i * N + j;
            if (s[t] == '.') cnt++;
            else draw(i, j, s[t] - '1', 1);
        }
        dfs(cnt);
        print(s);
    }
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
