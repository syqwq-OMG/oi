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
#define int long long
// #define CF
// ===========================================================
// Problem: 次小生成树
// URL: https://www.acwing.com/problem/content/description/358/
// ===========================================================
cint N = 3e5 + 5;

struct node {
    ll u, v, w;
};

ll n, m;
vpii g[N];
node edge[N];
bool st[N];
ll fa[N];
ll mst = 0;
ll ans = inf<ll>;
ll dep[N], f[N][18], d1[N][18], d2[N][18];

void add(ll x, ll y, ll z) { g[x].push_back({y, z}); }
ll get(ll x) {
    if (fa[x] == x) return x;
    return fa[x] = get(fa[x]);
}
// used to change the first and secong max value of df and ds
void change(ll &df, ll &ds, ll t) {
    if (t > df) ds = df, df = t;
    elif (t != df && t > ds) ds = t;
}
void bfs() {
    queue<int> q;
    dep[1] = 1, q.push(1);
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (auto [v, w] : g[u]) {
            if (dep[v]) continue; // exclude the parent node
            dep[v] = dep[u] + 1;
            d1[v][0] = w, d2[v][0] = -inf<ll>;
            f[v][0] = u;
            rep(i, 1, 17) {
                ll anc = f[v][i - 1];
                f[v][i] = f[anc][i - 1];
                ll distance[] = {d1[v][i - 1], d2[v][i - 1], d1[anc][i - 1], d2[anc][i - 1]};
                d1[v][i] = d2[v][i] = -inf<ll>;
                rep(j, 0, 3) {
                    int d = distance[j];
                    change(d1[v][i], d2[v][i], d);
                }
            }
            q.push(v);
        }
    }
}
void build() {
    rep(i, m) {
        if (st[i]) {
            auto [x, y, z] = edge[i];
            add(x, y, z), add(y, x, z);
        }
    }
}
ll lca(ll u, ll v, ll w) {
    ll disf = -inf<ll>, diss = -inf<ll>;
    if (dep[u] < dep[v]) swap(u, v);
    per(i, 17, 0) {
        if (dep[f[u][i]] >= dep[v]) {
            change(disf, diss, d1[u][i]);
            change(disf, diss, d2[u][i]);
            u = f[u][i];
        }
    }
    if (u != v) {
        per(i, 17, 0) {
            if (f[u][i] != f[v][i]) {
                change(disf, diss, d1[u][i]);
                change(disf, diss, d2[u][i]);
                change(disf, diss, d1[v][i]);
                change(disf, diss, d2[v][i]);
                u = f[u][i], v = f[v][i];
            }
        }
        change(disf, diss, d1[u][0]);
        change(disf, diss, d1[v][0]);
    }
    if (w > disf) return w - disf;
    if (w > diss) return w - diss;
    return inf<ll>;
}
void solve() {
    cin >> n >> m;
    rep(i, n) fa[i] = i;
    rep(i, m) {
        int x, y, z;
        cin >> x >> y >> z;
        edge[i] = {x, y, z};
    }
    sort(all(edge, m), [](auto x, auto y) { return x.w < y.w; });
    rep(i, m) {
        auto [u, v, w] = edge[i];
        ll x = get(u), y = get(v);
        if (x != y) {
            fa[x] = y, mst += w;
            st[i] = 1;
        }
    }
    build();
    bfs();
    ll ans = inf<ll>;
    rep(i, m) {
        if (st[i]) continue;
        auto [u, v, w] = edge[i];
        chmin(ans, mst + lca(u, v, w));
    }
    print(ans);
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
