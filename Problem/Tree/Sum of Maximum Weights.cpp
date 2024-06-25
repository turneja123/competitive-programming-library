//https://atcoder.jp/contests/abc214/tasks/abc214_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int R = 1e7 + 5;

int parent[N];
vector<pair<int, int>> adj[N];
map<int, int> mp[N];

long long ans = 0;

struct Node {
    int ct;
    long long sum;
    struct Node* left;
    struct Node* right;
};

struct Node* root[N];

long long query_sum(Node* node, int l, int r, int lq, int rq) {
    if (lq <= l && rq >= r) {
        return node->sum;
    }
    if (r < lq || l > rq) {
        return 0;
    }
    int mid = (l + r) / 2; long long qans = 0;
    if (node->left != nullptr) {
        qans += query_sum(node->left, l, mid, lq, rq);
    }
    if (node->right != nullptr) {
        qans += query_sum(node->right, mid + 1, r, lq, rq);
    }
    return qans;

}

int query_ct(Node* node, int l, int r, int lq, int rq) {
    if (lq <= l && rq >= r) {
        return node->ct;
    }
    if (r < lq || l > rq) {
        return 0;
    }
    int mid = (l + r) / 2, qans = 0;
    if (node->left != nullptr) {
        qans += query_ct(node->left, l, mid, lq, rq);
    }
    if (node->right != nullptr) {
        qans += query_ct(node->right, mid + 1, r, lq, rq);
    }
    return qans;

}

void update(Node* node, int l, int r, int ind, int val) {
    if (l == r) {
        node->ct += val;
        node->sum += (long long)ind * val;
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        if (node->left == nullptr) {
            node->left = new Node();
        }
        update(node->left, l, mid, ind, val);
    } else {
        if (node->right == nullptr) {
            node->right = new Node();
        }
        update(node->right, mid + 1, r, ind, val);
    }
    node->ct = 0;
    node->sum = 0;
    if (node->left != nullptr) {
        node->ct += node->left->ct;
        node->sum += node->left->sum;
    }
    if (node->right != nullptr) {
        node->ct += node->right->ct;
        node->sum += node->right->sum;
    }
}

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b) {
    if (mp[a].size() > mp[b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    for (auto it = mp[a].begin(); it != mp[a].end(); ++it) {
        ans += (long long)query_sum(root[b], 0, R - 1, it->first + 1, R - 1) * it->second;
        ans += (long long)query_ct(root[b], 0, R - 1, 0, it->first) * it->first * it->second;
    }
    for (auto it = mp[a].begin(); it != mp[a].end(); ++it) {
        mp[b][it->first] += it->second;
        update(root[b], 0, R - 1, it->first, it->second);
    }
    return;
}

void dfs(int u, int p) {
    for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
        int v = it->first, wt = it->second;
        if (v != p) {
            dfs(v, u);
            int a = dsu_find(v), ct = 1;
            while (mp[a].size() && mp[a].begin()->first < wt) {
                ct += mp[a].begin()->second;
                update(root[a], 0, R - 1, mp[a].begin()->first, -mp[a].begin()->second);
                mp[a].erase(mp[a].begin());
            }
            update(root[a], 0, R - 1, wt, ct);
            mp[a][wt] += ct;
            ans += root[a]->sum;
        }
    }
    for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
        int v = it->first;
        if (v != p) {
            int a = dsu_find(u), b = dsu_find(v);
            dsu_merge(a, b);
        }
    }
    return;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back(make_pair(v, wt));
        adj[v].push_back(make_pair(u, wt));
    }

    for (int i = 0; i < n; i++) {
        root[i] = new Node();
        parent[i] = i;
    }
    dfs(0, 0);
    cout << ans;
    return 0;
}
