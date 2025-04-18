//https://www.hackerearth.com/practice/data-structures/advanced-data-structures/segment-trees/practice-problems/algorithm/do-you-order-queries-27a70fdd/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

const int L = -1e9, R = 1e9;
const int MAX = 1e7;
const long long INF = 2e18;

struct Line {
    long long k, b;
    long long f(long long x) {
        return k * x + b;
    }
    Line(long long k, long long b) : k(k), b(b) {}
};

struct Node {
    Line line;
    int left;
    int right;
    Node(Line line) : line(line), left(-1), right(-1) {}
    Node() : line(0, -INF), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;
int root = 0;

vector<int> restore;
vector<tuple<int, int>> queries[N];
vector<pair<int, int>> segtree[4 * N];
long long ans[N];

int add(int l, int r, int node, Line cur) {
    if (l > r) {
        return -1;
    }
    int mid = (l + r) / 2;
    if (r - l == 1 && mid == r) {
        mid--;
    }
    bool lf = cur.f(l) > nodes[node].line.f(l);
    bool md = cur.f(mid) > nodes[node].line.f(mid);
    nodes[idx] = Node();
    nodes[idx].left = nodes[node].left;
    nodes[idx].right = nodes[node].right;
    nodes[idx].line = nodes[node].line;
    if (md) {
        nodes[idx].line = cur;
        cur = nodes[node].line;
    }
    node = idx++;
    if (l == r) {
        return node;
    }
    if (lf != md) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node(cur);
        } else {
            nodes[node].left = add(l, mid, nodes[node].left, cur);
        }
    } else {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node(cur);
        } else {
            nodes[node].right = add(mid + 1, r, nodes[node].right, cur);
        }
    }
    return node;
}

long long query(int l, int r, int node, long long x) {
    if (l > r) {
        return -INF;
    }
    int mid = (l + r) / 2;
    if (r - l == 1 && mid == r) {
        mid--;
    }
    long long ans = nodes[node].line.f(x);
    if (l == r) {
        return ans;
    }
    if (x <= mid && nodes[node].left != -1) {
        ans = max(ans, query(l, mid, nodes[node].left, x));
    }
    if (x > mid && nodes[node].right != -1) {
        ans = max(ans, query(mid + 1, r, nodes[node].right, x));
    }
    return ans;
}

void upd(int l, int r, int lq, int rq, pair<int, int> edge, int node) {
    if (r < lq || l > rq) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].push_back(edge);
        return;
    }
    int mid = (l + r) / 2;
    upd(l, mid, lq, rq, edge, 2 * node + 1);
    upd(mid + 1, r, lq, rq, edge, 2 * node + 2);
    return;
}

void dfs(int l, int r, int node) {
    int ct = 0;
    for (auto [u, v] : segtree[node]) {
        ct++;
        restore.push_back(root);
        Line line = Line(u, v);
        root = add(L, R, root, line);
    }
    if (l == r) {
        for (auto [a, ind] : queries[l]) {
            ans[ind] = query(L, R, root, a);
        }
    } else {
        int mid = (l + r) / 2;
        dfs(l, mid, 2 * node + 1);
        dfs(mid + 1, r, 2 * node + 2);
    }
    for (int i = 0; i < ct; i++) {
        root = restore.back();
        restore.pop_back();
        idx = min(idx, root + 100);
    }
    return;
}

int main() {
    IOS;
    nodes[idx] = Node();
    restore.push_back(idx++);
    int q;
    cin >> q;
    map<int, pair<int, int>> mp;
    vector<tuple<int, int, int, int>> edges;
    int j = 0;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int a, b;
            cin >> a >> b;
            mp[i] = make_pair(a, b);
        } else if (t == 2) {
            int k;
            cin >> k;
            k--;
            auto it = mp.find(k);
            edges.push_back(make_tuple(it->second.first, it->second.second, it->first, i - 1));
            mp.erase(it);
        } else {
            int a;
            cin >> a;
            queries[i].push_back(make_tuple(a, j++));
        }
    }
    while (mp.size()) {
        auto [u, v] = mp.begin()->second;
        edges.push_back(make_tuple(u, v, mp.begin()->first, q));
        mp.erase(mp.begin());
    }
    for (auto [u, v, l, r] : edges) {
        upd(0, q, l, r, {u, v}, 0);
    }
    dfs(0, q, 0);
    for (int i = 0; i < j; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
