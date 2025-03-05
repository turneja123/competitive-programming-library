//https://arena.petlja.org/sr-Latn-RS/competition/bubblecup17finals#tab_136696
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    pair<long long, int> key;
    long long sum;
    int priority;
    int cnt;
    Node* left;
    Node* right;

    Node(pair<long long, int> key) : key(key), sum(key.first), priority(generator()), cnt(1), left(nullptr), right(nullptr) {}
};

Node* root[N];

long long a[N];
long long sz[N];

int dsu[N];
int parent[N];
vector<int> adj[N];
vector<pair<int, int>> queries[N];
long double ans[N];
set<pair<long long, int>> st[N];


int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

long long get_sum(Node* node) {
    return node ? node->sum : 0;
}

void upd_cnt(Node* node) {
    if (node) {
        node->cnt = 1 + get_cnt(node->left) + get_cnt(node->right);
        node->sum = node->key.first + get_sum(node->left) + get_sum(node->right);
    }
}

void split(Node* node, pair<long long, int> key, Node*& left, Node*& right) {
    if (!node) {
        left = right = nullptr;
        return;
    }
    if (node->key > key) {
        split(node->right, key, node->right, right);
        left = node;
    } else {
        split(node->left, key, left, node->left);
        right = node;
    }
    upd_cnt(node);
}

void split_by_ind(Node* node, int k, Node*& left, Node*& right) {
    if (!node) {
        left = right = nullptr;
        return;
    }
    if (get_cnt(node->left) >= k) {
        split_by_ind(node->left, k, left, node->left);
        right = node;
    } else {
        split_by_ind(node->right, k - get_cnt(node->left) - 1, node->right, right);
        left = node;
    }
    upd_cnt(node);
}

Node* merge(Node* left, Node* right) {
    if (!left || !right) {
        return left ? left : right;
    }
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        upd_cnt(left);
        return left;
    } else {
        right->left = merge(left, right->left);
        upd_cnt(right);
        return right;
    }
}

Node* insert(Node* root, Node* node) {
    if (!root) {
        return node;
    }
    if (node->priority > root->priority) {
        split(root, node->key, node->left, node->right);
        upd_cnt(node);
        return node;
    } else if (node->key > root->key) {
        root->left = insert(root->left, node);
    } else {
        root->right = insert(root->right, node);
    }
    upd_cnt(root);
    return root;
}

Node* erase(Node* root, pair<long long, int> key) {
    if (!root)
        return root;
    if (key > root->key) {
        root->left = erase(root->left, key);
    } else if (key < root->key) {
        root->right = erase(root->right, key);
    } else {
        Node* temp = merge(root->left, root->right);
        //delete root;
        return temp;
    }
    upd_cnt(root);
    return root;
}

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b) {
    if (st[a].size() > st[b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    for (auto it = st[a].begin(); it != st[a].end(); ++it) {
        st[b].insert(*it);
        root[b] = insert(root[b], new Node(*it));
    }
    return;
}

void dfs(int u, int p) {
    sz[u] = a[u];
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
    for (int v : adj[u]) {
        if (v != p) {
            int a = dsu_find(u), b = dsu_find(v);
            dsu_merge(a, b);
        }
    }
    int x = dsu_find(u);
    if (st[x].empty()) {
        st[x].insert(make_pair(a[u], u));
        root[x] = insert(root[x], new Node(make_pair(a[u], u)));
    } else {
        pair<long long, int> p = *st[x].rbegin();
        st[x].erase(p);
        root[x] = erase(root[x], p);
        st[x].insert(make_pair(p.first + a[u], p.second));
        root[x] = insert(root[x], new Node(make_pair(p.first + a[u], p.second)));
    }
    for (int i = 0; i < queries[u].size(); i++) {
        auto [k, j] = queries[u][i];
        k = min(k, (int)st[x].size());
        Node *l = nullptr;
        Node *r = nullptr;
        split_by_ind(root[x], k, l, r);
        ans[j] = (long double)l->sum / (long double)sz[u];
        root[x] = merge(l, r);
    }
    return;
}

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(12);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < q; i++) {
        int u, k;
        cin >> u >> k;
        u--;
        queries[u].push_back(make_pair(k, i));
    }

    for (int i = 0; i < n; i++) {
        parent[i] = i;
        root[i] = nullptr;
    }
    dfs(0, -1);
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
