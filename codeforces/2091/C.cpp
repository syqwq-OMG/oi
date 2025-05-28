#include <algorithm>
#include <array>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
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
#define rep(i, a, b) for (ll i = a; i < b; i++)
#define repp(i, a, b) for (ll i = a; i <= b; i++)
#define per(i, a, b) for (ll i = (a) - 1; i >= b; i--)
#define perr(i, a, b) for (ll i = a; i >= b; i--)
#define cint const int
#define all(x) x.begin(), x.end()
#define len(x) ll(x.size())
#define MIN(v) *min_element(all(v))
#define MAX(v) *max_element(all(v))
template <class T, class S>
inline bool chmax(T &a, const S &b) {
    return (a < b ? a = b, 1 : 0);
}
template <class T, class S>
inline bool chmin(T &a, const S &b) {
    return (a > b ? a = b, 1 : 0);
}
template <class T>
void print(T _x) { cout << _x << endl; }
template <class T>
void print(const T *_arr, int _beg, int _end) {
    if (_beg <= _end) repp(i, _beg, _end) cout << _arr[i] << " \n"[i == _end];
    else perr(i, _beg, _end) cout << _arr[i] << " \n"[i == _end];
}
void YES(bool t = 1) { cout << (t ? "YES" : "NO") << endl; }
void NO(bool t = 1) { YES(!t); }
void Yes(bool t = 1) { cout << (t ? "Yes" : "No") << endl; }
void No(bool t = 1) { Yes(!t); }
void yes(bool t = 1) { cout << (t ? "yes" : "no") << endl; }
void no(bool t = 1) { yes(!t); }
// ===========================================================
// Problem: C. Combination Lock
// URL: https://codeforces.com/contest/2091/problem/C
// ===========================================================
cint N = 2e5 + 5;

int n;
int a[N];

void solve() {
    cin >> n;
    if (n % 2 == 0) return print(-1);
    int tt = 0;
    for (int i = 1; i <= n; i += 2) a[++tt] = i;
    for (int i = 2; i <= n; i += 2) a[++tt] = i;
    print(a, 1, n);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    int T;
    cin >> T;
    while (T--) solve();
    // ================================================
    return 0;
}
