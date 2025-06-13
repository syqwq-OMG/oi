#include <algorithm>
#include <bitset>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
using namespace std;

const int null = 0x7f7f7f7f;
const int N = 1e4 + 5;

struct node {
    int val;
    node *l;
    node *r;
    node() {
        l = NULL;
        r = NULL;
    }
    node(int val) : val(val) {}
};

int n;
int in[N], post[N];

node *build(int il, int ir, int pl, int pr) {
    if (il > ir)
        return NULL;
    node *root = new node(post[pr]);
    int mid = il;
    while (mid <= ir) {
        if (in[mid] == post[pr])
            break;
        mid++;
    }
    root->l = build(il, mid - 1, pl, pl - il + mid - 1);
    root->r = build(mid + 1, ir, pr + mid - ir, pr - 1);
    return root;
}

void bfs(node *root) {
    queue<node *> q;
    q.push(root);
    while (q.size()) {
        auto p = q.front();
        q.pop();
        cout << p->val << " ";
        if (p->l != NULL)
            q.push(p->l);

        if (p->r != NULL)
            q.push(p->r);
    }
}

int main() {
    cin >> n;
    rep(i, 1, n) cin >> in[i];
    rep(i, 1, n) cin >> post[i];

    node *root = build(1, n, 1, n);
    bfs(root);
    return 0;
}
