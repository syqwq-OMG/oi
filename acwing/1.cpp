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
#define rep(i, a, b) for (int i = a; i < b; i++)
#define repp(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = (a) - 1; i >= b; i--)
#define perr(i, a, b) for (int i = a; i >= b; i--)
#define all(x) x.begin(), x.end()
#define len(x) ll(x.size())
#define MIN(v) *min_element(all(v))
#define MAX(v) *max_element(all(v))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> PII;
typedef vector<int> vi;
typedef vector<PII> vpii;
template <class T>
using vc = vector<T>;
template <class T>
using vvc = vc<vc<T>>;
template <class T, class S>
inline bool chmax(T &a, const S &b) {
    return (a < b ? a = b, 1 : 0);
}
template <class T, class S>
inline bool chmin(T &a, const S &b) {
    return (a > b ? a = b, 1 : 0);
}
template <class T>
void print(T x) { cout << x << endl; }
template <class T>
void print(const T *arr, int beg, int end) {
    if (beg <= end) repp(i, beg, end) cout << arr[i] << " \n"[i == end];
    else perr(i, beg, end) cout << arr[i] << " \n"[i == end];
}
void YES(bool t = 1) { cout << (t ? "YES" : "NO") << endl; }
void NO(bool t = 1) { YES(!t); }
void Yes(bool t = 1) { cout << (t ? "Yes" : "No") << endl; }
void No(bool t = 1) { Yes(!t); }
void yes(bool t = 1) { cout << (t ? "yes" : "no") << endl; }
void no(bool t = 1) { yes(!t); }
// ===========================================================
// Problem: A + B
// URL: https://www.acwing.com/problem/content/1/
// ===========================================================

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    int a, b;
    cin >> a >> b;
    int x[5];
    repp(i, 1, 3) x[i] = i;
    print(x, 1, 3);
    // ================================================
    return 0;
}
