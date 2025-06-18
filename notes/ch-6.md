## Ch 6 基础算法

### 水题 www

#### [90. 64位整数乘法](https://www.acwing.com/problem/content/92/)
##### 思路
类似快速幂的想法，也叫做“龟速乘”
##### 蒟蒻代码
``` cpp
void solve() {
    ll a, b, p;
    cin >> a >> b >> p;
    ll ans = 0;
    for (ll t = a; b; b >>= 1, t = add(t, t, p))
        if (b & 1) ans = add(ans, t, p);
    print(ans);
}
```
#### [95. 费解的开关](https://www.acwing.com/problem/content/97/)
##### 思路
注意到
1、一个开关最多被按一次
2、开关按的顺序与最终结果无关
3、固定前k行后，如果要求k+1行全是1，那么方案最多一种
于是，根据以上的想法，可以先枚举第一行的所有状态，然后，向下递推，看最后一行是否满足要求。

*感觉 递推要求状态转换的路径的唯一性* 
##### 蒟蒻代码
``` cpp
cint N = 6;
cint dx[] = {-1, 1, 0, 0, 0};
cint dy[] = {0, 0, 0, -1, 1};

char a[N][N], b[N][N];

void turn(int x, int y) {
    rep(i, 0, 4) {
        auto &t = b[x + dx[i]][y + dy[i]];
        t = (t == '0' ? '1' : '0');
    }
}

void solve() {
    rp(i, 0, 5) cin >> a[i];

    int ans = inf<int>;
    rp(op, 0, 1 << 5) {
        int cnt = 0;

        memcpy(b, a, sizeof a);
        // operate on the 1th row
        rp(i, 0, 5) if (op >> i & 1) turn(0, i), cnt++;

        rep(i, 4) rep(j, 0, 4) if (b[i - 1][j] == '0') turn(i, j), cnt++;

        if (cnt > 6) continue;
        bool flg = 1;
        rep(i, 0, 4) if (b[4][i] == '0') {
            flg = 0;
            break;
        }
        if (flg) chmin(ans, cnt);
    }

    if (ans == inf<int>) print(-1);
    else print(ans);
}
```
#### [97. 约数之和](https://www.acwing.com/problem/content/99/)
##### 思路
容易发现：
$$
A^{B}=\prod_{p \mid A} \sum_{i=0}^{\alpha_{p}\cdot B}p^{i}
$$
分别处理每个局部的因式，可以考虑用等比数列求和公式，因为9901是质数，所以模他的环构成域，但是注意对于零元没有逆，所以在考虑计算如果 $p-1$ 是9901的倍数的时候，要特判，因为$p-1=0$, 所以$p=1$，所以，计算的时候只要乘上 $\alpha_p \cdot B$就可以
##### 蒟蒻代码
``` cpp
cint mod = 9901;
ll add(ll x, ll y) { return (x + y) % mod; }
ll sub(ll x, ll y) { return (x - y + mod) % mod; }
ll mul(ll x, ll y) { return x * y % mod; }
ll inv(ll x) { return qpow(x, mod - 2, mod); }

vpii divisors;

void solve() {
    ll a, b;
    cin >> a >> b;
    if (b == 0) return print(1);
    if (a == 0) return print(0);

    for (ll i = 2; i <= a / i; i++) {
        if (a % i != 0) continue;
        int cnt = 0;
        while (a % i == 0) cnt++, a /= i;
        divisors.emplace_back(i, cnt);
    }
    if (a > 1) divisors.emplace_back(a, 1);

    ll ans = 1;

    for (auto [p, q] : divisors) {
        q *= b;
        if ((p - 1) % mod != 0) {
            ans = mul(ans, sub(qpow(p, q + 1, mod), 1));
            ans = mul(ans, inv(p - 1));
        } else {
            ans = add(ans, q);
        }
    }

    print(ans);
}
```
#### [98. 分形之城](https://www.acwing.com/problem/content/100/)
##### 思路 
分治题目，每次分成4个子问题，然后进行坐标变换。这里注意左上角相当于对对角线做对称变换，左下角相当于对反对角线做对称变换
*注意 1不加ll是32位，要通过移位运算符得到long long的话，要写 1ll*
##### 蒟蒻代码
``` cpp
double dis(PII x, PII y) {
    double dx = x.fi - y.fi, dy = x.se - y.se;
    return 10.0 * sqrt(dx * dx + dy * dy);
}

PII calc(ll n, ll p) {
    if (!n) return {0, 0};
    ll sz = 1ll << (2 * n - 2);
    auto [x, y] = calc(n - 1, p % sz);
    ll len = 1ll << (n - 1), z = p / sz;
    if (z == 0) return {y, x};
    elif (z == 1) return {x, y + len};
    elif (z == 2) return {x + len, y + len};
    else return {2 * len - y - 1, len - x - 1};
}

void solve() {
    ll n, x, y;
    cin >> n >> x >> y;
    auto xx = calc(n, x - 1);
    auto yy = calc(n, y - 1);
    print(dis(xx, yy));
}
```

#### [99. 激光炸弹](https://www.acwing.com/problem/content/description/101/)
##### 思路
二维前缀和模板题，但是注意数组大小比较大，容易MLE，所以尽可能压缩一下空间。
##### 蒟蒻代码
``` cpp
cint N = 5005;

int n, r;
int s[N][N];

int qwq(int x, int y) {
    int xx = x + r - 1, yy = y + r - 1;
    if (xx > 5001 || yy > 5001) return -inf<int>;
    return s[xx][yy] - s[x - 1][yy] - s[xx][y - 1] + s[x - 1][y - 1];
}

void solve() {
    cin >> n >> r;
    chmin(r, 5001);
    rep(n) {
        int x, y, w;
        cin >> x >> y >> w;
        s[x + 1][y + 1] += w;
    }

    rep(i, 5001) rep(j, 5001) s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + s[i][j];

    int ans = -inf<int>;
    rep(i, 5001) rep(j, 5001) chmax(ans, qwq(i, j));
    print(ans);
}
```
#### [100. 增减序列](https://www.acwing.com/problem/content/102/)
##### 思路
对于区间修改，考虑差分数组的形式，因为只能加1或者减1，所以对应的差分数组就是只能选两个点一个+1，一个-1，从而，最终期望的状态就是除了第一个元素，其他都是0，于是为了尽可能少修改，我们希望正项与负项能尽可能抵消，所以可以对此进行统计，在抵消的时候就意味着修改，因此就把这个抵消的量加到ans里面。

对于最后可能出现的所有值，实际上在2~n都是0的时候，只取决于`d[1]`的取值，所以只要考虑最后还剩下的那些+1 或者 -1的操作是给到 `d[1]` 还是给 `d[n+1]`，因此可能的情况就是操作的次数+1.

*注意：考虑最终的状态，并对操作按照对**有效部分**的影响进行分类有助于更好的分析问题*
##### 蒟蒻代码
``` cpp
cint N = 1e5 + 5;

int n;
int a[N], d[N];

void solve() {
    cin >> n;
    rep(i, n) cin >> a[i], d[i] = a[i] - a[i - 1];

    ll ans = 0, po = 0, ne = 0;
    rep(i, 2, n) {
        if (d[i] > 0) po += d[i];
        if (d[i] < 0) ne -= d[i];
        if (po == 0 || ne == 0) continue;
        if (po >= ne) ans += ne, po -= ne, ne = 0;
        else ans += po, ne -= po, po = 0;
    }

    if (po == 0 && ne == 0) return print(ans), print(1);
    elif (po) return print(ans + po), print(po + 1);
    else return print(ans + ne), print(ne + 1);
}
```

#### [102. 最佳牛围栏](https://www.acwing.com/problem/content/104/)
##### 思路
首先，求**平均值的最大值**问题，可以想到**对答案做二分**，在这里显然当平均值比较小的时候都是可以满足的，而大的时候就无法满足，满足二分判定的条件。

因此，在对一个平均值$x$确定的情况下，需要判定的就是是否存在一个长度大于$f$的子区间，使得他的平均值大于$x$，对于这种情形，我们等价于，**给每个数字都减去$x$**，是否存在长度大于$f$的**子区间的和**大于0，于是可以想到利用**前缀和**优化。

于是问题变成了对于$s[i],i \in \{ f,f+1, \ldots ,n \}$，是否有$s[i]-\min\{ s[0],s[1], \ldots ,s[i-f] \}>0$，观察到**需要dp的集合是不断扩展的，所以可以用一个变量来维护最小值**，因此本来$O(n^{2})$的暴力枚举，由于集合扩展的单调性，优化成了$O(n)$的判定.

因此整个算法的时间复杂度是$O(n\log W)$

*注意：
1、平均值求最大，考虑二分
2、求子区间平均值是否都大于给定值可以对所有值减去给定值，再判断和是否大于0
3、随时随地考虑dp思想
4、考虑dp能否被优化
5、注意最后答案只能用$r$，不能用$l$，因为如果答案恰好是一个整数，那么$l$会有问题*
##### 蒟蒻代码
``` cpp
cint N = 1e5 + 5;
cdouble eps = 1e-5;

int n, f;
int a[N];
double s[N];

bool check(double x) {
    double ans = 0;
    rep(i, n) s[i] = s[i - 1] + a[i] - x;
    double mn = s[0];
    rep(i, f, n) chmax(ans, s[i] - mn), chmin(mn, s[i - f + 1]);
    return ans > 0;
}

void solve() {
    cin >> n >> f;
    rep(i, n) cin >> a[i];

    double l = 1, r = 2000;
    while (r - l > eps) {
        auto mid = (l + r) / 2;
        if (check(mid)) l = mid;
        else r = mid;
    }

    print(int(r * 1000.0));
}
```

#### [113. 特殊排序](https://www.acwing.com/problem/content/115/)
##### 思路
可以用归并排序，直接偷懒（本来用的是插入排序的思路）。其实这题的核心在于使用二分，不一定是一边满足要求，另一边不满足要求，而是，只要能够确定一边一定有满足要求的解，另一边无所谓，就能用二分，也就是只要满足每次能够去除一半的可能性，就能用二分。
##### 蒟蒻代码
``` cpp
// Forward declaration of compare API.
// bool compare(int a, int b);
// return bool means whether a is less than b.
#include <iostream>
#include <cstring>
#include <numeric>
#include <algorithm>

class Solution {
public:
    vector<int> specialSort(int N) {
        vector<int> v(N);
        iota(v.begin(), v.end(), 1);
        stable_sort(v.begin(), v.end(), compare);
        return v;
    }
};
```

#### [105. 七夕祭](https://www.acwing.com/problem/content/description/107/)
##### 思路
首先，对于这种网格的题目，不难观察到如果只对列进行操作，对于每行的元素个数是没有影响的；同理对于每行的元素进行操作，对于每一列的元素个数也是没有影响的。因此，我们可以对行列分开考虑，不妨我们先考虑行的最小值，在考虑列的最小值。

其次，由于一共有 $t$ 个摊点，如果能够均匀分布在行上，那么一定有 $n \mid t$；同理，如果列有解，那么一定有 $m \mid t$，因此可以快速用此判断是否有解。

接下来，我们考虑有解的情况。以行为例，列同理。由于是要操作次数的最小值，因此一定不存在“推推搡搡”的交换过程，所以**一定有一种适当的顺序，使得每一次的传递操作可以转化为交换一堆左右相邻的摊点（其中cl恰好对这两个摊点之一感兴趣）**。

假设 $n$ 行每行的原始数量分别为 $a_1,a_2, \ldots ,a_{n}$，假设在最优的操作中，$a_{i}$ 给 $a_{i-1}$ 的摊点数量为 $x_{i}$（$x_{1}$ 为 $a_{1}$ 给 $a_n$ 的数量，且如果 $x_{i}<0$ 表示反向）。那么就应该是 $\sum |x_{i}|$。那么我们接下来考虑一下要求这个式子的最小值的约束条件。

令 $a=\frac{1}{n}\sum a_{i}$，也就是最终要达到的平均值的目标。于是我们考虑每一行的数量变化，仅仅来自给出的和得到的，于是我们得到方程组：
$$
\begin{cases}
a_1-x_1+x_2&=a\\ 
a_2-x_2+x_3&=a\\
\cdots &= \cdots \\
a_n-x_n+x_1&=a
\end{cases}
$$
这个方程组显然不可能有唯一解，不然最小值就不能称之为最小值了 QwQ,因为我们把所有式子相加得到的是一个恒等式，于是这里面的自由变量至少有1个，不妨设自由变量为 $x_1$，于是我们重写方程组为：
$$
\begin{cases}
x_2&=x_1-(a_1-a)\\ 
x_3&=x_2-(a_2-a)=x_1-(a_1+a_2-2a)\\
\cdots&=\cdots\\
x_n&=x_1-(a_1+a_2+ \cdots +a_{n-1}-(n-1)a)
\end{cases}
$$
于是，我们要求的 $\sum |x_i|= |x_1|+|x_1-(a_1-a)|+ \cdots +|x_1-(a_1+a_2+ \cdots +a_{n-1}-(n-1)a)|$，于是求这坨东西的最小值，我们考虑排序后，首尾组合用三角不等式，因此最小值在排序后的中位数取到，这题就做完了 ovo

##### 蒟蒻代码
``` cpp
cint N = 1e5 + 5;

int n, m, tt;
int a[N], b[N];
ll t[N];

ll doo(int *f, int v) {
    ll mm = tt / v;
    rep(i, 2, v) t[i] = t[i - 1] + f[i - 1] - mm;
    sort(all(t, v));
    mm = t[(v + 1) >> 1];
    ll ret = 0;
    rep(i, 1, v) ret += abs(mm - t[i]);
    return ret;
}

void solve() {
    cin >> n >> m >> tt;
    rep(tt) {
        int x, y;
        cin >> x >> y;
        a[x]++, b[y]++;
    }

    ll ans1 = tt % n == 0 ? doo(a, n) : -1;
    ll ans2 = tt % m == 0 ? doo(b, m) : -1;
    if (ans1 == -1 && ans2 == -1) print("impossible");
    elif (ans1 == -1 && ans2 != -1) print("column", ans2);
    elif (ans1 != -1 && ans2 == -1) print("row", ans1);
    else print("both", ans1 + ans2);
}
```

#### [106. 动态中位数](https://www.acwing.com/problem/content/108/)
##### 思路
可以用平衡树，可以用链表来离线，这里使用对顶堆来维护数组的一半的集合，其中保证下一个堆要么和上面大小相等，要么之比他多1个元素即可。
##### 蒟蒻代码
``` cpp
cint N = 5e5 + 5;

int P, n;

void doo() {
    priority_queue<int> small;
    priority_queue<int, vc<int>, greater<int>> big;

    int cnt = 0, len = 0;
    rep(i, n) {
        int x;
        cin >> x;

        if (small.empty() || x <= small.top()) small.push(x);
        else big.push(x);
        while (big.size() > small.size()) small.push(big.top()), big.pop();
        while (small.size() > big.size() + 1) big.push(small.top()), small.pop();

        if (i & 1) len++, wt(small.top()), wt(' ');
        if (len == 10) len = 0, print();
    }
    if (len) print();
}

void solve() {
    cin >> P >> n;
    print(P, (n + 1) / 2);
    doo();
}
```

#### [107. 超快速排序](https://www.acwing.com/problem/content/109/)
##### 思路
线性代数结论：只通过邻项交换，一个排列变成排好序的状态的交换次数等于逆序对的数量。

每次交换，最多使得逆序对的数量减少1，而最终状态，逆序对的数量为0，因此至少要交换逆序对的数量次。如果当前序列还存在逆序对的话，必然存在两个相邻元素，前面一个大于后面一个（因为如果都不满足，就是排好序的）所以，每一次只要保证交换的是这俩就行，所以就是逆序对的数量次。
##### 蒟蒻代码
``` cpp
cint N = 5e5 + 5;

int n;
int a[N];

ll mgsort(int *f, int l, int r) {
    if (l >= r) return 0;
    int mid = (l + r) >> 1;
    ll ret = mgsort(f, l, mid) + mgsort(f, mid + 1, r);
    int cnt = 0, t[N];
    int i = l, j = mid + 1;
    while (i <= mid && j <= r) {
        if (f[i] <= f[j]) t[++cnt] = f[i++];
        else t[++cnt] = f[j++], ret += mid - i + 1;
    }
    while (i <= mid) t[++cnt] = f[i++];
    while (j <= r) t[++cnt] = f[j++];
    for (i = l, j = 1; i <= r; i++, j++) f[i] = t[j];
    return ret;
}

void solve() {
    while (cin >> n, n) {
        rep(i, n) cin >> a[i];
        ll ans = mgsort(a, 1, n);
        print(ans);
    }
}
```

#### [1273. 天才的记忆](https://www.acwing.com/problem/content/1275/)
##### 思路
查询区间最值，可以用线段树，树状数组…… 但是这里使用ST表（跳表）。

ST表，可以理解为是一种基于倍增思想的dp。我们用 $f[i][j]$ 表示 从 $i$ 开始，长度为 $2^{j}$ 的区间的最大值，于是可以很简单得到状态转移方程，这里不写了，可以看`init`函数，计算这个数组类似区间dp，查询的时候，按照区间长度对2取对数向下取整，用两端区间去覆盖即可。于是，预处理时间复杂度为 $O(n\log n)$，每次查询时间复杂度为 $O(w)$，$w$ 为对数运算计算的时间。也可以对区间长度预处理出对应的对数值，可以实现严格的 $O(1)$ 查询。

*注意考虑边界是否+1*

##### 蒟蒻代码
``` cpp
cint N = 2e5 + 5, M = 18;

int n, m;
int a[N];
int f[N][20];

void init() {
    rp(len, 0, M) for (int l = 1; l + (1 << len) - 1 <= n; l++)
        f[l][len] = len ? max(f[l][len - 1], f[l + (1 << (len - 1))][len - 1]) : a[l];
}

int query(int l, int r) {
    int len = log2(r - l + 1);
    return max(f[l][len], f[r - (1 << len) + 1][len]);
}

void solve() {
    cin >> n; 
    rep(i, n) cin >> a[i];
    init();
    cin >> m;
    rep(m) {
        int l, r;
        cin >> l >> r;
        print(query(l, r));
    }
}
```
