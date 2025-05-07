// Problem: 试除法求约数
// URL: https://www.acwing.com/problem/content/871/

#include <algorithm>
#include <array>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
using ll = long long;
using ull = unsigned long long;
using PII = pair<int, int>;

int n;

void solve(int x) {
    vector<PII> ans;
    for (int i = 1; i <= x / i; i++) {
        if (x % i == 0)
            ans.push_back(make_pair(i, x / i));
    }
    for (auto it = ans.begin(); it != ans.end(); it++)
        cout << (*it).first << " ";
    for (auto it = ans.rbegin(); it != ans.rend(); it++) {
        auto t = *it;
        if (t.first != t.second)
            cout << t.second << " ";
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ================================================
    cin >> n;
    rep(i, 1, n) {
        int t;
        cin >> t;
        solve(t);
    }
    // ================================================
    return 0;
}
