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
// Problem: 观光
// URL: https://www.acwing.com/problem/content/385/
// ===========================================================
cint N = 1005;

struct node {
    int ver, type, dist;
    node(int ver, int type, int dist) : ver(ver), type(type), dist(dist) {}
    bool operator<(const node p) const { return dist > p.dist; }
};

int n, m, S, F;

int dij(vpii *g) {
    bool st[N][2];
    int dis[N][2], cnt[N][2];
    priority_queue<node> pq;
    mset(dis, 0x3f), mset(st, 0), mset(cnt, 0);

    dis[S][0] = 0, cnt[S][0] = 1, pq.push(node(S, 0, 0));
    while (pq.size()) {
        auto [u, t, d] = pq.top();
        pq.pop();
        if (st[u][t]) continue;
        st[u][t] = 1;
        for (auto [v, w] : g[u]) {
            if (dis[v][0] > d + w) {
                dis[v][1] = dis[v][0], cnt[v][1] = cnt[v][0],
                dis[v][0] = d + w, cnt[v][0] = cnt[u][t];
                pq.push(node(v, 0, dis[v][0])), pq.push(node(v, 1, dis[v][1]));
            }
            elif (dis[v][0] == d + w) cnt[v][0] += cnt[u][t];
            elif (dis[v][1] > d + w) dis[v][1] = d + w, cnt[v][1] = cnt[u][t], pq.push(node(v, 1, dis[v][1]));
            elif (dis[v][1] == d + w) cnt[v][1] += cnt[u][t];
        }
    }

    int res = cnt[F][0];
    if (dis[F][1] == dis[F][0] + 1) res += cnt[F][1];
    return res;
}

void solve() {
    cin >> n >> m;
    vpii g[N];
    auto add = [&g](int u, int v, int w) { g[u].push_back({v, w}); };
    rep(m) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w);
    }
    cin >> S >> F;
    print(dij(g));
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
