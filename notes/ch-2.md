## Ch 2 搜索
### 零零碎碎
#### BFS
- 最短距离（比如走迷宫）-> 从点到点

- 最小步数 -> 把地图看成状态，求的是一种状态变成另一种状态的最小步数

- bfs存储的队列具有**两段性**：队列中所有的点到起点的距离的差值最多是1

  bfs存储的队列具有**单调性**：队列中存的都有元素到原点的距离一定是单调递增的

  因此在边权都是1的情况下以上两条性质就保证了，当前队列就相当于dijkstra中的优先队列，且每个点只会入队一次，因此可以在线性时间内得到单源最短路

- 只包含0-1两种边权的图的最短路可以用双端队列bfs求解

  和普通队列bfs的区别在于：扩展边的时候，判断扩展出的边的权重，**如果是0就插到队头，如果是1就插到队尾**

  所有能够用bfs求最短路的问题的证明都可以把问题转换为dijkstra算法的证明。

  因为每次扩展的时候边权只有0-1，利用数学归纳法，可以得到**这个双端队列具有两段性和单调性**，因此这个队列亦可以看成单调队列，所以就等价于dijkstra算法

- 在**最小步数模型**中，可以使用双向广搜来优化，因为状态的扩展是指数级的，因此双向广搜可以把 $O(N^{k})$ 的搜索规模缩小到 $O(2\cdot N^{k / 2})$，其实是一个很大的跨越；为了防止某一边一条道走到黑，可以在每次扩展的时候选择队列大小较小的一边进行扩展

- **A\* 算法** :依旧是对于搜索空间非常庞大的问题的优化，考虑引入一个**启发函数**，目的就是只需要遍历很少的状态就可以找到到达终点的路径。（要求没有负权回路并且一定有解才可以使用）
  
  算法流程：
  
  ``` cpp
  priority_queue<...> q;  // 小根堆
  // 排序依据：从起点到当前点的真实距离 + 从当前点到终点的估价距离
  while(pq.size()){
      auto t=pq.top();pq.pop();
      当终点第一次出队的时候 break 返回
      for t的所有邻边:
          如果能更新 pq.push(邻边)
  }
  ```
  其实非常类似dijkstra算法（但是与dijkstra不同），但是dijkstra算法就是估价函数恒为0的A\*算法。A\*算法成立的重要条件：假设当前状态是 $s$ ，从起点到当前点的距离为 $d(s)$, 从当前点到终点的真实距离为 $g(s)$，那么真实的这条路径的距离就是 $d(s)+g(s)$ ，假设估价函数是 $f$，那么一定要有 $f(s) \le g(s)$也就是估价不能大于未来实际价值。 对于这个算法正确性的证明：考虑反证法，假设终点 $T$ 第一次出队的时候不是最小值，即 $d(T) \gt d_{\min}$，那么在队列里面一定存在一个最优解路径上的点 $u$，对于 $u$ 而言，$d(u)+f(u) \le d(u)+g(u)=d_{\min}<d(T)+f(T)$，而 $T$ 在它前面出队，矛盾。因此第一次出队一定是最优解。
  **A\*算法只能保证终点出队的时候是最小值，不能保证其他点第一次出队的时候是最小值**，因为估价函数估计的是到终点的距离，而对于中间的点不一定具有参考意义。因此，对于中间的点出队一次就要更新一次而不是对他标记然后不入队了。 

主要是能求“求最小”的题型，bfs是基于迭代的算法，所以不会爆栈。
- **flood fill** 可以在线性时间复杂度内，找到某个点所在的连通块
- **最短路模型** 当边权全相等时，通过bfs可以在线性时间内得到单源最短路

#### DFS
- 走迷宫只能找到是否连通，无法确定是否是最短路
- 一定要思考是否需要回溯！在比如一个棋盘里面遍历的时候，为了保证每个点只被搜一次，不需要回溯；在考虑是把整个棋盘看成一个状态，在状态之间进行转换的时候，需要回溯。**就是要看清楚每次搜索的时候，起始的状态是否要求是一样的。**
- 常用的**剪枝策略**：
  - 一般情况下，我们应该**优先搜索分支较少的节点**、策略选择数量较少的节点，因为如果夭折的较早的话，下面可能很多的深层的分支直接pass了
  - **排除等效冗余** 比如以组合的形式来搜索而不是排列
  - **可行性剪枝**
  - **最优性剪枝**
  - 记忆化搜索 
- 搜索中顺序非常重要！！！枚举的顺序一定要保证都能枚举到
- 搜索的结果记录既可以在全局变量中记录，也可以用返回值或者dfs的参数引用来记录，但是外部的记录容易实现搜索到之后直接最优性剪枝
- 组合型的枚举方式的特点就是在**枚举每个集合的时候**，只会**取按照偏序关系字典序最小的方式作为一种状态**。枚举方式可以是**枚举每个元素**在哪一个现有的集合，或者新开一个集合，也可以是 **枚举每个集合里面有哪些元素**，从前往后**枚举集合**。注意第二种枚举方式，有可能如果不能作为第一个元素或者最后一个元素，他就不可能满足条件了。
- **迭代加深： 搜索树的有些错误节点可能会特别深，但是合法方案可能在某个很浅的位置。** 迭代加深的思想就是定义一个层数上限，每次搜索的时候，如果当前的深度超过上限了就直接return了，然后这个上限是一层层扩大的。
- 双向DFS：原理和双向bfs一样，用空间换时间
- IDAstar 思想和Astar差不多，一般都是配合迭代加深一起做。设定一个最大深度的阈值，再构造一个估价函数，如果当前的步数加上未来的（保守的）估计的值都会超过深度阈值，那就剪枝剪掉。注意：估价函数的值小于真实值，就是当前状态到目标状态无论如何都要的最少的步数。
- 感觉估价函数就是用来表征**一次操作最小价值**的东西
- **比较复杂的操作可以给操作打表。**

### 水题 ovo
#### [1097. 池塘计数](https://www.acwing.com/problem/content/1099/)
##### 思路
基础搜索题，每次把能扫到的连通的区域全部扫一遍就行，最后统计一共有多少个连通块。

*注意是八向*
##### 蒟蒻代码
``` cpp
cint N = 1005;
cint dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
cint dy[] = {0, 0, -1, 1, -1, 1, -1, 1};

int n, m;
char a[N][N];
bool st[N][N];

bool check(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= m; }

bool bfs(int x, int y) {
    if (st[x][y] || a[x][y] == '.') return 0;
    queue<PII> q;
    q.push({x, y}), st[x][y] = 1;
    while (q.size()) {
        auto [xx, yy] = q.front();
        q.pop();
        rep(i, 0, 7) {
            int tx = xx + dx[i], ty = yy + dy[i];
            if (!check(tx, ty) || st[tx][ty] || a[tx][ty] == '.') continue;
            st[tx][ty] = 1;
            q.push({tx, ty});
        }
    }
    return 1;
}

void solve() {
    cin >> n >> m;
    rep(i, n) cin >> (a[i] + 1);
    int ans = 0;
    rep(i, n) rep(j, m) ans += bfs(i, j);
    print(ans);
}
```

#### [1098. 城堡问题](https://www.acwing.com/problem/content/1100/)
##### 思路
bfs基础题，每次扩展的时候判断：1、是否越界 2、是否被访问过 3、是否有墙 即可
##### 蒟蒻代码
``` cpp
cint N = 55;

cint dx[] = {0, -1, 0, 1};
cint dy[] = {-1, 0, 1, 0};

int n, m;
int a[N][N];
bool st[N][N];

bool check(int x, int y) { return !st[x][y] && 1 <= x && x <= n && 1 <= y && y <= m; }

int bfs(int sx, int sy) {
    int ret = 1;
    queue<PII> q;
    q.push({sx, sy}), st[sx][sy] = 1;
    while (q.size()) {
        auto [x, y] = q.front();
        q.pop();
        rep(i, 0, 3) {
            if (a[x][y] >> i & 1) continue;
            int xx = x + dx[i], yy = y + dy[i];
            if (!check(xx, yy)) continue;
            st[xx][yy] = 1, ret++;
            q.push({xx, yy});
        }
    }

    return ret;
}

void solve() {
    cin >> n >> m;
    rep(i, n) rep(j, m) cin >> a[i][j];

    int cnt = 0, ans = -inf<int>;
    rep(i, n) rep(j, m) if (!st[i][j]) cnt++, chmax(ans, bfs(i, j));
    print(cnt);
    print(ans);
}
```

#### [1106. 山峰和山谷](https://www.acwing.com/problem/content/1108/)
##### 思路
每次扩展只扩展高度相同的，同时记录周围的严格偏序关系是否一致，如果有异端就G了即可
##### 蒟蒻代码
``` cpp
cint N = 1005;
cint dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
cint dy[] = {0, 0, -1, 1, 1, -1, 1, -1};

int n;
int a[N][N];
bool st[N][N];

bool check(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= n; }

pair<bool, bool> bfs(int sx, int sy) {
    if (st[sx][sy]) return {0, 0};
    bool hi = 1, lo = 1;
    queue<PII> q;
    q.push({sx, sy}), st[sx][sy] = 1;
    while (q.size()) {
        auto [x, y] = q.front();
        q.pop();
        rep(i, 0, 7) {
            int xx = x + dx[i], yy = y + dy[i];
            if (!check(xx, yy)) continue;
            if (st[xx][yy] && a[xx][yy] == a[x][y]) continue;

            if (a[xx][yy] == a[x][y]) st[xx][yy] = 1, q.push({xx, yy});
            elif (a[xx][yy] > a[x][y]) hi = 0;
            else lo = 0;
        }
    }
    return {hi, lo};
}

void solve() {
    cin >> n;
    rep(i, n) rep(j, n) cin >> a[i][j];

    int qwq = 0, awa = 0;
    rep(i, n) rep(j, n) {
        auto [h, l] = bfs(i, j);
        qwq += l, awa += h;
    }

    print(awa, qwq);
}
```

#### [1076. 迷宫问题](https://www.acwing.com/problem/content/1078/)
##### 思路
在扩展的时候记录是从谁转移的，搜完之后用dfs逆序输出路径即可
##### 蒟蒻代码
``` cpp
cint N = 1005;
cint dx[] = {-1, 1, 0, 0};
cint dy[] = {0, 0, -1, 1};

int n;
bool a[N][N];
bool st[N][N];
PII p[N][N];

void dfs(int x, int y) {
    if (x == 1 && y == 1) return print(0, 0);
    dfs(p[x][y].fi, p[x][y].se);
    print(x - 1, y - 1);
}

bool check(int x, int y) { return !st[x][y] && 1 <= x && x <= n && 1 <= y && y <= n; }

void bfs() {
    queue<PII> q;
    q.push({1, 1}), st[1][1] = 1;
    while (q.size()) {
        auto [x, y] = q.front();
        q.pop();
        rep(i, 0, 3) {
            int xx = x + dx[i], yy = y + dy[i];
            if (!check(xx, yy) || a[xx][yy]) continue;
            st[xx][yy] = 1, p[xx][yy] = {x, y}, q.push({xx, yy});
            if (xx == n && yy == n) return;
        }
    }
}

void solve() {
    cin >> n;
    rep(i, n) rep(j, n) cin >> a[i][j];
    bfs();
    dfs(n, n);
}
```

#### [188. 武士风度的牛](https://www.acwing.com/problem/content/190/)
##### 思路
bfs水题，注意读入的时候行列长度是反的
##### 蒟蒻代码
```cpp
cint N = 155;
cint dx[] = {-1, -1, -2, -2, 1, 1, 2, 2};
cint dy[] = {2, -2, 1, -1, 2, -2, 1, -1};

int n, m;
PII s;
char a[N][N];
bool st[N][N];
int dis[N][N];

bool check(int x, int y) { return !st[x][y] && 1 <= x && x <= n && 1 <= y && y <= m; }

int bfs() {
    queue<PII> q;
    q.push(s);
    st[s.fi][s.se] = 1;
    while (q.size()) {
        auto [x, y] = q.front();
        q.pop();
        rep(i, 0, 7) {
            int xx = x + dx[i], yy = y + dy[i];
            if (!check(xx, yy)) continue;
            if (a[xx][yy] == '*') continue;
            dis[xx][yy] = dis[x][y] + 1, st[xx][yy] = 1;
            if (a[xx][yy] == 'H') return dis[xx][yy];
            q.push({xx, yy});
        }
    }
    return -1;
}

void solve() {
    cin >> m >> n;
    rep(i, n) rep(j, m) {
        cin >> a[i][j];
        if (a[i][j] == 'K') s = {i, j};
    }
    print(bfs());
}
```

#### [1100. 抓住那头牛](https://www.acwing.com/problem/content/1102/)
##### 思路
依旧bfs水题
##### 蒟蒻代码
``` cpp
cint N = 1e5 + 5;

int f, c;
int dis[N];

int bfs() {
    queue<int> q;
    q.push(f), dis[f] = 0;
    while (q.size()) {
        int x = q.front();
        q.pop();
        if (x - 1 >= 0) dis[x - 1] = dis[x - 1] == -1 ? q.push(x - 1), dis[x] + 1 : dis[x - 1];
        dis[x + 1] = dis[x + 1] == -1 ? q.push(x + 1), dis[x] + 1 : dis[x + 1];
        if (x * 2 < N) dis[x * 2] = dis[x * 2] == -1 ? q.push(x * 2), dis[x] + 1 : dis[x * 2];
        if (x - 1 == c || x + 1 == c || x * 2 == c) return dis[x] + 1;
    }
    return dis[c];
}

void solve() {
    mset(dis, -1);
    cin >> f >> c;
    if(f==c) return print(0);
    else return print(bfs());
}
```

#### [173. 矩阵距离](https://www.acwing.com/problem/content/175/)
##### 思路
题目就是求每个点距离最近的1的位置，因此可以考虑反向扩展，先把所有1的位置加入队列，然后逐层扩展即可
##### 蒟蒻代码
``` cpp
cint N = 1005;
cint dx[] = {-1, 1, 0, 0};
cint dy[] = {0, 0, 1, -1};

int n, m;
char a[N][N];
int dis[N][N];

bool check(int x, int y) { return dis[x][y] == inf<int> && 1 <= x && x <= n && 1 <= y && y <= m; }

void bfs() {
    queue<PII> q;
    rep(i, n) rep(j, m) dis[i][j] = a[i][j] == '1' ? q.push({i, j}), 0 : inf<int>;
    while (q.size()) {
        auto [x, y] = q.front();
        q.pop();
        rep(i, 0, 3) {
            int xx = x + dx[i], yy = y + dy[i];
            if (!check(xx, yy)) continue;
            dis[xx][yy] = dis[x][y] + 1;
            q.push({xx, yy});
        }
    }
}

void solve() {
    cin >> n >> m;
    rep(i, n) cin >> (a[i] + 1);
    bfs();
    rep(i, n) aprint(dis[i], 1, m);
}
```

#### [1107. 魔板](https://www.acwing.com/problem/content/1109/)
##### 思路
同样也是bfs的基础题，但是注意输入的是终止状态不是初始状态！！！
##### 蒟蒻代码
``` cpp
string tar;
string st = "12348765";
unordered_map<string, int> mp;
unordered_map<string, pair<char, string>> p;

string get(string s, int op) {
    if (op == 0) return {s[4], s[5], s[6], s[7], s[0], s[1], s[2], s[3]};
    if (op == 1) return {s[3], s[0], s[1], s[2], s[7], s[4], s[5], s[6]};
    return {s[0], s[5], s[1], s[3], s[4], s[6], s[2], s[7]};
}

void bfs() {
    queue<string> q;
    q.push(st);
    mp[st] = 0;
    while (q.size()) {
        auto x = q.front();
        q.pop();
        rep(i, 0, 2) {
            auto t = get(x, i);
            if (mp.find(t) != mp.end()) continue;
            mp[t] = mp[x] + 1, p[t] = {'A' + i, x}, q.push(t);
            if (t == tar) return;
        }
    }
}

void dfs(string s) {
    if (s == st) return;
    dfs(p[s].se);
    wt(p[s].fi);
}

void solve() {
    rep(8) {
        int t;
        cin >> t;
        tar += '0' + t;
    }
    swap(tar[4], tar[7]), swap(tar[5], tar[6]);
    bfs();
    print(mp[tar]);
    dfs(tar);
}
```

#### [175. 电路维修](https://www.acwing.com/problem/content/description/177/)
##### 思路
首先，假设起点的坐标为 $(0,0)$，因为只能斜着走，所以每次横纵坐标要同时变化1，也就意味着横纵坐标的和一定是偶数，奇数的格点一定无法到达。

接着，这题求的是需要变换多少次，那么我们可以对于两个（斜着）相邻的格点，如果他们本来边的方向就是可以走到的，那就意味着不需要变换，因此把边权看成0，如果恰好相反，那么需要变换1次，把边权看成1，于是 这题就变成了 $(0,0) \to (n,m)$ 的最短路问题，而由于边权只有0-1，因此我们可以考虑使用双端队列bfs来求答案，注意这种bfs可以看成是青春版的dijkstra，因此写法和堆优化的dijkstra比较像，注意返回答案的时间，不能在第一次被扩展到之后，因为有0边权的存在，应该在第一次由他扩展的时候。
##### 蒟蒻代码
``` cpp
cint N = 505;
cint dx[] = {-1, 1, 1, -1};
cint dy[] = {1, 1, -1, -1};
cint ix[] = {0, 1, 1, 0};
cint iy[] = {1, 1, 0, 0};
const string cd = "/\\/\\";

int n, m;
char a[N][N];
int dis[N][N];
bool st[N][N];

int bfs() {
    mset(dis, 0x7f), mset(st, 0);
    auto check = [](int x, int y) { return 0 <= x && x <= n && 0 <= y && y <= m; };

    deque<PII> q;
    dis[0][0] = 0, q.push_back({0, 0});
    while (q.size()) {
        auto [x, y] = q.front();
        q.pop_front();
        if (st[x][y]) continue;
        st[x][y] = 1;
        if (x == n && y == m) return dis[n][m];
        rep(i, 0, 3) {
            int xx = x + dx[i], yy = y + dy[i];
            if (!check(xx, yy)) continue;
            int w = a[x + ix[i]][y + iy[i]] != cd[i];
            if (chmin(dis[xx][yy], dis[x][y] + w)) {
                if (w) q.push_back({xx, yy});
                else q.push_front({xx, yy});
            }
        }
    }
    return dis[n][m];
}

void solve() {
    cin >> n >> m;
    rep(i, n) cin >> (a[i] + 1);
    if (n + m & 1) return print("NO SOLUTION");
    else return print(bfs());
}
```

#### [190. 字串变换](https://www.acwing.com/problem/content/192/)
##### 思路
比较标准的最小步数问题，可以用双端bfs进行优化，同时从两边开始扩展 
##### 蒟蒻代码
``` cpp
cint N = 10;
using msi = unordered_map<string, int>;

string a, b;
int n = 0;
string ra[N], rb[N];

int extend(queue<string> &q, msi &ma, msi &mb, string from[], string to[]) {
    string s = q.front();
    q.pop();
    rp(i, 0, s.size())
        rep(j, n) if (s.substr(i, from[j].size()) == from[j]) {
        string t = s.substr(0, i) + to[j] + s.substr(i + from[j].size());
        if (mb.count(t)) return ma[s] + 1 + mb[t];
        if (ma.count(t)) continue;
        ma[t] = ma[s] + 1, q.push(t);
    }
    return inf<int>;
}

int bfs(string sa, string sb) {
    if (sa == sb) return 0;

    unordered_map<string, int> ma, mb;
    queue<string> qa, qb;

    ma[sa] = 0, mb[sb] = 0, qa.push(sa), qb.push(sb);
    while (qa.size() && qb.size()) {
        int t = qa.size() <= qb.size() ? extend(qa, ma, mb, ra, rb) : extend(qb, mb, ma, rb, ra);
        if (t <= 10) return t;
    }
    return inf<int>;
}

void solve() {
    cin >> a >> b;
    while (cin >> ra[++n] >> rb[n]);
    int ans = bfs(a, b);
    if (ans > 10) print("NO ANSWER!");
    else print(ans);
}
```

#### [179. 八数码](https://www.acwing.com/problem/content/181/)
##### 思路
首先，对于奇数数码问题，问题可解等价于写成一行之后的序列逆序对的数量为偶数。这是因为考虑交换有两种，一种在行内交换，不会改变序列的顺序，所以逆序对数量不变，第二种上下交换，这种情况下，相当于把一个数移动了偶数次，已知一次移动会使逆序对数量改变1，因此移动偶数次不会改变逆序对的奇偶性，于是我们可以利用它来判断问题的可解性。

然后，针对有解的情况，我们使用 A\*算法。估价函数的设计，由于每次交换，最多使得一个数到它答案位置的曼哈顿距离-1，因此，我们设**估价函数为所有数字到正确位置的曼哈顿距离之和**，显然小于等于真正的步数，然后写A\*算法就行了。
##### 蒟蒻代码
``` cpp
using PIS = pair<int, string>;
cint dx[] = {0, 0, -1, 1};
cint dy[] = {-1, 1, 0, 0};
const string tar = "12345678x";
const string cd = "lrud";

string start;

void bfs(string s) {
    unordered_map<string, int> dis;
    unordered_map<string, pair<char, string>> p;
    priority_queue<PIS, vc<PIS>, greater<PIS>> q;

    auto check = [](int x, int y) { return x >= 0 && x < 3 && y >= 0 && y < 3; };

    auto f = [](string s) {
        int cnt = 0;
        rp(i, 0, s.size()) {
            if (s[i] == 'x') continue;
            int t = s[i] - '1';
            cnt += abs(i / 3 - t / 3) + abs(i % 3 - t % 3);
        }
        return cnt;
    };

    auto dfs = [&](auto &&self, string s) {
        if (s == start) return;
        self(self, p[s].se);
        wt(p[s].fi);
    };

    dis[s] = 0,
    q.push({f(s), s});
    while (q.size()) {
        string t = q.top().se;
        q.pop();
        if (t == tar) return dfs(t, dfs);

        int x, y;
        rp(i, 0, t.size()) if (t[i] == 'x') {
            x = i / 3, y = i % 3;
            break;
        }

        rep(i, 0, 3) {
            int xx = x + dx[i], yy = y + dy[i];
            if (!check(xx, yy)) continue;
            string tt = t;
            swap(tt[xx * 3 + yy], tt[x * 3 + y]);
            if (dis.count(tt) == 0 || dis[tt] > dis[t] + 1)
                dis[tt] = dis[t] + 1, p[tt] = {cd[i], t}, q.push({dis[tt] + f(tt), tt});
        }
    }
}

void solve() {
    string t;
    char c;
    while (cin >> c) {
        start += c;
        if (c != 'x') t += c;
    }
    int cnt = 0;
    rep(i, 0, 7) rep(j, i, 7) cnt += t[i] > t[j];
    if (cnt & 1) print("unsolvable");
    else bfs(start);
}
```


#### [178. 第K短路](https://www.acwing.com/problem/content/180/)
##### 思路
由于要搜索所有的路径，并且求第k短路径，搜索范围非常大，考虑使用 A\* 算法优化

由于估价函数要求小于等于实际的未来价值，我们**取 $f(u)$ 为 起点到 $u$ 的距离加上它 到终点的最短距离**，因此显然满足要求。

接下来我们考虑如何得到第k短路。首先估价函数保证了终点第一次从优先队列取出时一定是最短路，那么我们猜想当终点第 k 次从队列弹出时，就是第k短路。证明：最短路的时候的证明省略，我们考虑次短路，后面的同理。 假设第二次终点 $T$ 从优先队列弹出的不是次短路 $d_2$，那就意味着，存在在次短路路径上但是还在队列中的 $u$ 使得 $f(u)<d_2<f(T)$，与优先队列矛盾，因此第二次从小根堆弹出一定是次短路。因此，第k次弹出的是k短路。

为了求终点到所有点的距离，可以建一个反图，跑一遍dijkstra。然后容易想到的一个剪枝是当起点终点不连通的时候，一定不存在，所以可以在跑完之后直接判断。**一定要记住，A\* 算法在无解情况下会退化，所以能判断无解尽量判断。**

然后还有一个优化：因为是第k短路，所以路径上的中间点，最多只会出队k次，因为k条路径最多只会让一个中间点出现k次。（好像是可以严谨证明？但是我没细看ovo），但是这个Astar做法其实有点假，正解可以看oiwiki

*注意题目要求路径至少包含一条边，因此在起点和终点重合的时候，最短路是子环，不符合要求，因此要 `k++`*
##### 蒟蒻代码
``` cpp
cint N = 1005;

struct node {
    ll f, dis, ver;
    bool operator<(const node &p) const { return f > p.f; }
};

int n, m;
vpii g[N], gt[N];
int dis[N];

void add(vpii *g, int u, int v, int w) { g[u].push_back({v, w}); }

void dijkstra(vpii *g, int s) {
    rep(i, n) dis[i] = inf<int>;
    priority_queue<PII> q;
    bitset<N> st;
    dis[s] = 0, q.push({0, s});
    while (q.size()) {
        int u = q.top().se;
        q.pop();
        if (st[u]) continue;
        st[u] = 1;
        for (auto [v, w] : g[u])
            if (chmin(dis[v], dis[u] + w)) q.push({-dis[v], v});
    }
}

int bfs(int s, int e, int k) {
    if (dis[s] == inf<int>) return -1;
    auto f = [](int x, int d) { return dis[x] + d; };

    int cnt[N];
    priority_queue<node> q;
    q.push({f(s, 0), 0, s});
    while (q.size()) {
        auto [_, d, u] = q.top();
        q.pop();
        cnt[u]++;
        if (cnt[e] == k) return d;
        for (auto [v, w] : g[u])
            if (cnt[v] < k) q.push({f(v, d + w), d + w, v});
    }
    return -1;
}

void solve() {
    cin >> n >> m;
    rep(m) {
        int u, v, w;
        cin >> u >> v >> w;
        add(g, u, v, w), add(gt, v, u, w);
    }
    int s, e, k;
    cin >> s >> e >> k;
    if (s == e) k++;
    dijkstra(gt, e);
    print(bfs(s, e, k));
}
```

#### [1112. 迷宫](https://www.acwing.com/problem/content/1114/)
##### 思路
dfs模版题，记得考虑要不要回溯
##### 蒟蒻代码
``` cpp
cint N = 105;
cint dx[] = {0, 0, -1, 1};
cint dy[] = {-1, 1, 0, 0};

int n;
char a[N][N];
bool st[N][N];
PII s, e;

bool check(int x, int y) { return a[x][y] != '#' && 1 <= x && x <= n && 1 <= y && y <= n; }
bool dfs(PII p) {
    if (p == e) return 1;
    st[p.fi][p.se] = 1;
    rep(i, 0, 3) {
        int x = p.fi + dx[i], y = p.se + dy[i];
        if (!check(x, y)) continue;
        if (st[x][y]) continue;
        if (dfs({x, y})) return 1;
    }
    return 0;
}

void solve() {
    cin >> n;
    rep(i, n) cin >> (a[i] + 1);
    rep(i, n) rep(j, n) st[i][j] = 0;
    cin >> s.fi >> s.se >> e.fi >> e.se;
    s.fi++, s.se++, e.fi++, e.se++;
    if (!check(s.fi, s.se) || !check(e.fi, e.se)) return NO();
    if (dfs(s)) YES();
    else NO();
}
```
#### [1113. 红与黑](https://www.acwing.com/problem/content/1115/)
##### 思路
dfs基础题
##### 蒟蒻代码
``` cpp
cint N = 25;

int n, m, sx, sy, ans;
int dx[] = {0, 0, -1, 1}, dy[] = {-1, 1, 0, 0};
char a[N][N];
bool st[N][N];

bool check(int x, int y) { return !st[x][y] && 1 <= x && x <= n && 1 <= y && y <= m; }
void dfs(int x, int y) {
    if (st[x][y]) return;
    ans++, st[x][y] = 1;
    rep(i, 0, 3) {
        int xx = x + dx[i], yy = y + dy[i];
        if (check(xx, yy) && a[xx][yy] != '#') dfs(xx, yy);
    }
}

void solve() {
    while (cin >> m >> n, m || n) {
        ans = 0;
        rep(i, n) rep(j, m) {
            cin >> a[i][j];
            st[i][j] = 0;
            if (a[i][j] == '@') sx = i, sy = j;
        }
        dfs(sx, sy);
        print(ans);
    }
}
```
#### [1116. 马走日](https://www.acwing.com/problem/content/1118/)
##### 思路
dfs模板题，但是注意这里求的是路径的总数，所以扩展完之后注意要还原！因为上次搜的路径和这次不一样
##### 蒟蒻代码
``` cpp
cint N = 11;

int n, m, sx, sy, ans;
int dx[] = {-1, -1, 1, 1, -2, -2, 2, 2}, dy[] = {2, -2, 2, -2, 1, -1, 1, -1};
bool st[N][N];

bool check(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= m; }
void dfs(int x, int y, int cnt) {
    if (cnt == n * m) {
        ans++;
        return;
    }
    rep(i, 0, 7) {
        int a = x + dx[i], b = y + dy[i];
        if (!check(a, b)) continue;
        if (st[a][b]) continue;
        st[a][b] = 1;
        dfs(a, b, cnt + 1);
        st[a][b] = 0;
    }
}

void solve() {
    cin >> n >> m >> sx >> sy;
    sx++, sy++, ans = 0;
    mset(st, 0);
    st[sx][sy] = 1;
    dfs(sx, sy, 1);
    print(ans);
}
```
#### [1117. 单词接龙](https://www.acwing.com/problem/content/1119/)
##### 思路
BF，注意在求最长的长度的时候我们尽量让重合的部分最短，这是一个小贪心，这样可以让最后的拼出来的字符串最长；注意每个字符串可以最多用两次
##### 蒟蒻代码
``` cpp
cint N = 25;

int n;
string a[N];
int st[N];
char start;

int check(string x, string y) {
    int t = x.size();
    pr(i, t, 1) if (x.substr(i) == y.substr(0, t - i)) return t - i;
    return 0;
}
int dfs(string s, int cnt) {
    int ret = cnt;
    rep(i, n) {
        if (st[i] == 2) continue;
        int t = check(s, a[i]);
        if (!t) continue;
        st[i]++;
        chmax(ret, dfs(a[i], cnt + a[i].size() - t));
        st[i]--;
    }
    return ret;
}

void solve() {
    cin >> n;
    rep(i, n) cin >> a[i];
    cin >> start;
    int ans = -1;
    rep(i, n) {
        if (a[i][0] == start) {
            mset(st, 0);
            st[i] = 1;
            chmax(ans, dfs(a[i], a[i].size()));
        }
    }
    print(ans);
}
```
#### [1118. 分成互质组](https://www.acwing.com/problem/content/description/1120/)
##### 思路
一定要跳出排列思维！！！用组合的写法，就是groups的顺序无所谓，要考虑的是本质不同的组！这里的k表示当前要考虑第k个数字放到哪个组，并且前k-1个数字已经放好了
##### 蒟蒻代码
``` cpp
cint N = 15;

int n, a[N];
int ans = inf<int>;

void dfs(vi groups, int k) {
    if (groups.size() >= ans) return;
    if (k == n + 1) {
        chmin(ans, groups.size());
        return;
    }
    rp(i, 0, groups.size()) {
        if (gcd(groups[i], a[k]) > 1) continue;
        groups[i] *= a[k];
        dfs(groups, k + 1);
        groups[i] /= a[k];
    }
    groups.push_back(a[k]);
    dfs(groups, k + 1);
    groups.pop_back();
}

void solve() {
    cin >> n;
    rep(i, n) cin >> a[i];
    dfs({}, 1);
    print(ans);
}
```
#### [165. 小猫爬山](https://www.acwing.com/problem/content/167/)
##### 思路
枚举的时候，以当前小猫放入哪一个缆车里，或者新开一辆缆车为顺序。
剪枝考虑：1、最优化剪枝  2、将猫的体重从大到小排序，因为胖猫对应的缆车坐的数量肯定较少，所以前面繁琐的枚举哪一辆缆车就会少了很多
##### 蒟蒻代码
``` cpp
cint N = 25;

int n, w, a[N];
int ans = inf<int>;

void dfs(vi cables, int k) {
    if (cables.size() >= ans) return;
    if (k == n + 1) chmin(ans, cables.size());
    rp(i, 0, cables.size()) {
        if (cables[i] + a[k] > w) continue;
        cables[i] += a[k];
        dfs(cables, k + 1);
        cables[i] -= a[k];
    }
    cables.push_back(a[k]);
    dfs(cables, k + 1);
    cables.pop_back();
}

void solve() {
    cin >> n >> w;
    rep(i, n) cin >> a[i];
    sort(all(a, n), greater<int>());
    dfs({}, 1);
    print(ans);
}
```
#### [166. 数独](https://www.acwing.com/problem/content/168/)
##### 思路
剪枝：
1. 搜索顺序，考虑每次从可能的情况数**最少**的格子进行扩展 
2. 利用位运算和lowbit加速判断数字是否使用过

u1s1，这代码写的真的太艺术了，哎哟

首先为了使用lowbit来取，我们要求1表示空闲位置，0表示选中的位置，这样，就可以每次取出1的位置，然后取log的部分我们可以事先打表，然后由于我们要取出空闲位置，也就是能填的数字最少的数字，需要求出每个数字里面1的个数，这个也可以事先打表，然后要考虑每行每列每个九宫格每个数字是否出现，所以开数组记录，每次填的时候把数字的位设为0，不然设为1，也就是设置的时候把那位的二进制减掉，还原的时候把那位加回来，其实用位运算就行，哦对哦，用位运算就行。。。南奔，没动脑子了。额，然后注意代码的模块化，把每个小组件可以分开来，总之这个代码写的确实很艺术了。

dfs返回值写bool是为了在找到解之后，就可以返回了，因为题目保证唯一解。
##### 蒟蒻代码
``` cpp
cint N = 9, M = 1 << N;

int ones[M], lg[M];
// 1 not used 0 used
int row[N], col[N], cell[3][3];
string s;

int lowbit(int x) { return x & (-x); }

void init() {
    rp(i, 0, N) row[i] = col[i] = (1 << N) - 1;
    rp(i, 0, 3) rp(j, 0, 3) cell[i][j] = (1 << N) - 1;
}

int get(int x, int y) { return row[x] & col[y] & cell[x / 3][y / 3]; }

void draw(int x, int y, int d, bool flg) {
    if (flg) s[x * N + y] = d + '1';
    else s[x * N + y] = '.';
    int t = 1 << d;
    if (!flg) t = -t;
    row[x] -= t, col[y] -= t, cell[x / 3][y / 3] -= t;
}

bool dfs(int cnt) {
    if (cnt == 0) return 1;

    int mn = inf<int>, x, y;
    rp(i, 0, N) rp(j, 0, N) {
        if (s[i * N + j] == '.' && chmin(mn, ones[get(i, j)]))
            x = i, y = j;
    }
    int state = get(x, y);
    for (int i = state; i; i -= lowbit(i)) {
        int t = lowbit(i);
        draw(x, y, lg[t], 1);
        if (dfs(cnt - 1)) return 1;
        draw(x, y, lg[t], 0);
    }
    return 0;
}

void solve() {
    rp(i, 0, N) lg[1 << i] = i;
    rp(i, 0, 1 << N) rp(j, 0, N) ones[i] += i >> j & 1;

    while (cin >> s, s != "end") {
        init();
        int cnt = 0;
        rp(i, 0, N) rp(j, 0, N) {
            int t = i * N + j;
            if (s[t] == '.') cnt++;
            else draw(i, j, s[t] - '1', 1);
        }
        dfs(cnt);
        print(s);
    }
}
```
#### [167. 木棒](https://www.acwing.com/problem/content/169/)
##### 思路
考虑枚举最终木棒的长度，然后依次**拼好每一根木棒**

剪枝:
1. 最终木棒的长度一定整除木棒的总长
2. 优化搜索顺序，我们要前面扩展比较少，后面扩展比较多的分支，那就是木棍长度大的，因为他长度大就会先塞满，后面能扩展的空间就会比较少，所以我们先对木棍长度从大到小排序
3. 排除等效冗余
   1. 按照组合的方式进行枚举
   2. 如果当前木棍没有搜到方案，则跳过所有长度相等的木棍
   3. 如果是木棒的第一根木棍就搜索失败了，则一定搜不到方案。因为如果第一根木棍失败了，但是如果他放到后面可行的话，我们可以把它交换到第一根的位置，并且交换到先前的位置，就得到了一个可行的方案，矛盾。
   4. 如果是木棒的最后一根木棍（+ 上它木棒长度正好是 length）搜索失败了，也一定搜不到方案。证明和上一个类似
    
##### 蒟蒻代码
``` cpp
cint N = 70;

int n, a[N];
int len, tot = 0;
bitset<N> used;

bool dfs(int st, int sl, int k) {
    if (st * len == tot) return 1;
    if (sl == len) return dfs(st + 1, 0, 1);
    rep(i, k, n) { // 组合型枚举
        if (used[i]) continue;
        if (sl + a[i] > len) continue;

        used[i] = 1;
        if (dfs(st, sl + a[i], k + 1)) return 1;
        used[i] = 0;

        // 作为木棒的第一根失败了，就失败了
        if (!sl) return 0;
        // 作为最后一根失败了，就失败了
        if (sl + a[i] == len) return 0;

        // 当前长度失败了，相同的长度也会失败
        int j = i;
        while (j <= n && a[j] == a[i]) j++;
        i = j - 1;
    }
    return 0;
}

void solve() {
    while (cin >> n, n) {
        len = 1, tot = 0, used &= 0;
        rep(i, n) cin >> a[i], tot += a[i];
        sort(all(a, n), greater<int>());
        while (len <= tot) {
            if (tot % len == 0 && dfs(0, 0, 1)) {
                print(len);
                break;
            }
            len++;
        }
    }
}
```
#### [168. 生日蛋糕](https://www.acwing.com/problem/content/170/)
##### 思路
将第 $i$ 层的半径记作 $r_i$，高度记作 $h_i$ ，从上到下依次是 $1,2, \ldots ,m$ 层

剪枝：
1. 优化搜索顺序，先枚举底部半径较大的部分，在同一层里，先枚举半径再枚举高度，因为半径是平方级别的，同时应该是从大到小枚举。
2. 可行性剪枝：如果当前是第 $u$ 层，那么 $u\le r_u\le r_{u+1}-1$，再由体积可知 $r_u^{2}\le r_u^{2}h_u\le n-v$，因此 $u\le r_u\le \min\{ \sqrt{n-v},r_{u+1}-1 \}$，其中 $v$ 是已经做好的体积，同理 $u \le h_u\le \min\{ h_{u+1}-1,(n-v)r_u^{-2} \}$
3. 最优化剪枝：预处理前 $u$ 层体积的最小值和表面积最小值。就是说当前的体积加上上面的体积最小值一定要小于等于 $n$ 才可行，同时，当前的表面积加上上面的表面积最小值一定要小于现在的ans才有可能产生新的ans，否则可以进行剪枝
4. 前 $u$ 层的表面积和体积分别是是 $S_{1 \sim u}=\sum_{i=1}^{u}2 r_i h_i$, $V_{1 \sim u}=n-v=\sum_{i=1}^{u} r_i^{2}h_i$，考虑如下变形:
   $$
   S_{1 \sim u}=\sum_{i=1}^{u}2 r_i h_i=\frac{2}{r_{u+1}}\sum_{i=1}^{u}r_ir_{u+1}h_i>\frac{2}{r_{u+1}}\sum_{i=1}^{u}r_i^{2}h_i=\frac{2(n-v)}{r_{u+1}}
   $$
所以，如果当前面积加上 $2(n-v) / r_{u+1}$ 已经大于等于ans了，说明不可能更新ans了
##### 蒟蒻代码
``` cpp
cint N = 30;

int n, m, mins[N], minv[N], r[N], h[N];
int ans = inf<int>;

void dfs(int u, int v, int s) {
    if (v + minv[u] > n) return;
    if (s + mins[u] >= ans) return;
    if (s + 2 * (n - v) / r[u + 1] >= ans) return;
    if (!u) {
        if (v == n) chmin(ans, s);
        return;
    }
    per(rr, min(r[u + 1] - 1, (int)sqrt(n - v)), u) {
        per(hh, min((ll)h[u + 1] - 1, (n - v) / rr / rr), u) {
            int t = 0;
            if (u == m) t = rr * rr;
            r[u] = rr, h[u] = hh;
            dfs(u - 1, v + rr * rr * hh, s + 2 * rr * hh + t);
        }
    }
}

void solve() {
    cin >> n >> m;
    rep(i, m) {
        minv[i] = minv[i - 1] + i * i * i;
        mins[i] = mins[i - 1] + 2 * i * i;
    }
    r[m + 1] = h[m + 1] = inf<int>;
    dfs(m, 0, 0);
    if (ans == inf<int>) print(0);
    else print(ans);
}
```
#### [170. 加成序列](https://www.acwing.com/problem/content/172/)
##### 思路
迭代加深

剪枝：
1、每次优先枚举较大的数字
2、排除等效冗余 比如1+4 2+3 都是 5
##### 蒟蒻代码
``` cpp
cint N = 105;

int n, a[N];

bool dfs(int u, int dep) {
    if (u > dep) return 0;
    bitset<N> st;
    per(i, u - 1, 1) per(j, i, 1) {
        int t = a[i] + a[j];
        if (t > n || t < a[u - 1] || st[t]) continue;
        st[t] = 1, a[u] = t;
        if (a[u] == n) return 1;
        if (dfs(u + 1, dep)) return 1;
        st[t] = 0;
    }
    return 0;
}

void solve() {
    while (cin >> n, n) {
        if (n == 1) {
            print(1);
            continue;
        }
        a[1] = 1;
        int depth = 1;
        while (!dfs(2, depth)) depth++;
        aprint(a, 1, depth);
    }
}
```
#### [171. 送礼物](https://www.acwing.com/problem/content/173/)
##### 思路
dp做法时间复杂度是 $O(NV)$ 超时了，考虑暴力枚举，就是枚举每个物品选或者不选，直接枚举时间复杂度是 $O(2^{N})$ 爆了，所以可以用双向dfs，第一次处理前一半，然后后一半暴力的时候二分前一半里面加起来不超过 $w$ 的最大的数，时间复杂度为 $O(2^{N / 2}+2^{N / 2}\cdot \log 2^{N / 2})=O(N\cdot 2^{N / 2})$，实际上是 $O(2^{k}+k\cdot 2^{N-k})$ 可以玄学调一下两个的比例。
优化搜索顺序，先从大到小排序，然后显然前一半打表的时候用大的打比较好，然后只要答案已经可以取到w了，就别的都不用搜了，因为顶天就是w，然后每次更新答案的时候只用看当前选了的情况，因为没选情况在之前就更新过了。
##### 蒟蒻代码
``` cpp
cint N = 50;

ll n, w, a[N];
ll sz = 0, mp[1 << 23];
ll ans = 0;

void table(int u, const int r) {
    if (u > r) return;
    ll m = sz;
    rep(i, 0, m) if (mp[i] + a[u] <= w) mp[++sz] = mp[i] + a[u];
    table(u + 1, r);
}

bool dfs(int u, ll sum) {
    if (ans == w) return 1;
    if (sum > w) return 0;
    if (u > n) {
        if (sum + mp[sz] <= w) chmax(ans, sum + mp[sz]);
        else {
            ll l = 0, r = sz;
            while (l < r) {
                ll mid = (l + r + 1) >> 1;
                if (mp[mid] + sum <= w) l = mid;
                else r = mid - 1;
            }
            chmax(ans, sum + mp[l]);
        }
        return ans == w;
    }
    if (dfs(u + 1, sum)) return 1;
    if (dfs(u + 1, sum + a[u])) return 1;
    return 0;
}

void solve() {
    cin >> w >> n;
    rep(i, n) cin >> a[i];

    sort(all(a, n), greater<int>());
    ll mid = n >> 1;
    table(1, mid);
    sort(all(mp, sz));
    sz = unique(all(mp, sz)) - mp - 1;

    dfs(mid + 1, 0);
    print(ans);
}
```
#### [180. 排书](https://www.acwing.com/problem/content/description/182/)
##### 思路
直接爆搜会超时，证明的话可以考虑每次搜索的时候扩展的分支数量，做法是考虑移动长度为 $i$ 的区间有多少种移动的方法，然后全部相加。

可以使用双向bfs，但是在这里使用idastar。接下来我们来看估价函数。

注意到，排好序的数组，每个数的后继都是大于他自己的，而每次移动一段数字，最多改变3个数字的后继，也就是移动区间的端点处和移动到的位置的端点处。因此可以设计**估价函数**为：所有后继不是自己+1的个数除以3向上取整，也就是到最终状态最少要交换的次数。
##### 蒟蒻代码
``` cpp
cint N = 20;

int n, a[N];
int tmp[N];

int f() {
    int ret = 0;
    rep(i, 1, n - 1) ret += a[i + 1] != a[i] + 1;
    return ceil((double)ret / 3);
}

// q 从 l 开始 len 的区间放到 k 后面
void change(int *q, int l, int len, int k) {
    int tot = k - l + 1, i = 1, j;
    for (j = l + len; j <= k; j++, i++) tmp[i] = q[j];
    for (j = l; j < len + l; j++, i++) tmp[i] = q[j];
    for (i = 1, j = l; i <= tot; i++, j++) q[j] = tmp[i];
}

bool dfs(int u, const int dep) {
    if (u + f() > dep) return 0;
    if (f() == 0) return 1;

    rep(len, 1, n - 1) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            for (int k = r + 1; k <= n; k++) {
                int tot = k - l + 1;
                change(a, l, len, k);
                if (dfs(u + 1, dep)) return 1;
                change(a, l, tot - len, k);
            }
        }
    }
    return 0;
}

void solve() {
    cin >> n;
    rep(i, n) cin >> a[i];
    int depth = 0;
    while (depth < 5 && !dfs(0, depth)) depth++;
    if (depth >= 5) print("5 or more");
    else print(depth);
}
```
#### [181. 回转游戏](https://www.acwing.com/problem/content/183/)
##### 思路
因为可以来回拉扯，所以搜索树可能非常深，但是答案有可能非常浅，所以考虑迭代加深。

接下来，我们给他一个估价函数来让他进化。由于每一次的拉扯，最多只会改变中间8个格子中的一个，所以我们可以设计估价函数为8捡起中间8个格子中出现次数最多的数字出现的次数。枚举操作的时候，不能和上一次操作为逆操作。

**比较复杂的操作可以给操作打表。**我还是那句话，代码太漂亮了。。。。
##### 蒟蒻代码
```cpp
cint N = 24;

int op[8][7] = {
    {0, 2, 6, 11, 15, 20, 22},
    {1, 3, 8, 12, 17, 21, 23},
    {10, 9, 8, 7, 6, 5, 4},
    {19, 18, 17, 16, 15, 14, 13},
    {23, 21, 17, 12, 8, 3, 1},
    {22, 20, 15, 11, 6, 2, 0},
    {13, 14, 15, 16, 17, 18, 19},
    {4, 5, 6, 7, 8, 9, 10}};

int oppsite[8] = {5, 4, 7, 6, 1, 0, 3, 2};
int center[8] = {6, 7, 8, 11, 12, 15, 16, 17};

int a[N];
int path[100];

int f() {
    int cnt[4] = {0};
    rp(i, 0, 8) cnt[a[center[i]]]++;
    return 8 - MAX(cnt, 3);
}

void operate(int x) {
    int t = a[op[x][0]];
    rep(i, 0, 5) a[op[x][i]] = a[op[x][i + 1]];
    a[op[x][6]] = t;
}

bool dfs(int u, const int dep, int last) {
    if (u + f() > dep) return 0;
    if (f() == 0) return 1;
    rp(i, 0, 8) if (oppsite[i] != last) {
        operate(i);
        path[u] = i;
        if (dfs(u + 1, dep, i)) return 1;
        operate(oppsite[i]);
    }
    return 0;
}

void solve() {
    while (cin >> a[0], a[0]) {
        rp(i, 1, N) cin >> a[i];
        int depth = 0;
        while (!dfs(0, depth, -1)) depth++;
        if (depth == 0) wt("No moves needed");
        else rp(i, 0, depth) cout << (char)('A' + path[i]);
        print(), print(a[6]);
    }
}
```
