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
- prim算法
  - 朴素版本（邻接矩阵） $O(n^{2})$
  - 维护一个已经在mst中的集合，每次贪心加入**到这个集合距离最短的点**。
  - 堆优化版本
- kruskal算法 
  - 直接存边
  - 时间复杂度 $O(m\log m)$
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
必须要用的边直接加到mst中，剩下的继续kruskal
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
每个格点看成一个点，然后手动建图即可，已经联通的点既可以直接放到一个并查集里面，也可以设为边权为0的边。
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
