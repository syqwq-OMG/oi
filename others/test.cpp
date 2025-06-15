#include <bits/stdc++.h>
#define mod 1000000007
#define int long long
using namespace std;
struct node {
    int t, x, y, a;
} a[1200005];
int tag[1200005], sy[1200005];
vector<int> vx[1200005], vy[1200005], vxda[1200005];
const int B = 314;
int pw[1200005];
inline int read() {
    int s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
    return s * w;
}
int ksm(int x, int y) {
    int rtn = 1;
    while (y) {
        if (y & 1) rtn = (rtn * x) % mod;
        x = x * x % mod, y >>= 1;
    }
    return rtn;
}
int f(int a, int x) {
    return ksm(a, pw[x]);
}
signed main() {
    pw[0] = 1;
    for (int i = 1; i <= 1200000; i++)
        pw[i] = (pw[i - 1] << 1) % (mod - 1);
    int n, m;
    n = read(), m = read();
    for (int i = 1; i <= n; i++) {
        a[i].x = read(), a[i].y = read(), a[i].a = read();
        a[i].t = 0;
        vx[a[i].x].push_back(i);
        vy[a[i].y].push_back(i);
        sy[a[i].y] += a[i].a;
    }
    for (int i = 1; i <= n; i++) {
        if (vy[a[i].y].size() >= B)
            vxda[a[i].x].push_back(i);
    }
    while (m--) {
        int op, x;
        op = read(), x = read();
        if (op == 1) {
            ++tag[x];
            for (auto t : vxda[x]) {
                sy[a[t].y] -= a[t].a;
                a[t].a = (a[t].a * a[t].a) % mod;
                sy[a[t].y] += a[t].a;
            }
        } else {
            if (vy[x].size() >= B) {
                printf("%lld\n", (sy[x] % mod + mod) % mod);
                // cout << (sy[x] % mod + mod) % mod << "\n";
                continue;
            }
            int rtn = 0;
            for (auto t : vy[x]) {
                if (a[t].t + tag[a[t].x] != 0) {
                    int d = (a[t].t + tag[a[t].x]);
                    a[t].t -= d;
                    a[t].a = f(a[t].a, d);
                }
                rtn += a[t].a;
            }
            printf("%lld\n", (rtn % mod + mod) % mod);
            // cout << (rtn % mod + mod) % mod << "\n";
        }
    }
    return 0;
}
