## Ch 3 图论
### 零零碎碎零零碎碎
#### 最短路
- 边权均非负
  - 朴素dijkstra（稠密图比较好）
  - 堆优化dijkstra（稀疏图较好） $O(m\log n)$
- 有负权边
  - bellman-ford
  - spfa
- 边权全相等，bfs；边权只有0-1，双端队列bfs
- 一定要善于简化问题，比如统计多少个小于某个值的边，直接把边变成0-1，而不是傻傻记录；就像之前的平均值，把区间每个数减去平均值，再看区间和是不是大于0，多把问题变成0-1的问题
- **分层图or拆点**：大部分的dp的依赖关系可以看成是dag上的拓扑序，每个状态对应一个节点；这启发我们如果这些状态的依赖关系不具有拓扑序，我们可以用最短路来做
- 多源最短路floyd算法：
  - $O(n^{3})$ 求出任意两点最短路径
  - 求传递闭包
  - 找最小环
  - 恰好经过k条边的最短路（倍增）

### 水题 awa
#### [1129. 热浪](https://www.acwing.com/problem/content/1131/)
##### 思路
最短路模板题
##### 蒟蒻代码
``` cpp
cint N = 2505;

int n, m;
vpii g[N];
int dis[N];
bitset<N> st;

void add(int u, int v, int w) { g[u].push_back({v, w}); }
int dijkstra(int start, int end) {
    st &= 0, mset(dis, 0x7f);
    priority_queue<PII> pq;
    dis[start] = 0, pq.push({0, start});
    while (pq.size()) {
        int x = pq.top().se;
        pq.pop();
        if (st[x]) continue;
        st[x] = 1;
        for (auto [y, w] : g[x])
            if (chmin(dis[y], dis[x] + w)) pq.push({-dis[y], y});
    }
    return dis[end];
}

void solve() {
    cin >> n >> m;
    int s, e; cin >> s >> e;
    rep(m) {
        int u, v, w; cin >> u >> v >> w;
        add(u, v, w), add(v, u, w);
    }
    print(dijkstra(s, e));
}
```
#### [1128. 信使](https://www.acwing.com/problem/content/1130/)
##### 思路
模板题
##### 蒟蒻代码
``` cpp
cint N = 105;

int n, m;
ll dis[N][N];

ll floyd() {
    rep(k, n) rep(i, n) rep(j, n)
        chmin(dis[i][j], dis[i][k] + dis[k][j]);
    return MAX(dis[1], n);
}

void solve() {
    cin >> n >> m;
    rep(i, n) rep(j, n) dis[i][j] = inf<ll>;
    rep(i, n) dis[i][i] = 0;
    rep(m) {
        int u, v, w; cin >> u >> v >> w;
        chmin(dis[u][v], w), chmin(dis[v][u], w);
    }
    ll t = floyd();
    if (t == inf<ll>) print(-1);
    else print(t);
}
```
#### [1127. 香甜的黄油](https://www.acwing.com/problem/content/1129/)
##### 思路
因为奶牛都在牧场，所以 枚举每个牧场作为起点到其他牧场的最短距离，然后对奶牛的数量加权求和就是答案，时间复杂度 最短路是 $O(m\log m)$，一共 $n$ 个牧场，总复杂度是 $O(nm\log m)$
##### 蒟蒻代码
``` cpp
cint N = 808;

ll n, f, m, cow[N];
vpii g[N];

void add(int u, int v, int w) { g[u].push_back({v, w}); }
ll dijkstra(int farm) {
    ll dis[N];
    bitset<N> st;
    priority_queue<PII> pq;
    rep(i, f) dis[i] = inf<ll>;
    dis[farm] = 0, pq.push({0, farm});
    while (pq.size()) {
        int x = pq.top().se;
        pq.pop();
        if (st[x]) continue;
        st[x] = 1;
        for (auto [y, w] : g[x])
            if (chmin(dis[y], dis[x] + w))
                pq.push({-dis[y], y});
    }
    ll sum = 0ll;
    rep(i, f) sum += dis[i] * cow[i];
    return sum;
}

void solve() {
    cin >> n >> f >> m;
    rep(i, n) {
        int t;
        cin >> t;
        cow[t]++;
    }
    rep(m) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w), add(v, u, w);
    }
    ll ans = inf<ll>;
    rep(i, f) chmin(ans, dijkstra(i));
    print(ans);
}
```
#### [1126. 最小花费](https://www.acwing.com/problem/content/1128/)
##### 思路
肯定希望手续费越少越好，所以每次转账实际上剩下的钱是1-手续费，所以按照这个来建边，然后我们希望最后能留下的钱的比例是最大的，所以跑一个最长路，时间复杂度是 $O(m\log m)$
##### 蒟蒻代码
``` cpp
cint N = 2005;

int n, m, aa, bb;
vc<pair<int, double>> g[N];
double dis[N];
bitset<N> st;

void add(int u, int v, double w) { g[u].push_back({v, w}); }
void dijkstra() {
    rep(i, n) dis[i] = 0.0;
    priority_queue<pair<double, int>> pq;
    dis[aa] = 1.0, pq.push({1.0, aa});
    while (pq.size()) {
        int u = pq.top().se; pq.pop();
        if (st[u]) continue;
        st[u] = 1;
        for (auto [v, w] : g[u])
            if (chmax(dis[v], dis[u] * w)) pq.push({dis[v], v});
    }
}
void solve() {
    cin >> n >> m;
    rep(m) {
        int u, v, w; cin >> u >> v >> w;
        double t = (double)(100 - w) / 100.0;
        add(u, v, t), add(v, u, t);
    }
    cin >> aa >> bb;
    dijkstra();
    print(100.0 / dis[bb]);
}
```
#### [920. 最优乘车](https://www.acwing.com/problem/content/922/)
##### 思路
逆天建图，我们考虑乘坐车的次数，而不是换乘的次数，因为换乘的次数相当于乘坐车的次数-1. 于是，在同一条路线上的点，边权就是1，然后直接这样建图，由于这个图的边权全为1，于是用bfs求最短路即可。
##### 蒟蒻代码
``` cpp
cint N = 505, M = 105;

int n, m;
bool g[N][N];
int dis[N];
bitset<N> st;

void bfs() {
    queue<int> q;
    q.push(1), dis[1] = 0;
    while (q.size()) {
        int t = q.front();
        q.pop();
        rep(i, n) if (!st[i] && g[t][i])
            dis[i] = dis[t] + 1,
            st[i] = 1, q.push(i);
    }
}

void solve() {
    cin >> m >> n;
    string line;
    int p;
    getline(cin, line);
    rep(m) {
        vi t;
        getline(cin, line);
        istringstream iss(line);
        while (iss >> p) t.push_back(p);
        rp(i, 0, t.size()) rp(j, i + 1, t.size()) g[t[i]][t[j]] = 1;
    }
    rep(i, n) dis[i] = inf<int>;
    bfs();
    if (dis[n] == inf<int>) print("NO");
    else print(dis[n] - 1);
}
```
#### [903. 昂贵的聘礼](https://www.acwing.com/problem/content/905/)
##### 思路
实际上是**求多源点，一个目标点的最短路，我们可以考虑新建一个虚拟原点**，到每个点的距离为他的点权，然后从这个点做dijkstra即可

注意要枚举区间，因为**不能保证酋长的等级是最高的**
##### 蒟蒻代码
``` cpp
cint N = 105;

int n, m;
vpii g[N];
int grade[N];
int ans = inf<int>;

void add(int u, int v, int w) { g[u].push_back({v, w}); }
int dijkstra(int l, int r) {
    int dis[N];
    bitset<N> st;
    rep(i, n) dis[i] = inf<int>;
    priority_queue<PII> pq;
    dis[0] = 0, pq.push({0, 0});
    while (pq.size()) {
        int u = pq.top().se;
        pq.pop();
        for (auto [v, w] : g[u])
            if (grade[v] >= l && grade[v] <= r && chmin(dis[v], dis[u] + w))
                pq.push({-dis[v], v});
    }
    return dis[1];
}
void solve() {
    cin >> m >> n;
    rep(i, n) {
        int price, cnt;
        cin >> price >> grade[i] >> cnt;
        rep(cnt) {
            int u, w;
            cin >> u >> w;
            add(u, i, w);
        }
        add(0, i, price);
    }
    rep(l, grade[1] - m, grade[1] + m) chmin(ans, dijkstra(l, l + m));
    print(ans);
}
```
#### [1135. 新年好](https://www.acwing.com/problem/content/1137/)
##### 思路
把每个车站看成一个点，然后因为只有5个亲戚，加上自己一定从家也就是1出发，一共6个点，然后可以预处理给每个点跑一遍单源最短路，最后枚举一下2-6的全排列，也就是访问的顺序即可，时间复杂度 $O(5!+6\cdot m\log n)$
##### 蒟蒻代码
``` cpp
cint N = 5e4 + 5;

int n, m, sta[7], dis[7][N];
vpii g[N];
int ord[7];
int ans = inf<int>;
bitset<7> used;

void add(int u, int v, int w) { g[u].push_back({v, w}); }
void dijkstra(int start, int *d) {
    rep(i, n) d[i] = inf<int>;
    bitset<N> st;
    priority_queue<PII> pq;
    d[start] = 0, pq.push({0, start});
    while (pq.size()) {
        int u = pq.top().se;
        pq.pop();
        if (st[u]) continue;
        st[u] = 1;
        for (auto [v, w] : g[u])
            if (chmin(d[v], d[u] + w))
                pq.push({-d[v], v});
    }
}

void dfs(int u) {
    if (u == 7) {
        int t = 0;
        rep(i, 5) t += dis[ord[i]][sta[ord[i + 1]]];
        chmin(ans, t);
    }
    rep(i, 2, 6) {
        if (used[i]) continue;
        used[i] = 1, ord[u] = i;
        dfs(u + 1);
        used[i] = 0;
    }
}

void solve() {
    cin >> n >> m;
    sta[1] = 1;
    rep(i, 2, 6) cin >> sta[i];
    rep(m) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w), add(v, u, w);
    }
    rep(i, 6) dijkstra(sta[i], dis[i]);
    ord[1] = 1;
    dfs(2);
    print(ans);
}
```
#### [340. 通信线路](https://www.acwing.com/problem/content/342/)
##### 思路
题意就是，一张图，对于一条路径定义他的长度是路径边权的第k+1大的数字，求起点到终点的最短路，也就是让第k+1大的数字最小。

于是我们考虑使用二分，假设最终花费是x的话，显然x大于某个值的时候是一定成立的，小于某个值一定不成立。至于如何判断，就是说我找的**路径上，超过x的边最多只有k条**，于是我二分判断的时候，可以把大于x的边边权看成1，其他的看成0，然后看起点到终点的最短路是不是小于等于k，也就是存在一个路径，我可以让x成为真正的花费ovo，判断变成了0-1图最短路，使用双端队列bfs时间复杂度是 $O(m)$，整体的时间复杂度是 $O(m\log L)$

注意这边右侧边界是1e6+1因为，有可能无解，为了区分1e6和无解，我们要用一个大于1e6的数字作为边界。
##### 蒟蒻代码
``` cpp
cint N = 1005;

int n, p, k, dis[N];
vpii g[N];

void add(int u, int v, int w) { g[u].push_back({v, w}); }

bool check(int x) {
    rep(i, n) dis[i] = inf<int>;
    bitset<N> st;
    deque<int> dq;
    dis[1] = 0, dq.push_back(1);
    while (dq.size()) {
        int u = dq.front();
        dq.pop_front();
        if (u == n) break;
        if (st[u]) continue;
        st[u] = 1;
        for (auto [v, w] : g[u])
            if (chmin(dis[v], dis[u] + (w > x))) {
                if (w <= x) dq.push_front(v);
                else dq.push_back(v);
            }
    }

    return dis[n] <= k;
}

void solve() {
    cin >> n >> p >> k;
    rep(i, p) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w), add(v, u, w);
    }
    int l = 0, r = 1e6 + 1;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    if (l == 1e6 + 1) print(-1);
    else print(l);
}
```

#### [342. 道路与航线](https://www.acwing.com/problem/content/344/)
##### 思路
由于有负权边的存在，所以不能用堆优化的dij，但是spfa的时间复杂度又过不了。注意到负权边是有向的，而且是无环的，所以我们可以把仅用道路联通的块看成一个团，然后，这些团的外部仅由水路相连，于是这些团存在拓扑序，而我们知道利用拓扑序我们可以线性dp求最短路。于是，这题我们可以先求出每个联通块，然后在每个联通块内部跑dij，对于块之间可以利用拓扑序直接转移。拓扑序的入度的维护放在dij里面，因为我是以块作为单位整体考虑的入度，所以它理应考虑的是别的块里面所有点对他的影响。然后注意在dij放入优先队列判断的时候，只有在同一个块里面的才能放入，块之间的只能更新，不能放进去。
##### 蒟蒻代码
``` cpp
cint N = 25005, M = 5e4 + 5;

int n, mr, mw, S, bcnt, id[N], dis[N], in[N];
vi block[N];
vpii g[N];
queue<int> q;
bitset<N> st;

void add(int u, int v, int w) { g[u].push_back({v, w}); }

void dfs(int u, int bid) {
    id[u] = bid;
    block[bid].push_back(u);
    for (auto [v, _] : g[u])
        if (!id[v]) dfs(v, bid);
}

void dijkstra(int bid) {
    priority_queue<PII> pq;
    for (auto x : block[bid]) pq.push({-dis[x], x});
    while (pq.size()) {
        int u = pq.top().se;
        pq.pop();
        if (st[u]) continue;
        st[u] = 1;
        for (auto [v, w] : g[u]) {
            if (chmin(dis[v], dis[u] + w)) {
                if (id[u] == id[v]) pq.push({-dis[v], v});
            }
            if (id[u] != id[v] && --in[id[v]] == 0) q.push(id[v]);
        }
    }
}

void topsort() {
    rep(i, bcnt) if (!in[i]) q.push(i);
    while (q.size()) {
        int t = q.front();
        q.pop();
        dijkstra(t);
    }
}

void solve() {
    cin >> n >> mr >> mw >> S;

    rep(i, n) dis[i] = inf<int>;
    dis[S] = 0;

    rep(mr) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w), add(v, u, w);
    }

    rep(i, n) if (!id[i]) dfs(i, ++bcnt);

    rep(mw) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w), in[id[v]]++;
    }

    topsort();

    rep(i, n) {
        if (dis[i] > inf<int> / 2) print("NO PATH");
        else print(dis[i]);
    }
}
```

#### [341. 最优贸易](https://www.acwing.com/problem/content/343/)
##### 思路
感觉其实很多的题解讲的不是很清楚，其实很直觉的一个做法是枚举每个点作为卖出的点，然后减去可能买入的价值的最小值。那么假设当前在 u，哪些可能买入的点可以在 u 卖出呢？首先，这条旅游路线是从1出发的，其次这条路线要能够经过u这个点，注意这里的经过可以是折返的经过，比如： 1->5->6->5，然后用6的价值更新5的最小值，只要对每个点求出可以买入的最小值，那么假设在自己这里卖出，所有答案更新一下就是结果。

那么如何求这个最小值呢？这其实就是一个dp问题，他可以从哪些状态转移过来？转移的路径就是所有终点是u的边，但是我们不能保证这张图是无环的，所以不一定有拓扑序，因此把状态看成点，相当于在有向图上跑最短路。对于有向图跑最短路，可以用dijkstra或者spfa，但是注意到dijkstra要求第一次从某个点更新之后，这个点就一定不会被后续的点进行更新，还是回到刚才的例子：1->5->6->5，显然5在更新6之后，还会被6更新，所以dij的贪心是假的。因此采用spfa，但是考虑这种情况：1的价值是5，2的价值是2，显然如果2有到1的边的话，是可以反向更新1的，但是如果在初始化队列的时候只加入1，那么2因为不会被1更新，因此不会扩展，因此不会反过来更新1，那么如何解决这种跑起来的启动问题呢？一种方法是把与1联通的所有的点在初始化的时候都加入队列，或者给每个点一次机会，如果他是第一次被扩展，那么也给他一次扩展别人的机会，如果她不中用那算了，这样就行了。

还有要注意的点就是，因为题目要求要以n为结束，所以我们之前的spfa保证了经过1，但是没保证经过n，所以建一个反图，然后只更新和n联通的点即可。
##### 部分代码
``` cpp
cint N = 100010;

int n, m, a[N];
vi g[N], gt[N];
int mn[N]; // mn[i]: 1 能到的所有的经过 i 这个点的所有的路径上的点的价值的最小值
int ans = 0;
bitset<N> st;

void add(vi *graph, int u, int v) {
    graph[u].push_back(v);
}

void spfa() {
    queue<int> q;
    bitset<N> inq, init;
    q.push(1), inq[1] = 1;
    while (q.size()) {
        int u = q.front();
        q.pop();
        inq[u] = 0;
        for (int v : g[u]) {
            if (!init[v]) init[v] = 1, q.push(v), inq[v] = 1;
            if (chmin(mn[v], mn[u]) && !inq[v]) q.push(v);
        }
    }
}

void dfs(int u) {
    st[u] = 1;
    chmax(ans, a[u] - mn[u]);
    for (int v : gt[u])
        if (!st[v]) dfs(v);
}

void solve() {
    cin >> n >> m;
    rep(i, n) cin >> a[i], mn[i] = a[i];
    rep(m) {
        int u, v, z;
        cin >> u >> v >> z;
        if (z == 1) add(g, u, v), add(gt, v, u);
        else add(g, u, v), add(g, v, u), add(gt, u, v), add(gt, v, u);
    }
    spfa();
    dfs(n);
    print(ans);
}
```
#### [1137. 选择最佳线路](https://www.acwing.com/problem/content/1139/)
##### 思路
模版题，可以从多个起点选择作为路径起点，给定终点的最短路，如果终点只有一个，可以考虑建反图然后跑SSSP，但是如果有多个终点，更general的做法是建立一个虚拟源点，到每个起点的距离都是0，这样任何从虚拟源点出发的最短路一定一一对应一条从起点出发的最短路，因此这个做法是正确的，时间复杂度是 $O(m\log n)$
##### 蒟蒻代码
``` cpp
cint N = 1005;

int n, m, home, w;

int dij(vpii *g, int start) {
    int dis[N];
    bitset<N> st;
    rep(i, 0, n) dis[i] = inf<int>;
    priority_queue<PII> pq;
    dis[start] = 0, pq.push({0, start});
    while (pq.size()) {
        int u = pq.top().se;
        pq.pop();
        if (st[u]) continue;
        st[u] = 1;
        for (auto [v, w] : g[u])
            if (chmin(dis[v], dis[u] + w)) pq.push({-dis[v], v});
    }
    if (dis[home] == inf<int>) return -1;
    else return dis[home];
}

void solve() {
    while (cin >> n >> m >> home) {
        vpii g[N];
        auto add = [&g](int u, int v, int w) { g[u].push_back({v, w}); };
        rep(m) {
            int u, v, w;
            cin >> u >> v >> w;
            add(u, v, w);
        }
        cin >> w;
        rep(w) {
            int t;
            cin >> t;
            add(0, t, 0);
        }
        print(dij(g, 0));
    }
}
```

#### [1131. 拯救大兵瑞恩](https://www.acwing.com/problem/content/1133/)
##### 思路
如果没有门的话，直接bfs就可以做出来，但是现在问题是有门，那么我们在表示当前状态的时候不仅仅记录当前位置 (x,y) ，还需要记录当前身上的钥匙的种类，把坐标映射成一维pos，携带的钥匙的种类用状态压缩，因此问题就类似dp了，但是显然dp状态之间的依赖关系可能存在环，不是拓扑图，于是考虑使用最短路。显然每次走到要钥匙的格子全部拿起来一定是最优的，并且不消耗时间，所以从状态 dis[pos,state] 到 dis[pos,state|keys] 的边权是0，但是如果从一个格子到另一个格子 dis[pos,state] 到 dis[adjacnt_pos,state] ，边权是1，因为格子之间的转移是要消耗时间的，因此，可以利用最短路求解，同时注意到边权是0-1，因此可以用双端队列bfs，终点是 dis[n\*m,\*] 时间复杂度是 $O(M\cdot 2^{p})$

##### 蒟蒻代码
``` cpp
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
```
#### [1134. 最短路计数](https://www.acwing.com/problem/content/1136/)
##### 思路
可以用dis记录到某个点的最短路径，cnt为该最短路径的次数，如果按照dp的思想，那么就看每条该点的最短路径是由谁转移过来的，然后进行统计就好了。但是问题在于，一般的dp可以线性递推是因为它本身保证了拓扑序，但是我们在统计最短路距离的时候不一定能够有拓扑序，因为路径可能存在环，每个点可能会依赖其他的点。但是在这题里面，由于每条边都是1，因此不会在最短路树加上其他转移的边上有环，所以可以在求最短路的时候统计，但这就要求我们的最短路算法能够保证遍历的顺序是一个拓扑序。那么在bfs，dij，spfa中，只有bfs和dij有这种顺序的性质。在本题中，因为边权全部相同，所以用bfs即可。如果真的有负权边，一定要用spfa那就需要先跑一遍spfa最短路，然后枚举所有边，来手动建最短路树，就是判断这个边的两个端点是不是用这条边维系着最短路，然后再在树上跑拓扑排序就行。【主要是看有最短路径树上有没有环形更新】
##### 蒟蒻代码
``` cpp
cint N = 1e5 + 5;
cint mod = 100003;

int n, m;
vi g[N];
int dis[N], cnt[N];
bitset<N> st;

int add(int x, int y) { return (x + y) % mod; }
void gadd(int u, int v) { g[u].push_back(v); }
void bfs() {
    queue<int> q;
    rep(i, n) dis[i] = inf<int>;
    dis[1] = 0, q.push(1), cnt[1] = 1;
    while (q.size()) {
        int u = q.front();
        q.pop();
        if (st[u]) continue;
        st[u] = 1;
        for (auto v : g[u]) {
            if (dis[v] == dis[u] + 1) cnt[v] = add(cnt[v], cnt[u]);
            if (dis[v] > dis[u] + 1) dis[v] = dis[u] + 1, cnt[v] = cnt[u], q.push(v);
        }
    }
}

void solve() {
    cin >> n >> m;
    rep(m) {
        int u, v;
        cin >> u >> v;
        gadd(u, v), gadd(v, u);
    }
    bfs();
    rep(i, n) print(cnt[i]);
}
```
#### [383. 观光](https://www.acwing.com/problem/content/385/)
##### 思路
与上一题类似，这题是要统计到终点最短路和最短距离+1的路径的数量。我们可以记录 dis[i][0-1] 为起点到i点的最短路和次短路，就是类似拆点的思路，然后更新路径的时候，更新次短路就行。因此，在优先队列中，我们不仅要记录当前的距离和节点的编号，还要记录当前距离的种类是次短还是最短，因为要更新cnt的时候需要用到当前边的cnt。用dij是可以的因为可以证明用dij在最短路树上跑不会有环，也就是循环依赖。

##### 蒟蒻代码
``` cpp
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
```


#### [1125. 牛的旅行](https://www.acwing.com/problem/content/1127/)
##### 思路

##### 蒟蒻代码
``` cpp
cint N = 155;

int n, x[N], y[N];
double dis[N][N], mx[N];
double get(int u, int v) {
    int dx = x[u] - x[v], dy = y[u] - y[v];
    return sqrt(dx * dx + dy * dy);
}
void floyd() {
    rep(k, n) rep(i, n) rep(j, n) chmin(dis[i][j], dis[i][k] + dis[k][j]);
}
void solve() {
    cin >> n;
    rep(i, n) rep(j, n) dis[i][j] = i == j ? 0 : inf<double>;
    rep(i, n) cin >> x[i] >> y[i];
    string line;
    getline(cin, line);
    rep(i, n) {
        getline(cin, line);
        assert(line.size() == n);
        rp(j, 0, line.size()) {
            bool flg = line[j] - '0';
            if (flg) dis[i][j + 1] = get(i, j + 1);
        }
    }
    floyd();
    double ans1 = 0;
    rep(i, n) rep(j, n) if (dis[i][j] != inf<double>) chmax(mx[i], dis[i][j]), chmax(ans1, mx[i]);
    double ans = inf<double>;
    rep(i, n) rep(j, n) if (dis[i][j] == inf<double>) chmin(ans, mx[i] + mx[j] + get(i, j));
    chmax(ans, ans1);
    print(ans);
}
```

