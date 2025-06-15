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
// #define CF
// ===========================================================
// Problem: 拯救大兵瑞恩
// URL: https://www.acwing.com/problem/content/1133/
// ===========================================================
cint N = 11, M = N * N, P = 10;

int n, m, p, k;
vpii g[M];
int id[N][N], key[M], dis[M][1 << P];
set<PII> wall;
bool st[M][1 << P];

void add(int u, int v, int w) { g[u].push_back({v, w}); }

void build() {
    auto check = [](int x, int y) { return 1 <= x && x <= n && y >= 1 && y <= m; };
    int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
    rep(i, 1, n) rep(j, 1, m) rep(d, 0, 3) {
        int x = i + dx[d], y = j + dy[d];
        if (!check(x, y)) continue;
        int a = id[i][j], b = id[x][y];
        if (wall.count({a, b}) == 0) add(a, b, 0);
    }
}

int bfs() {
    auto has = [](int state, int kid) { return state >> (kid - 1) & 1; };
    mset(dis, 0x3f);
    deque<PII> q;
    dis[1][0] = 0, q.push_back({1, 0});
    while (q.size()) {
        auto [u, state] = q.front();
        q.pop_front();

        if (u == n * m) return dis[u][state];
        if (st[u][state]) continue;
        st[u][state] = 1;

        if (key[u]) {
            int t = state | key[u];
            if (chmin(dis[u][t], dis[u][state])) q.push_front({u, t});
        }

        for (auto [v, kind] : g[u]) {
            if (kind && !has(state, kind)) continue;
            if (chmin(dis[v][state], dis[u][state] + 1)) q.push_back({v, state});
        }
    }

    return -1;
}

void solve() {
    cin >> n >> m >> p >> k;
    for (int i = 1, t = 1; i <= n; i++) rep(j, 1, m) id[i][j] = t++;
    rep(k) {
        int x1, x2, y1, y2, w;
        cin >> x1 >> y1 >> x2 >> y2 >> w;
        int u = id[x1][y1], v = id[x2][y2];
        wall.insert({u, v}), wall.insert({v, u});
        if (w) add(u, v, w), add(v, u, w);
    }
    build();
    int s;
    cin >> s;
    rep(s) {
        int x, y, z;
        cin >> x >> y >> z;
        key[id[x][y]] |= 1 << (z - 1);
    }
    print(bfs());
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
