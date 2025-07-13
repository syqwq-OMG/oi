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
  - 恰好经过k条边的最短路（倍增·快速幂·邻接矩阵乘法）
  - 一定要理解floyd本质是有dp的成分在里面的，所以遇到的题目也可以考虑floyd的本来的推导，提供思路。
#### 最小生成树
- **任意一棵最小生成树一定包含无向图中权值最小的边**。
证明：假设不包含最小的边，那么在树中加上这条边会构成一个环，此时，用最小边替换环上任意一条边，都可以得到更优解，矛盾。所以一定包含最小的边
- 无向图联通块可以缩点，然后在联通块之间跑mst
- prim算法
  - 朴素版本（邻接矩阵） $O(n^{2})$
  - 维护一个已经在mst中的集合，每次贪心加入**到这个集合距离最短的点**。
  - 堆优化版本
- kruskal算法 
  - 直接存边
  - 时间复杂度 $O(m\log m)$
- **（严格）次小生成树**
  - 把图的所有生成树按照权值大小进行排序，第二小的为次小生成树。
  - 方法1：先求mst，再枚举删除mst中的边，再在剩余的边中做一遍mst，时间复杂度 $O(m\log m + nm)$，不太好求严格次小生成树
  - 方法2：先求mst，然后依次枚举非树边，将该边加入树中，同时从树中去掉一条边，使得最终的图仍是一棵树，则一定可以求出次小生成树。时间复杂度 $O(m+n^{2}+m\log m)$，数据结构可以优化求树上两点间最长边的大小的时间复杂度
  - 次小生成树一定在mst的邻集中
#### 负环
- 会和01分数规划在一起
- 存在一个环路，使得这一圈的边权之和小于0
- 一般使用spfa算法（**假设一共有 n个点**）
  - 统计每个点入队的次数，如果某个点入队n次，则说明存在负环（等价于bellman ford算法，n条边，有n+1个点，则必然存在环）
  - 统计当前每个点的最短路中所包含的边的数量，如果某个点的大于等于n，则也说明存在负环（有n+1个点，则必然存在环）
- 如果原图可能不连通，那么**将所有点入队，并且将dis初始化成0**，这是因为可以构造一个虚拟源点，如果原图有负环，那么新图一定也有负环，且新图中的负环一定是从虚拟源点走到的
- 理论上是 $O(m)$，但实际上可能是 $O(nm)$，所以经验之谈，当所有点的入队次数超过一个阈值（比如2n）我们就认为图中有很大可能存在负环；也可以把spfa中的队列换成栈
#### 差分约束
- 可以求不等式组的可行解，每个不等式形如 $x_i \le x_j + c_k$
- 如何求最大值或者最小值
- 考虑求$x_i \le x_j + c_k$，那么假设有一个原点，在一张图上跑最短路，我们如果有一条从 j -> i的长度为c的边，那么如果图中没有负环，则一定有 $d[i] \le  d[j]+ c_k$ 因为松弛操作，如果不满足这个条件，那么经过松弛也一定会满足。那么**源点要满足：从源点出发，一定可以到达所有的边**，因为只有能遍历到的边，才会进行松弛操作，最后满足这个不等式。
- 求可行解的步骤：
  - > 1 把每个x[i] ≤ x[j] + C[k]不等式转化为一条从x[j]走到x[i]长度为C[k]的边
    > 2 然后在这个图上找一个超级源点,使得该源点一定可以遍历到所有边 
    > 3 从源点求一遍 单源最短路
    > 3.1 假如存在负环
      不等式无解 <=> 存在负环
    > 4 求完单源最短路之后
    > 4.1 存在负环 => 不等式无解
    > 4.2 没有负环 => 求完之后一定是满足这个不等式的 <=> 即一个可行解
- 也可以使用最长路，也就是 $d[i]\ge d[j]+c_k$，就是改变一下不等式建图的方向和边权，那么无解就等价于正环
- 求最小的可行解和最大的可行解（这里的最值是每个变量的最值）：**如果求的是最小值，则应该求最长路，如果求的是最大值，则应该求最短路**。比如求最小值，那么必然有一种条件比如 $x_1\ge 0$ 如何把这种不等式变成一条边呢？$x_i \le c$ ，建立一个虚拟源点0，那么就是 $x_i \le  0+c$ ，于是建立从 0 到 i的边即可。**如果求的是最大值**，比如 $x_i \le  x_j +c_1 \le  x_k + c_2+c_3 \le  \cdots \le  0+\sum c$所以我们要考虑所有这样的从 $x_i$ 出发的不等式链，然后取最后终点所计算出的**上界的最小值**。这其中每一条不等式链，都是从0出发走到 $x_i$ 的一条路径。

#### 最近公共祖先
- 在一棵有根树中，给定两个点，他们的共同祖先中距离他们最近的祖先。
- 求法：
  - **向上标记法：** 从一个点往上走直到根并标记所有的祖先，然后另一点往上走，走到的第一个标记过的点就是lca $O(n)$
  - **倍增法**：预处理数组 $f[i,j]$ 从 $i$ 开始向上走 $2^{j}$ 能够到达点节点，则 $0\le  j \le  \log n$，容易得到状态转移方程是 $f[i,0]=\text{father of }i$, $f[i,j]=f[f[i,j-1],j-1]$，预处理第二个数组 $d[i]$ 表示每个点的深度，就是每个点到根节点的距离+1。具体求lca的时候分两步：1、先将两个点跳到同一层，基于二进制拼凑的思想，就是用 $f$ 数组拼凑出 $d[x]-d[y]$ （这里假设x的深度大于y的），其实就是看 $d[f[i,k]] > d[y]$ 是否 成立，如果成立就可以继续跳 2、让两个点同时往上跳，一直跳到他们lca的下一层，因为这样可以更好判断是否是lca而不是仅仅是公共祖先，就是如果单单只有 $f[x,k]=f[y,k]$ 不能确认是否是最近的公共祖先，那么此时他们的lca就是 $f[k,0]$，所以**预处理 $O(n\log n)$，每次查询的时间复杂度是 $O(\log n)$**，哨兵：如果从 $i$ 跳 $2^{j}$ 跳出了根节点，那么 $f[i,j]=0, d[0]=0$
  - **tarjan离线求lca**：时间复杂度可以做到 $O(n+m)$，本质上是对向上标记法的一个优化。
  > 将遍历过程中遇到的所有节点划分为三类，标记数组为st[N]
    1> st[u] = 0, 代表节点u还未被遍历到
    2> st[u] = 1, 代表节点u被遍历到，但还 未回溯/未完成以i为根节点的子树的遍历
    3> st[u] = 2, 代表节点u被遍历到，同时 完成了回溯/完成了以i为根节点的子树的遍历
    > part2:
    引入并查集p[N]，初始时p[i] = i
    p[i]记录了节点i往上回溯寻找满足st[j] == 2的节点的过程中能够抵达的最上层的节点的父节点编号
    > part3:
    引入vector<pair<int, int>> query[N]
    query[u].first 与 u 共同组成查询编号为query[u].second的查询记录
    查询编号为k代表这条查询记录是输入数据中的第k条查询
    > part4:
    任选一个节点为根节点root(如 root = 1)
    dist[i]记录节点i到root的距离，可由一次简单的dfs得到
    > part5:
    当st[u] == 1时，记(u, v)为一条查询，且st[v] == 2
    查询结果：dist[u] + dist[v] - 2 * dist[find(v)]
    > 一定要在回溯的时候设爹，因为本质上找的是一个点的所有祖宗里面第一个被标记为1的点，那回溯的时候设爹，就意味着只有标记为2的点是有爹的，那么没设的，也就是并查集的代表元一定是被标记为1的点
- 树上两点间的最短距离：$d[x]+d[y]-2d[\operatorname{lca}(x,y)]$



#### 有向图的强联通分量
- 对于一个有向图，联通分量：对于分量中的任意两点u和v，u可以到v，v也可以到u
- 强联通分量指的是极大的联通分量，就是加上任意的点后，都不是联通分量
- 强联通分量可以缩点，进而将任何一个有向图转化成一个DAG（拓扑图）
- 缩点就是将所有的联通分量变成一个点
- 对于任意源 x，从它出发进行 DFS，每个点只访问一次，所有发生递归的边会形成以 x
 为根的 搜索树。在此过程中，按第一次到达的时间顺序，给每个点标记 时间戳，记 dfn[x]
- 可以将图中的边分为四类：
  - 树枝边： 搜索树中的边父亲节点指向儿子节点
  - 前向边：x指向他的祖先节点y
  - 后向边：x是y的祖先节点，且x指向y
  - 横叉边：除了以上三种边，且满足 `dfn[y]<dfn[x]`
- 求法：
  - low[x] 表示x的能遍历到的节点中，时间戳的最小值
  - Tarjan 算法 在 DFS 过程中维护一个栈存储以上节点，定义 low[x]为 x所在 SCC 根的 dfn，通过以下过程维护它
    > 当 x被初次访问时，将它入栈，令 low[x]=dfn[x]遍历 x的所有出边 (x,y)
    > 若 y未被访问，递归访问它，回溯后，令 low[x]=min(low[x],low[y])，因为 y能回溯到的点，x经由 y也能到达
    > 若 y已被访问且在栈中，令 low[x]=min(low[x],dfn[y])从 x回溯前，若 low[x]=dfn[x]，说明 x是当前 SCC 的根，因为它是 SCC 中第一个被访问的点，low值最小，不会被更新.由于每个点和每条边只访问一次，因此 Tarjan 求 SCC 的时间复杂度为线性
- 缩点：
  ``` cpp
  for v in V:
    for (v, u):
        if id[v] != id[u]:  // id 是 点所在scc的编号
            add_edge(id[v], id[u])
  ```
- 按 SCC 编号递减顺序遍历，就是 拓扑序

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
枚举到底在哪两个点之间加边，预处理任意两点的最短距离，分别求每个点最远的点的距离，然后答案应该是最大直径，和加完边之后的最小值的最大值。就是注意到底哪个是最大值，哪个是最小值，一定要想清楚。

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

#### [343. 排序](https://www.acwing.com/problem/content/345/)
##### 思路
floyd进行传递闭包，每次传入一个新关系的时候，跑一次，看看是否可以确定或者是矛盾，输出最后偏序关系的时候只要每次在没选过的元素找到最小值即可。时间复杂度 $O(n^{3}m)$

但是注意到，每次更新新的关系的时候，只需要更新这条边会影响到的关系，所以每次可以枚举可能会影响到的关系，整体时间复杂度可以降为 $O(n^{2}m)$
##### 蒟蒻代码
``` cpp
cint N = 26;

int n, m;
bool g[N][N], d[N][N];
bool st[N];

void floyd() {
    rp(i, 0, n) rp(j, 0, n) d[i][j] = g[i][j];
    rp(k, 0, n) rp(i, 0, n) rp(j, 0, n) d[i][j] |= d[i][k] & d[k][j];
}

int check() {
    rp(i, 0, n) if (d[i][i]) return 2;
    rp(i, 0, n) rp(j, 0, i) if (!d[i][j] && !d[j][i]) return 0;
    return 1;
}

char get_min() {
    rp(i, 0, n) {
        if (st[i]) continue;
        bool flg = 1;
        rp(j, 0, n) {
            if (!st[j] && d[j][i]) {
                flg = 0;
                break;
            }
        }
        if (flg) {
            st[i] = 1;
            return 'A' + i;
        }
    }
    return '0';
}

void oho() {
    mset(g, 0), mset(d, 0);
    int type = 0, rd;
    char c[5];
    rep(i, m) {
        cin >> c;
        int a = c[0] - 'A', b = c[2] - 'A';
        if (!type) {
            g[a][b] = d[a][b] = 1;
            // floyd();
            // u->a->b->v
            rp(u, 0, n) d[u][b] |= d[u][a], d[a][u] |= d[b][u];
            rp(u, 0, n) rp(v, 0, n) d[u][v] |= d[u][a] & d[b][v];
            type = check();
            if (type) rd = i;
        }
    }
    if (!type) return print("Sorted sequence cannot be determined.");
    if (type == 2) return print("Inconsistency found after", rd, "relations.");
    mset(st, 0);
    cout << "Sorted sequence determined after " << rd << " relations: ";
    rep(n) wt(get_min());
    print(".");
}

void solve() {
    while (cin >> n >> m, n || m) oho();
}
```

#### [344. 观光之旅](https://www.acwing.com/problem/content/346/)
##### 思路
因为所有的边都是正的，所以不会考虑有重复节点的情况，因为一定不是最优的。
因为也是最优化问题，所以也考虑使用集合划分的思想。考虑**按照环上编号最大的点的编号（也就是不超过k）来分类**，然后最后的答案就是环上最大点不超过n的答案。
floyd中 $d[i,j]$ 表示 **经过的最大点**（就是路径中的不包括端点的点集）不超过 k 的时候，i j之间的最短路径，那么我们在求最小环的第k个阶段的时候，可以枚举任意两个点，和k构成的环，环的大小也就是 $w[i,k]+w[k,j]+d[i,j]$，因为d中在没更新之前，存储的实际上是 $d[k-1,i,j]$ 。
最后，为了输出路径，我们可以考虑用一个pos数组，在进行relax操作的时候，记录中间转移的节点的编号，也就是两点中间的最短路径中经过的最大节点的编号，由于考虑到这个pos中两段部分可能还有中间点，所以在输出路径的时候只要递归操作就行。
##### 蒟蒻代码
``` cpp
cint N = 105;

int n, m;
ll g[N][N], d[N][N], pos[N][N];
ll ans = inf<ll>;
vi path;

void get(ll u, ll v) {
    ll t = pos[u][v];
    if (!t) return;
    get(u, t), path.push_back(t), get(t, v);
}
void floyd() {
    rep(k, n) {
        rep(i, k - 1) rep(j, i + 1, k - 1) {
            if (chmin(ans, d[i][j] + g[i][k] + g[k][j])) {
                path.clear();
                path.push_back(i), get(i, j), path.push_back(j), path.push_back(k);
            }
        }
        rep(i, n) rep(j, n) if (chmin(d[i][j], d[i][k] + d[k][j])) pos[i][j] = k;
    }
}                  
void solve() {
    cin >> n >> m;
    rep(i, n) rep(j, n) d[i][j] = g[i][j] = inf<ll>;
    rep(m) {
        ll u, v, w;
        cin >> u >> v >> w;
        chmin(g[u][v], w);
        g[v][u] = d[u][v] = d[v][u] = g[u][v];
    }
    floyd();
    if (ans == inf<ll>) print("No solution.");
    for (auto x : path) cout << x << " ";
}
```
#### [345. 牛站](https://www.acwing.com/problem/content/347/)
##### 思路
在floyd算法中，$d[k,i,j]$表示点是从i到j，中间只经过1～k的最短距离。在此题中考虑，$d[k,i,j]$表示i到j经过恰好k条边到最短距离，于是很容易得到 $d[a+b,i,j]=\min \{ d[a,i,k]+d[b,k,j] \}$，而我们求的就是 $d[N,S,E]$，于是这是另一种floyd的变体。而我们考虑对于刚好经过k条边两点的最短距离实际上可以通过邻接矩阵的幂来表示，并且对于最短路径，前面与后面是完全独立的，所以可以考虑使用快速幂，然后用二进制拼接的方法来得到最终的答案。这种方法的时间复杂度是 $O(n^{3}\log N)$，并且可以处理有负环的情况，因为限制了最多经过的边的条数。
做快速幂的时候，res中存的应该是单位元，在这里就是经过0条边的dis。但是g种一开始存的应该是经过1条边的dis，所以对角线不应该初始化成0.
##### 蒟蒻代码
``` cpp
cint N = 205;

ll n, m, k, S, E;
ll g[N][N], res[N][N];
unordered_map<ll, ll> mp;

void mul(ll C[][N], ll A[][N], ll B[][N]) {
    static ll tmp[N][N];
    mset(tmp, 0x3f);
    rep(i, n) rep(j, n) rep(k, n) chmin(tmp[i][j], A[i][k] + B[k][j]);
    memcpy(C, tmp, sizeof tmp);
}

void qmi() {
    mset(res, 0x3f);
    rep(i, 200) res[i][i] = 0;
    while (k) {
        if (k & 1) mul(res, res, g);
        mul(g, g, g), k >>= 1;
    }
}

void solve() {
    mset(g, 0x3f);
    cin >> k >> m >> S >> E;
    if (!mp.count(S)) mp[S] = ++n;
    if (!mp.count(E)) mp[E] = ++n;
    S = mp[S], E = mp[E];
    rep(m) {
        ll u, v, w;
        cin >> w >> u >> v;
        if (!mp.count(u)) mp[u] = ++n;
        if (!mp.count(v)) mp[v] = ++n;
        u = mp[u], v = mp[v];
        g[u][v] = g[v][u] = min(g[u][v], w);
    }
    qmi();
    print(res[S][E]);
}
```
#### [1140. 最短网络](https://www.acwing.com/problem/content/1142/)
##### 思路
最小生成树prim模版：维护一个已经在mst中的集合，每次贪心加入距离这个集合距离最短的点。
##### 蒟蒻代码
``` cpp
cint N = 105;

ll n;
ll g[N][N], dis[N];
bitset<N> st;

ll prim() {
    rep(i, n) dis[i] = inf<ll>;
    ll ans = 0ll;
    dis[1] = 0;
    rep(n) {
        ll t = -1;
        rep(i, n) {
            if (st[i]) continue;
            if (t == -1 || dis[i] < dis[t]) t = i;
        }
        ans += dis[t], st[t] = 1;
        rep(i, n) {
            if (st[i]) continue;
            chmin(dis[i], g[i][t]);
        }
    }
    return ans;
}
void solve() {
    cin >> n;
    rep(i, n) rep(j, n) cin >> g[i][j];
    print(prim());
}
```
#### [1141. 局域网](https://www.acwing.com/problem/content/1143/)
##### 思路
在每个联通块内部求mst，使用kruskal算法就行。
##### 蒟蒻代码
``` cpp
struct rec {
    int u, v, w;
};
cint N = 105, M = 205;
int n, m;
int sum = 0, mst = 0;
int fa[N];
rec edge[M];
int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }
void merge(int x, int y) { fa[get(x)] = get(y); }
void solve() {
    cin >> n >> m;
    rep(i, n) fa[i] = i;
    rep(i, m) {
        int u, v, w;
        cin >> u >> v >> w;
        sum += w, edge[i] = {u, v, w};
    }
    sort(all(edge, m), [](auto x, auto y) {
        return x.w < y.w;
    });
    rep(i, m) {
        auto [u, v, w] = edge[i];
        int x = get(u), y = get(v);
        if (x == y) continue;
        mst += w, merge(x, y);
    }
    print(sum - mst);
}
```
#### [1142. 繁忙的都市](https://www.acwing.com/problem/content/description/1144/)
##### 思路
可以使用二分，也可以直接使用kruskal。因为按照边权大小进行排序，那么，如果两点没有联通，按照贪心选出来的这条边一定不会更劣，因为如果这条边没有选出来，那么最后可以把这条边加上，构成一个环，对于环上任意一条边，用它替换，一定是更优解，因为仍然是一棵树。矛盾，所以贪心的策略是正确的。
##### 蒟蒻代码
``` cpp
struct rec {
    int u, v, w;
};
cint N = 305, M = 8005;

int n, m;
int fa[N];
rec edge[M];

int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }
void merge(int x, int y) { fa[get(x)] = get(y); }
void solve() {
    cin >> n >> m;
    rep(i, n) fa[i] = i;
    rep(i, m) {
        int u, v, w;
        cin >> u >> v >> w;
        edge[i] = {u, v, w};
    }
    int ans = 0;
    sort(all(edge, m), [](auto x, auto y) { return x.w < y.w; });
    rep(i, m) {
        auto [u, v, w] = edge[i];
        int x = get(u), y = get(v);
        if (x == y) continue;
        chmax(ans, w), merge(x, y);
    }
    print(n - 1, ans);
}
```
#### [1143. 联络员](https://www.acwing.com/problem/content/1145/)
##### 思路
必须要用的边直接加到mst中（缩点），剩下的继续kruskal
##### 蒟蒻代码
``` cpp
struct vec {
    int u, v, w;
};
cint N = 2005, M = 10005;

int n, m;
int fa[N];
int cnt = 0, ans = 0;
vec edge[M];
int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }
void merge(int x, int y) { fa[get(x)] = get(y); }
void solve() {
    cin >> n >> m;
    rep(i, n) fa[i] = i;
    rep(m) {
        int p, u, v, w;
        cin >> p >> u >> v >> w;
        if (p == 1) {
            ans += w;
            merge(u, v);
        } else {
            edge[++cnt] = {u, v, w};
        }
    }
    sort(all(edge, cnt), [](auto x, auto y) { return x.w < y.w; });
    rep(i, cnt) {
        auto [u, v, w] = edge[i];
        int x = get(u), y = get(v);
        if (x != y) ans += w, merge(x, y);
    }
    print(ans);
}
```
#### [1144. 连接格点](https://www.acwing.com/problem/content/1146/)
##### 思路
每个格点看成一个点，然后手动建图即可，已经联通的点既可以直接放到一个并查集里面，也可以设为边权为0的边。注意因为边权都是正的，所以才是最小生成树，如果边权可以是负的，不一定是最小生成树，比如所有边权都为负的完全图。
##### 蒟蒻代码
``` cpp
struct vec {
    int u, v, w;
};
cint N = 1005, M = N * N;

int n, m, ans;
int cnt;
int fa[M];
vec edge[M << 2];
int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};

int pos(int x, int y) { return (x - 1) * m + y; }
bool valid(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= m; }
int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }
void merge(int x, int y) { fa[get(x)] = get(y); }
void solve() {
    cin >> n >> m;
    rep(i, n * m) fa[i] = i;
    int x1, x2, y1, y2;
    while (cin >> x1 >> y1 >> x2 >> y2) edge[++cnt] = {pos(x1, y1), pos(x2, y2), 0};
    rep(i, n) rep(j, m) rep(k, 0, 3) {
        int x = i + dx[k], y = j + dy[k];
        int p1 = pos(i, j), p2 = pos(x, y);
        if (valid(x, y)) edge[++cnt] = {p1, p2, dx[k] ? 1 : 2};
    }
    sort(all(edge, cnt), [](auto x, auto y) { return x.w < y.w; });
    rep(i, cnt) {
        auto [u, v, w] = edge[i];
        int x = get(u), y = get(v);
        if (x != y) ans += w, merge(x, y);
    }
    print(ans);
}
```
#### [1146. 新的开始](https://www.acwing.com/problem/content/1148/)
##### 思路
感觉就是点权的一种处理方式，就是建立虚拟源点，然后连边变成边权
##### 蒟蒻代码
``` cpp
cint N = 305;

int n, g[N][N];
int dis[N];
bitset<N> st;
ll prim() {
    rep(i, 0, n) dis[i] = inf<int>;
    ll ans = 0;
    dis[0] = 0;
    rep(n + 1) {
        int t = -1;
        rep(i, 0, n) if (!st[i] && (t == -1 || dis[i] < dis[t])) t = i;
        st[t] = 1, ans += dis[t];
        rep(i, n) chmin(dis[i], g[t][i]);
    }
    return ans;
}
void solve() {
    cin >> n;
    rep(i, n) { cin >> g[0][i], g[i][0] = g[0][i]; }
    rep(i, n) rep(j, n) cin >> g[i][j];
    print(prim());
}
```
#### [1145. 北极通讯网络](https://www.acwing.com/problem/content/1147/)
##### 思路
就是把mst中按照边权大小排序的后k条边去掉就行
##### 蒟蒻代码
``` cpp
struct node {
    ll u, v, w;
};
cint N = 505, M = N * N;

ll n, k;
ll x[N], y[N];
ll fa[N];
ll cnt = 0;
node edge[M];

ll dist(ll a, ll b) {
    ll dx = x[a] - x[b], dy = y[a] - y[b];
    return dx * dx + dy * dy;
}
ll get(ll a) { return fa[a] == a ? a : fa[a] = get(fa[a]); }
void merge(ll a, ll b) { fa[get(a)] = get(b); }
void solve() {
    cin >> n >> k;
    rep(i, n) fa[i] = i;
    rep(i, n) cin >> x[i] >> y[i];
    rep(i, n) rep(j, n) if (i != j) edge[++cnt] = {i, j, dist(i, j)};
    ll mx = 0;
    sort(all(edge, cnt), [](auto a, auto b) { return a.w < b.w; });
    ll used = 0;
    rep(i, cnt) {
        if (used >= n - k) break;
        auto [u, v, w] = edge[i];
        ll a = get(u), b = get(v);
        if (a == b) continue;
        merge(a, b), chmax(mx, w), used++;
    }
    print(sqrt(mx));
}
```
#### [346. 走廊泼水节](https://www.acwing.com/problem/content/348/)
##### 思路
其实，intuition比较容易想到，就是考虑kruskal的过程，其实可以看成是把连通块进行缩点之后，再选择一条边权最短的边，而完全图要求连通块内部的边的数量是饱和的，所以，只要满足每次弄出来的连通块内部的边都比选的边要大就行，因为是最小值，所以只要大1就行，然后每次在进行连通块合并的时候进行加这些用来使得他饱和的边即可。
##### 蒟蒻代码
``` cpp
struct node {
    int u, v, w;
};
cint N = 6005;

int n;
int fa[N];
int sz[N];
node edge[N];
int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }
void solve() {
    cin >> n;
    rep(i, n) fa[i] = i, sz[i] = 1;
    rep(i, n - 1) {
        int u, v, w;
        cin >> u >> v >> w;
        edge[i] = {u, v, w};
    }
    sort(all(edge, n - 1), [](auto x, auto y) { return x.w < y.w; });
    ll ans = 0;
    rep(i, n - 1) {
        auto [u, v, w] = edge[i];
        int x = get(u), y = get(v);
        if (x == y) continue;
        ans += 1ll * (sz[x] * sz[y] - 1) * (w + 1);
        fa[x] = y, sz[y] += sz[x];
    }
    print(ans);
}
```
#### [1148. 秘密的牛奶运输](https://www.acwing.com/problem/content/description/1150/)
##### 思路
严格次小生成树模板题。
- 求最小生成树，统计标记每条边是否是树边；同时把最小生成树建立，权值之和为sum
- 预处理生成树中任意两点间的边权最大值dist1[a][b]和长度次大dist2[a][b]（树中两点路径唯一，dfs）
- 依次枚举所有非MST边t，边t连接a，b,权为w。显然a，b在MST中。尝试用t替换a-b的路径中最大的一条边A，A权为a。w > a。（若w < a,t边是外部边，直接换边就能得到更小的生成树，矛盾了）
- 如果w > a,替换后总权值是sum+w−dist1[a][b]
- 否则 w = a ，不能替换A边，会得到非严格次小生成树（权值和MST相等） 所以该做法也能得到非严
- w = a，w > 次大值b 则可以替换b的边，替换后总权值是sum+w−dist2[a][b]
> 如果求的是非严格的次小生成树，那么维护最大边权就行，但是如果求的是严格次小生成树，那么还要维护次大边权，因为如果最大边权和没选的边一样长，不一定是无解的，可能环上的次大边可以被替换。

##### 蒟蒻代码
略

#### [904. 虫洞](https://www.acwing.com/problem/content/906/)
##### 思路
spfa判负环模板题
##### 蒟蒻代码
``` cpp
cint N = 510, M = 5210;

int n, m1, m2;
vpii g[N];

void add(int u, int v, int w) { g[u].push_back({v, w}); }
bool spfa() {
    int dis[N], cnt[N];
    bitset<N> inq;
    queue<int> q;
    rep(i, n) q.push(i);
    rep(i, n) dis[i] = 0, cnt[i] = 0, inq[i] = 1;
    while (q.size()) {
        auto u = q.front();
        q.pop();
        inq[u] = 0;
        for (auto [v, w] : g[u]) {
            if (chmin(dis[v], dis[u] + w)) {
                cnt[v] = cnt[u] + 1;
                if (cnt[v] > n) return 1;
                if (!inq[v]) q.push(v);
            }
        }
    }
    return 0;
}
void solve() {
    cin >> n >> m1 >> m2;
    rep(i, n) g[i].clear();
    rep(m1) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w), add(v, u, w);
    }
    rep(m2) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, -w);
    }
    if (spfa()) return YES();
    else return NO();
}
```
#### [361. 观光奶牛](https://www.acwing.com/problem/content/363/)
##### 思路
01分数规划 转化为 二分判定，也就是要求 $\sum f_i / \sum t_i > x \iff \sum (f_i - x \cdot t_i) > 0$ 因为可以把点权缩到边权中，所以等价于判定图中存在正环，
##### 蒟蒻代码
``` cpp
cint N = 1005;

int n, m;
vpii g[N];
int f[N], cnt[N];
queue<int> q;
bitset<N> inq;
double dis[N];

void add(int u, int v, int w) { g[u].push_back({v, w}); }
bool check(double x) {
    while (q.size()) q.pop();
    rep(i, n) q.push(i), inq[i] = 1, dis[i] = 0, cnt[i] = 0;
    while (q.size()) {
        int u = q.front();
        q.pop();
        inq[u] = 0;
        for (auto [v, w] : g[u]) {
            if (chmax(dis[v], dis[u] + f[u] - w * x)) {
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n) return 1;
                if (!inq[v]) q.push(v), inq[v] = 1;
            }
        }
    }
    return 0;
}
void solve() {
    cin >> n >> m;
    rep(i, n) cin >> f[i];
    rep(m) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w);
    }
    double l = 0, r = 1010;
    while (r - l > 1e-4) {
        double mid = (l + r) / 2;
        if (check(mid)) l = mid;
        else r = mid;
    }
    print(l);
}
```
####
##### 思路
1. 建图
如果把单词看成点，把连接看成边，那么点的数量是1e5，边就会到1e10，太大了，于是我们做一个对偶（原来的点变成边，原来的边变成点）比如ababc，就看成是ab和bc之间有一条边，然后边权就是单词的长度，于是问题变成了01分数规划问题
2. $\sum w_j / \sum s_i$ 最大
也就是 $\sum w_j  / \sum 1$就是边权之和除以点的数量，于是考虑二分，判定函数是 $\sum w_j / \sum 1 > x \iff \sum (w_j -x) > 0$ 也就是判断新图中是否有正环。显然在x=0的时候最有可能有正环，所以判断是否有解可以看x=0的情况。
3. 利用经验来优化
##### 蒟蒻代码
``` cpp
cint N = 800, M = 1e5 + 5;

int m;
vpii g[N];
double dis[N];
int cnt[N];
queue<int> q;
bitset<N> inq;

void add(int u, int v, int w) { g[u].push_back({v, w}); }
bool check(double x) {
    mset(dis, 0), mset(cnt, 0);
    while (q.size()) q.pop();
    rep(i, 0, 26 * 26 - 1) inq[i] = 1, q.push(i);
    int count = 0;
    while (q.size()) {
        int u = q.front();
        inq[u] = 0;
        q.pop();
        for (auto [v, w] : g[u]) {
            if (chmax(dis[v], dis[u] + w - x)) {
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= N) return 1;
                if (++count >= 10000) return 1;
                if (!inq[v]) inq[v] = 1, q.push(v);
            }
        }
    }
    return 0;
}
void solve() {
    while (cin >> m, m) {
        rep(i, 0, 26 * 26 - 1) g[i].clear();
        string s;
        int len;
        rep(m) {
            cin >> s;
            len = s.length();
            if (len < 2) continue;
            int u = (s[0] - 'a') * 26 + s[1] - 'a';
            int v = (s[len - 2] - 'a') * 26 + s[len - 1] - 'a';
            add(u, v, len);
        }
        if (!check(0)) print("No solution");
        else {
            double l = 0, r = 1000;
            while (r - l > 1e-4) {
                double mid = (l + r) / 2;
                if (check(mid)) l = mid;
                else r = mid;
            }
            print(l);
        }
    }
}
```
#### [1169. 糖果](https://www.acwing.com/problem/content/1171/)
##### 思路
考虑每个小朋友有几个糖果，于是求的是 $\sum x_i$ 的最小值，因此不等式应该为 $x_i \ge  x_j +c_k$，这个松弛操作在最长路中出现，因此考虑使用最长路。
再来考虑约束条件：
- $x_i = x_j \iff (x_i \ge x_j)\land (x_j \ge  x_i)$
- $x_i< x_j \iff x_j \ge  x_i + 1$，于是从 i 到 j 建边
- $x_i \ge  x_j$ 于是从 j 到 i 建边
- $x_i > x_j \iff x_i \ge  x_j + 1$ 于是从 j 到 i 建边
- $x_i \le  x_j$ 于是从 i 到 j 建边
- 显然上面的约束条件，无法得到最小值，于是我们考虑有没有对于单变量的约束，因为每个小朋友不能没有糖，所以有 $x_i \ge  0+1$
##### 蒟蒻代码
``` cpp
cint N = 1e5 + 5, M = 3e5 + 5;

int n, m;
int idx = 0;
int h[N], ne[M], w[M], to[M];
ll dis[N], cnt[N];
bitset<N> ins;
stack<int> s;

void add(int u, int v, int ww) {
    w[++idx] = ww, to[idx] = v, ne[idx] = h[u], h[u] = idx;
}

bool spfa() {
    ins[0] = 1, s.push(0);
    while (!s.empty()) {
        auto u = s.top();
        ins[u] = 0, s.pop();
        for (int i = h[u]; i; i = ne[i]) {
            int v = to[i], ww = w[i];
            if (chmax(dis[v], dis[u] + ww)) {
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n + 1) return 0;
                if (!ins[v]) s.push(v), ins[v] = 1;
            }
        }
    }
    return 1;
}

void solve() {
    cin >> n >> m;
    rep(m) {
        int x, a, b;
        cin >> x >> a >> b;
        if (x == 1) add(a, b, 0), add(b, a, 0);
        elif (x == 2) add(a, b, 1);
        elif (x == 3) add(b, a, 0);
        elif (x == 4) add(b, a, 1);
        else add(a, b, 0);
    }
    rep(i, n) add(0, i, 1);
    auto t = spfa();
    if (!t) return print(-1);
    else print(accumulate(all(dis, n), 0ll));
}
```
#### [362. 区间](https://www.acwing.com/problem/content/364/)
##### 思路
考虑如何建图，因为题目中的约束条件是区间中数量的限制，因此考虑如何利用这个限制，**设 $s_i$ 表示从1-i中选入Z集合的数字的数量**，类似前缀和。由于求的是最小值，对应的松弛是大于等于，于是考虑最长路。于是我们有如下约束条件
- $s_i \ge s_{i-1}, i \in [1,50000]$
- $s_i - s_{i-1} \le 1 \iff s_{i-1}\ge s_i -1, i \in [1,50000]$
- 区间 $[a,b]$ 中必须选 $c$ 个，就是 $s_b - s_{a-1}\ge c \iff s_{b}\ge s_{a-1}+c$
但是注意这里的数字从0开始，为了不和我们的虚拟源点冲突，于是我们都要+1，这样就行了
##### 蒟蒻代码
``` cpp
cint N = 5e5 + 5, M = 5e5 + 5;

int n = 5e4 + 1, m;
int idx = 0, h[N], ne[N], to[N], w[N];
int dis[N];
bool inq[N];
void add(int x, int y, int z) {
    to[++idx] = y, w[idx] = z, ne[idx] = h[x], h[x] = idx;
}
void spfa() {
    queue<int> q;
    rep(i, n) dis[i] = -inf<int>;
    inq[0] = 1, q.push(0);
    while (q.size()) {
        int u = q.front();
        inq[u] = 0, q.pop();
        for (int i = h[u]; i; i = ne[i]) {
            int v = to[i];
            if (chmax(dis[v], dis[u] + w[i]))
                if (!inq[v]) inq[v] = 1, q.push(v);
        }
    }
}
void solve() {
    cin >> m;
    rep(i, n) add(i - 1, i, 0), add(i, i - 1, -1);
    rep(m) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b + 1, c);
    }
    spfa();
    print(dis[n]);
}
```

#### [1170. 排队布局](https://www.acwing.com/problem/content/1172/)
##### 思路
考虑如何利用给定的关系，因为求的是最大距离，一个很直觉的想法就是把每个牛的位置作为变量，于是约束条件是
- $x_i \le  x_{i+1}$
- $x_j - x_i \le  L \iff x_j \le  x_i + L$
- $x_j - x_i \ge  D \iff x_i \le  x_j-D$

但是注意这里没有保证**源点要满足：从源点出发，一定可以到达所有的边**，所以可以建一个超级源点0，在位置0，但是因为求的是相对的距离，所以可以不妨设 $x_i\ge 0$（那就是从0向所有点建一条边），且 $x_1=0$，我们可以增加这个0点，也可以由于spfa从0开始，所以把所有点加入初始的栈中即可。
于是求的是 $x_n$ 的最大值，那么是小于等于的关系，对应的是最短路的松弛操作
那么，无解对应存在负环，无穷距离对应距离inf也就是到不了，其余就是 $d[n]$
##### 蒟蒻代码
``` cpp
cint N = 1005, M = 2e4 + 5;

int n, m1, m2;
int idx = 0, h[N], ne[M], to[M], w[M];
int dis[N], cnt[N];
stack<int> stk;
bitset<N> ins;

void add(int a, int b, int c) {
    to[++idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx;
}

int spfa() {
    rep(i, n) dis[i] = inf<int>, ins[i] = 1, stk.push(i);
    dis[1] = 0;
    while (stk.size()) {
        int u = stk.top();
        ins[u] = 0, stk.pop();
        for (int i = h[u]; i; i = ne[i]) {
            int v = to[i];
            if (chmin(dis[v], dis[u] + w[i])) {
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n) return -1;
                if (!ins[v]) ins[v] = 1, stk.push(v);
            }
        }
    }
    if (dis[n] == inf<int>) return -2;
    return dis[n];
}
void solve() {
    cin >> n >> m1 >> m2;
    rep(i, n - 1) add(i + 1, i, 0);
    rep(m1) {
        int a, b, c; cin >> a >> b >> c;
        if (a > b) swap(a, b);
        add(a, b, c);
    }
    rep(m2) {
        int a, b, c; cin >> a >> b >> c;
        if (a > b) swap(a, b);
        add(b, a, -c);
    }
    print(spfa());
}
```
#### [393. 雇佣收银员](https://www.acwing.com/problem/content/395/)
##### 思路
用 $\max[i]$ 表示某个时刻可以来多少个工人，用 $x_i$ 表示某个时刻有多少的工人，$r_i$ 表示某个时刻的需求数量，那么有如下约束条件：
- $0\le x_i \le  \max[i]$
- $\sum_{k=i-7}^{i}x_k\ge r_i$

我们发现第一个约束条件中规中矩，但是第二个不是，但是考虑到这个是区间求和，于是我们利用前缀和（同时注意下标为了之后留出虚拟源点，所以我们下表都+1），用 $s[i]$ 表示 $s[i]=\sum_{k=1}^{i}x_i$，那么两个约束条件改写为：
- $0\le s[i]-s[i-1]\le \max[i]$
- if $i\ge 8$,then $s[i]-s[i-1]\ge r_i$
- if $0<i<7$ then $s[i]+s[24]-s[i+16]\ge r_i$

因为求的是最小值，于是关系使用大于等于号，对应的松弛操作是最长路，于是改写为：
- $s[i]\ge s[i-1]$
- $s[i-1]\ge s[i]-\max[i]$
- if $i\ge 8$ then $s[i]\ge s[i-8]+r_i$
- if $0<i<7$ then $s[i]\ge s[i+16]-s[24]+r_i$

我们发现除了最后一个式子，别的都很好，那么最后一个式子注意到 $s[24]$ 每次都是他，注意到本题数据范围很小，我们可以枚举 $s[24]$ 从 0 到 1000，这样四个都是很好的不等式了。 而答案就是所有 $x_i$的和，就是 $s[24]$ 于是，我们从小到大枚举，找到第一个有解的情况返回即可，如果都无解，那么整个无解。
##### 蒟蒻代码
``` cpp
cint N = 26;
cint n = 24;

int r[N];
int mx[N];
int dis[N], cnt[N];
bitset<N> st;
stack<int> stk;
int idx = 0;
int h[N], ne[N << 2], w[N << 2], to[N << 2];

void add(int x, int y, int z) {
    w[++idx] = z, to[idx] = y, ne[idx] = h[x], h[x] = idx;
}

void build(int ss) {
    mset(h, 0);
    idx = 0;
    rep(i, n) add(i - 1, i, 0);
    rep(i, n) add(i, i - 1, -mx[i]);
    rep(i, 8, n) add(i - 8, i, r[i]);
    rep(i, 7) add(i + 16, i, r[i] - ss);
    add(24, 0, -ss), add(0, 24, ss);
}

bool spfa(int ss) {
    build(ss);
    rep(i, 0, n) dis[i] = -inf<int>, cnt[i] = st[i] = 0;

    while (stk.size()) stk.pop();
    dis[0] = 0, st[0] = 1, stk.push(0);
    while (stk.size()) {
        int x = stk.top();
        st[x] = 0, stk.pop();
        for (int i = h[x]; i; i = ne[i]) {
            int y = to[i];
            if (chmax(dis[y], dis[x] + w[i])) {
                cnt[y] = cnt[x] + 1;
                if (cnt[y] >= 25) return 0;
                if (!st[y]) st[y] = 1, stk.push(y);
            }
        }
    }
    return 1;
}

void solve() {
    rep(i, n) cin >> r[i];
    int m;
    cin >> m;
    mset(mx, 0);
    rep(m) {
        int t;
        cin >> t;
        mx[t + 1]++;
    }
    int ans = 0;
    while (ans <= m) {
        if (spfa(ans)) return print(ans);
        ans++;
    }
    print("No Solution");
}
```
#### [1172. 祖孙询问](https://www.acwing.com/problem/content/1174/)
##### 思路
lca模板题
##### 蒟蒻代码
``` cpp
cint N = 4e4 + 5;

int n, m;
vi g[N];
int dep[N], fa[N][16];
void add(int x, int y) { g[x].push_back(y); }
void bfs(int root) {
    queue<int> q;
    mset(dep, 0x3f);
    dep[0] = 0, dep[root] = 1;
    q.push(root);
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (auto v : g[u]) {
            if (chmin(dep[v], dep[u] + 1)) {
                q.push(v);
                fa[v][0] = u;
                rep(i, 1, 15) fa[v][i] = fa[fa[v][i - 1]][i - 1];
            }
        }
    }
}
int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    per(i, 15, 0) if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
    if (x == y) return x;
    per(i, 15, 0) if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}
void solve() {
    int root = -1;
    cin >> n;
    rep(n) {
        int x, y;
        cin >> x >> y;
        if (y == -1) root = x;
        else add(x, y), add(y, x);
    }
    bfs(root);
    cin >> m;
    rep(m) {
        int x, y;
        cin >> x >> y;
        int t = lca(x, y);
        if (t == x) print(1);
        elif (t == y) print(2);
        else print(0);
    }
}
```
#### [1171. 距离](https://www.acwing.com/problem/content/1173/)
##### 思路
lca模板题
##### 蒟蒻代码
``` cpp
cint N = 1e5 + 5;
cint M = 2e5 + 5;

int n, m;
vpii g[N];
int st[N], dis[N];
vpii query[M];
int ans[N];
int fa[N];

void add(int a, int b, int c) { g[a].push_back({b, c}); }
void dfs(int u, int p) {
    for (auto [v, w] : g[u]) {
        if (v != p) {
            dis[v] = dis[u] + w;
            dfs(v, u);
        }
    }
}
int get(int x) {
    if (fa[x] == x) return x;
    return fa[x] = get(fa[x]);
}
void tarjan(int u) {
    st[u] = 1;
    for (auto [v, w] : g[u]) {
        if (!st[v]) {
            tarjan(v);
            fa[v] = u;
        }
    }
    for (auto [v, id] : query[u]) {
        if (st[v] == 2) {
            int anc = get(v);
            ans[id] = dis[u] + dis[v] - 2 * dis[anc];
        }
    }
    st[u] = 2;
}
void solve() {
    cin >> n >> m;
    rep(i, n) fa[i] = i;
    rep(n - 1) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    rep(i, m) {
        int a, b;
        cin >> a >> b;
        if (a != b) {
            query[a].push_back({b, i});
            query[b].push_back({a, i});
        }
    }
    dfs(1, -1);
    tarjan(1);
    rep(i, m) print(ans[i]);
}
```
#### [356. 次小生成树](https://www.acwing.com/problem/content/description/358/)
##### 思路
严格次小生成树，考虑从mst中选择一条边，用没选过的边进行替换。但是要注意我们不能仅仅维护两点间的最大值，还要考虑两点间的**次大值**，因为可能在加入一条边的环中，原来的最大值和现在是一样的，但是次大值比现在的新加的边要小，也是可以进行替换作为候选项的。
##### 蒟蒻代码
``` cpp
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
```
#### [352. 闇の連鎖](https://www.acwing.com/problem/content/description/354/)
##### 思路
题目意思说有两种边，一种是树边，一种是非树边，每次可以切一条树边一条非树边，请问能变得不联通的方案有多少种？那么计数问题的关键就是对集合的划分，我们在这里按照非树边进行划分，因为对于一棵树而言，增加一条边就意味着出现一个环，要想让图变得不联通，那就要在这个环里面至少去除两条边。所以对于这个环里面的任意一条边，我可以去除自身，并且一定要去除非树边，因为两次删边一定又一次要是非树边。（其实本来是按照每条非树边考虑，就是他造成的环中自己要删除，还要删除一条环中的任意树边，但是这里注意变换视角，这很重要）因此，要让这个环断开，对于这个树边来说，一定要删除这条非树边，那么每一条非树边都会影响一个环上的所有边，那么我们可以统计对于每条边来说受到几个环的影响，如果是0，那么删除这条边就已经能够造成不联通，那么第二条非树边随便删就行，如果是1那么就意味着一定要删除影响他的那条非树边，如果大于1，那么不可能通过仅仅删除一条非树边来使得这图变得不联通，所以最后只要看有几条非树边和当前的边在一个环中，所以这是一个区间修改的问题，因此**考虑使用树上差分，然后将前缀和变成子树和**。（更直观的理解可以考虑把点和边的顺序交换）如果想把树上 $a$ 到 $b$ 的路径全都 $+c$ ，只需要在差分数组做如下操作： $d[a]+=c, d[b]+=c,d[\operatorname{lca}(a,b)]-=2c$ 即可。然后统计的时候，**要看每棵子树的子树和，因为这表示子节点连接当前节点的边的权值！！！**
##### 蒟蒻代码
``` cpp
cint N = 100005;

int n, m;
vi g[N];
int dep[N], f[N][20];
int d[N];
int ans = 0;

void add(int a, int b) { g[a].push_back(b); }
void bfs() {
    queue<int> q;
    dep[1] = 1, q.push(1);
    while (q.size()) {
        int x = q.front();
        q.pop();
        for (auto y : g[x]) {
            if (dep[y]) continue;
            dep[y] = dep[x] + 1;
            f[y][0] = x;
            rep(i, 1, 18) f[y][i] = f[f[y][i - 1]][i - 1];
            q.push(y);
        }
    }
}
int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    per(i, 18, 0) if (dep[f[a][i]] >= dep[b]) a = f[a][i];
    if (a == b) return a;
    per(i, 18, 0) {
        if (f[a][i] != f[b][i]) {
            a = f[a][i], b = f[b][i];
        }
    }
    return f[a][0];
}
int dfs(int u, int fa) {
    int res = d[u];
    for (auto v : g[u]) {
        if (v == fa) continue;
        int t = dfs(v, u);
        if (t == 0) ans += m;
        elif (t == 1) ans++;
        res += t;
    }
    return res;
}
void solve() {
    cin >> n >> m;
    rep(n - 1) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    bfs();
    rep(m) {
        int a, b;
        cin >> a >> b;
        int anc = lca(a, b);
        d[a]++, d[b]++, d[anc] -= 2;
    }
    dfs(1, -1);
    print(ans);
}
```
#### [1174. 受欢迎的牛](https://www.acwing.com/problem/content/description/1176/)
##### 思路
就是判断是否有些点，可以被所有其他点访问到。如果该图是拓扑图，那就直接看在最尾部的点是否是唯一就行了，那在这边可以考虑缩点，然后转化成拓扑图上的问题即可。不用真的建图，只要看缩点之后的每个强联通分量的出度就行。
##### 蒟蒻代码
``` cpp
cint N = 1e4 + 5;

int n, m;
vi g[N];
stack<int> stk;
bitset<N> ins;
int low[N], dfn[N], id[N], sz[N], idx = 0, scnt = 0;
int out[N];

void add(int a, int b) { g[a].push_back(b); }
void tarjan(int u) {
    low[u] = dfn[u] = ++idx;
    stk.push(u), ins[u] = 1;
    for (int v : g[u]) {
        if (dfn[v] == 0) {
            tarjan(v);
            chmin(low[u], low[v]);
        }
        elif (ins[v]) chmin(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        ++scnt;
        int t;
        do {
            t = stk.top();
            ins[t] = 0, stk.pop();
            id[t] = scnt, sz[scnt]++;
        } while (t != u);
    }
}
void solve() {
    cin >> n >> m;
    rep(m) {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }
    rep(i, n) if (dfn[i] == 0) tarjan(i);
    rep(i, n) {
        for (int j : g[i]) {
            int a = id[i], b = id[j];
            if (a != b) out[a]++;
        }
    }
    int zero = 0, ans = 0;
    rep(i, scnt) {
        if (out[i] == 0) {
            zero++, ans = sz[i];
            if (zero > 1) return print(0);
        }
    }
    print(ans);
}
```
#### [367. 学校网络](https://www.acwing.com/problem/content/369/)
##### 思路
对于拓扑图上来说，第一个问题就是问有几个indeg为0的点。第二问，就是要让所有点都强联通，其实我们也可以这样理解，我们将起点所能到达的终点分为P类，每个起点分别可以到达其中一类，从每个终点分别向下一个起点连一条边，最后一个终点向第一个起点连一条边，这样就构成了一个回路，所有点都可以达到任意点。需要连的边的数量就是 P个终点里面对应的所有点的数量 Q，所以就是P和Q中的最大值。记得特判整个图本来就是强联通的情况。
##### 蒟蒻代码
``` cpp
cint N = 105;

int n;
vi g[N];
int sz[N], low[N], id[N], dfn[N], idx = 0, scnt = 0;
stack<int> stk;
bitset<N> ins;
int ind[N], outd[N];

void add(int a, int b) { g[a].push_back(b); }
void scc(int u) {
    low[u] = dfn[u] = ++idx;
    stk.push(u), ins[u] = 1;
    for (int v : g[u]) {
        if (!dfn[v]) {
            scc(v);
            chmin(low[u], low[v]);
        }
        elif (ins[v]) chmin(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        ++scnt;
        int t;
        do {
            t = stk.top();
            stk.pop(), ins[t] = 0;
            id[t] = scnt, sz[scnt]++;
        } while (t != u);
    }
}
void solve() {
    cin >> n;
    int t;
    rep(i, n) {
        while (cin >> t, t) add(i, t);
    }
    rep(i, n) if (!dfn[i]) scc(i);
    rep(a, n) for (int b : g[a]) if (id[a] != id[b]) ind[id[b]]++, outd[id[a]]++;
    int incnt = 0, outcnt = 0;
    rep(i, scnt) incnt += ind[i] == 0, outcnt += outd[i] == 0;
    print(incnt);
    if (scnt == 1) return print(0);
    print(max(incnt, outcnt));
}
```
####
##### 思路
因为强联通分量一定是半联通子图，所以先进行缩点，然后得到的拓扑图中的最大的半联通子图就是最长链，因为不能有分叉，如果有分叉，那么分叉末端中的点不是半联通的了
##### 蒟蒻代码