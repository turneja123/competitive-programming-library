//https://dmoj.ca/problem/dmpg15g3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int MAX = 5e6 + 5;

string s;

int lk, rk, lc, rc;

int sz[N];
bool seen_c[N];
int parent_c[N];

vector<int> adj[N];
vector<tuple<int, int, int>> events;
vector<tuple<int, int, int, int, int>> queries;

long long ans = 0;


bool comp(tuple<int, int, int, int, int> &a, tuple<int, int, int, int, int> &b) {
    return get<1>(a) < get<1>(b);
}

struct Node {
    int val;
    int left;
    int right;
    Node() : val(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int root[N];
int idx = 0;
int mx = 0;

int query(int node, int l, int r, int lq, int rq) {
    if (r < lq || l > rq) {
        return 0;
    }
    if (lq <= l && rq >= r) {
        return nodes[node].val;
    }
    int mid = (l + r) / 2, ans = 0;
    if (nodes[node].left != -1) {
        ans += query(nodes[node].left, l, mid, lq, rq);
    }
    if (nodes[node].right != -1) {
        ans += query(nodes[node].right, mid + 1, r, lq, rq);
    }
    return ans;

}

void update(int node, int l, int r, int ind, int val) {
    if (l == r) {
        nodes[node].val += val;
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        update(nodes[node].left, l, mid, ind, val);
    } else {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        update(nodes[node].right, mid + 1, r, ind, val);
    }
    nodes[node].val = 0;
    if (nodes[node].left != -1) {
        nodes[node].val += nodes[nodes[node].left].val;
    }
    if (nodes[node].right != -1) {
        nodes[node].val += nodes[nodes[node].right].val;
    }
}

void dfs_subtree(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_subtree(v, u);
            sz[u] += sz[v];
        }
    }
    return;
}

int dfs_centroid(int u, int p, int n) {
    for (int v : adj[u]) {
        if (v != p && !seen_c[v] && sz[v] > n / 2) {
            return dfs_centroid(v, u, n);
        }
    }
    return u;
}

void dfs_depth1(int u, int p, int entry, int c, int K, int C) {
    if (s[u] == 'K') {
        K++;
    } else {
        C++;
    }
    mx = max(mx, C);
    if (K >= lk && K <= rk && C >= lc && C <= rc) {
        ans += 2;
    }
    events.push_back(make_tuple(K, C, entry));
    int ck = s[c] == 'K', cc = s[c] == 'C';

    int LK = max(0, lk - K + ck), RK = rk - K + ck, LC = max(0, lc - C + cc), RC = rc - C + cc;
    if (LK <= RK && LC <= RC) {
        queries.push_back(make_tuple(LK, RK, LC, RC, entry));
    }
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_depth1(v, u, entry, c, K, C);
        }
    }

    return;
}

void build(int u, int p) {
    dfs_subtree(u, u);
    int c = dfs_centroid(u, u, sz[u]);
    if (p == -1) {
        p = c;
    }
    parent_c[c] = p;
    seen_c[c] = true;
    idx = 0;
    root[c] = idx;
    nodes[idx++] = Node();
    int K = s[c] == 'K';
    int C = s[c] == 'C';
    mx = C;
    if (K >= lk && K <= rk && C >= lc && C <= rc) {
        ans += 2;
    }
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            root[v] = idx;
            nodes[idx++] = Node();
            dfs_depth1(v, v, v, c, K, C);
        }
    }

    sort(events.begin(), events.end());
    sort(queries.begin(), queries.end(), comp);
    int l = 0, r = 0;
    for (int i = 0; i < queries.size(); i++) {
        auto [LK, RK, LC, RC, entry] = queries[i];
        while (r < events.size() && get<0>(events[r]) <= RK) {
            update(root[c], 0, mx, get<1>(events[r]), 1);
            update(root[get<2>(events[r])], 0, mx, get<1>(events[r]), 1);
            r++;
        }
        while (l < r && get<0>(events[l]) < LK) {
            update(root[c], 0, mx, get<1>(events[l]), -1);
            update(root[get<2>(events[l])], 0, mx, get<1>(events[l]), -1);
            l++;
        }
        ans += query(root[c], 0, mx, LC, RC) - query(root[entry], 0, mx, LC, RC);
    }
    events.clear();
    queries.clear();
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            build(v, c);
        }
    }
    return;
}

int main() {
    IOS;
    int n;
    cin >> n >> lk >> rk >> lc >> rc;
    cin >> s;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    build(0, -1);
    cout << ans / 2;


    return 0;
}
