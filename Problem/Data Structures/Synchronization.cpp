//https://dmoj.ca/problem/joi13op2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

vector<pair<int, int>> adj[N];
int open[N];
vector<pair<int, int>> ivals[N];
int sz[N];
bool seen_c[N];
int parent_c[N];
int parent[N];
int sz_dsu[N];
int ans[N];


mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    int key;
    int priority;
    int val;
    int cnt;
    Node* left;
    Node* right;

    Node(pair<int, int> key) : key(key.first), priority(generator()), val(key.second), cnt(key.second), left(nullptr), right(nullptr) {}
};

Node* root[N];

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

void upd_cnt(Node* node) {
    if (node) {
        node->cnt = node->val + get_cnt(node->left) + get_cnt(node->right);
    }
}

void split(Node* node, int key, Node*& left, Node*& right) {
    if (!node) {
        left = right = nullptr;
        return;
    }
    if (node->key < key) {
        split(node->right, key, node->right, right);
        left = node;
    } else {
        split(node->left, key, left, node->left);
        right = node;
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
    } else if (node->key < root->key) {
        root->left = insert(root->left, node);
    } else {
        root->right = insert(root->right, node);
    }
    upd_cnt(root);
    return root;
}

Node* erase(Node* root, int key) {
    if (!root)
        return root;
    if (key < root->key) {
        root->left = erase(root->left, key);
    } else if (key > root->key) {
        root->right = erase(root->right, key);
    } else {
        Node* temp = merge(root->left, root->right);
        delete root;
        return temp;
    }
    upd_cnt(root);
    return root;
}

int find(Node* root, int key) {
    if (!root) {
        return -1;
    }
    if (root->key == key) {
        return root->val;
    }
    if (root->key > key) {
        return find(root->left, key);
    } else {
        return find(root->right, key);
    }
}

void dfs_treap(Node* root, vector<pair<int, int>> &v) {
    if (!root) {
        return;
    }
    v.push_back(make_pair(root->key, root->val));
    dfs_treap(root->left, v);
    dfs_treap(root->right, v);
}

void dfs_clear(Node* root) {
    if (!root) {
        return;
    }
    dfs_clear(root->left);
    dfs_clear(root->right);
    delete root;
}

Node* add_treap(int x, int y, Node* root) {
    int z = find(root, x);
    if (z == -1) {
        root = insert(root, new Node(make_pair(x, y)));
    } else {
        root = erase(root, x);
        root = insert(root, new Node(make_pair(x, y + z)));
    }
    return root;
}

void dfs_subtree(int u, int p) {
    sz[u] = 1;
    for (auto [v, e] : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_subtree(v, u);
            sz[u] += sz[v];
        }
    }
    return;
}

int dfs_centroid(int u, int p, int n) {
    for (auto [v, e] : adj[u]) {
        if (v != p && !seen_c[v] && sz[v] > n / 2) {
            return dfs_centroid(v, u, n);
        }
    }
    return u;
}

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b) {
    if (sz_dsu[a] > sz_dsu[b]) {
        swap(a, b);
    }
    parent[a] = b;
    sz_dsu[b] += sz_dsu[a];
    vector<pair<int, int>> elems;
    dfs_treap(root[a], elems);
    for (auto [x, y] : elems) {
        root[b] = add_treap(x, y, root[b]);
    }
    //dfs_clear(root[a]);
    return;
}

void dfs(int u, int p) {
    parent[u] = u;
    sz_dsu[u] = 1;
    dfs_clear(root[u]);
    root[u] = nullptr;
    for (auto [v, e] : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs(v, u);
        }
    }
}

void dfs_add(int u, int p) {
    for (auto [v, e] : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_add(v, u);
        }
    }
    for (auto [v, e] : adj[u]) {
        if (v != p && !seen_c[v]) {
            int a = dsu_find(u), b = dsu_find(v);
            int last = -1;
            for (auto [l, r] : ivals[e]) {
                if (last < l - 1) {
                    Node* A = nullptr;
                    Node* B = nullptr;
                    Node* C = nullptr;
                    Node* D = nullptr;
                    split(root[b], last + 1, A, B);
                    split(B, l, C, D);
                    root[b] = merge(A, D);
                    if (C) {
                        root[b] = add_treap(l, C->cnt, root[b]);
                        dfs_clear(C);
                    }
                }
                last = r;
            }
            if (ivals[e].size() > 0) {
                int r = ivals[e].back().second;
                Node* A = nullptr;
                Node* B = nullptr;
                split(root[b], r + 1, A, B);
                root[b] = A;
                dfs_clear(B);
                dsu_merge(a, b);
            }
        }
    }
    int a = dsu_find(u);
    root[a] = add_treap(0, 1, root[a]);
    return;
}

void dfs_calc(int u, int p, int ed, int c) {
    if (ivals[ed].empty() || !root[c]) {
        return;
    }
    vector<tuple<Node*, int, int, int>> rollback;
    int last = -1;
    for (auto [l, r] : ivals[ed]) {
        if (last < l - 1) {
            Node* A = nullptr;
            Node* B = nullptr;
            Node* C = nullptr;
            Node* D = nullptr;
            split(root[c], last + 1, A, B);
            split(B, l, C, D);
            root[c] = merge(A, D);
            if (C) {
                rollback.push_back(make_tuple(C, 2, l, 0));
                //root[b] = add_treap(l, C->cnt, root[b]);
                int x = l, y = C->cnt;
                int z = find(root[c], x);
                if (z == -1) {
                    root[c] = insert(root[c], new Node(make_pair(x, y)));
                    rollback.push_back(make_tuple(nullptr, -1, x, y));
                } else {
                    root[c] = erase(root[c], x);
                    rollback.push_back(make_tuple(nullptr, 1, x, z));
                    root[c] = insert(root[c], new Node(make_pair(x, y + z)));
                    rollback.push_back(make_tuple(nullptr, -1, x, y + z));
                }
            }
        }
        last = r;
    }
    int r = ivals[ed].back().second;
    Node* A = nullptr;
    Node* B = nullptr;
    split(root[c], r + 1, A, B);
    root[c] = A;
    rollback.push_back(make_tuple(B, 2, r + 1, 0));
    ans[u] += get_cnt(root[c]);
    for (auto [v, e] : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_calc(v, u, e, c);
        }
    }
    for (int i = rollback.size() - 1; i >= 0; i--) {
        auto [node, f, x, y] = rollback[i];
        if (f == -1) {
            root[c] = erase(root[c], x);
        } else if (f == 1) {
            root[c] = insert(root[c], new Node(make_pair(x, y)));
        } else {
            Node* A = nullptr;
            Node* B = nullptr;
            split(root[c], x, A, B);
            root[c] = merge(A, merge(node, B));
        }
    }
}

void build(int u, int p) {
    dfs_subtree(u, u);
    int c = dfs_centroid(u, u, sz[u]);
    if (p == -1) {
        p = c;
    }
    parent_c[c] = p;
    seen_c[c] = true;

    root[c] = nullptr;
    sz_dsu[c] = 1;
    parent[c] = c;
    root[c] = add_treap(0, 1, root[c]);
    for (auto [v, e] : adj[c]) {
        if (!seen_c[v]) {
            dfs(v, v);
        }
    }
   for (int i = 0; i < adj[c].size(); i++) {
        auto [v, e] = adj[c][i];
        if (!seen_c[v]) {
            dfs_calc(v, v, e, dsu_find(c));
            dfs_add(v, v);
            int a = dsu_find(c), b = dsu_find(v);
            int last = -1;
            for (auto [l, r] : ivals[e]) {
                if (last < l - 1) {
                    Node* A = nullptr;
                    Node* B = nullptr;
                    Node* C = nullptr;
                    Node* D = nullptr;
                    split(root[b], last + 1, A, B);
                    split(B, l, C, D);
                    root[b] = merge(A, D);
                    if (C) {
                        root[b] = add_treap(l, C->cnt, root[b]);
                        dfs_clear(C);
                    }
                }
                last = r;
            }
            if (ivals[e].size() > 0) {
                int r = ivals[e].back().second;
                Node* A = nullptr;
                Node* B = nullptr;
                split(root[b], r + 1, A, B);
                root[b] = A;
                dfs_clear(B);
                dsu_merge(a, b);
            }
        }
    }
    vector<pair<int, int>> elems;
    dfs_treap(root[dsu_find(c)], elems);
    for (auto [x, y] : elems) {
        ans[c] += y;
    }

    root[c] = nullptr;
    sz_dsu[c] = 1;
    parent[c] = c;
    for (auto [v, e] : adj[c]) {
        if (!seen_c[v]) {
            dfs(v, v);
        }
    }
   for (int i = adj[c].size() - 1; i >= 0; i--) {
        auto [v, e] = adj[c][i];
        if (!seen_c[v]) {
            dfs_calc(v, v, e, dsu_find(c));
            dfs_add(v, v);
            int a = dsu_find(c), b = dsu_find(v);
            int last = -1;
            for (auto [l, r] : ivals[e]) {
                if (last < l - 1) {
                    Node* A = nullptr;
                    Node* B = nullptr;
                    Node* C = nullptr;
                    Node* D = nullptr;
                    split(root[b], last + 1, A, B);
                    split(B, l, C, D);
                    root[b] = merge(A, D);
                    if (C) {
                        root[b] = add_treap(l, C->cnt, root[b]);
                        dfs_clear(C);
                    }
                }
                last = r;
            }
            if (ivals[e].size() > 0) {
                int r = ivals[e].back().second;
                Node* A = nullptr;
                Node* B = nullptr;
                split(root[b], r + 1, A, B);
                root[b] = A;
                dfs_clear(B);
                dsu_merge(a, b);
            }
        }
    }
    for (auto [v, e] : adj[c]) {
        if (!seen_c[v]) {
            dfs(v, v);
        }
    }
    for (auto [v, e] : adj[c]) {
        if (!seen_c[v]) {
            build(v, c);
        }
    }
    return;
}


int main() {
    IOS;
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(make_pair(v, i));
        adj[v].push_back(make_pair(u, i));
        open[i] = -1;
    }
    for (int i = 0; i < m; i++) {
        int j;
        cin >> j;
        j--;
        if (open[j] == -1) {
            open[j] = i;
        } else {
            ivals[j].push_back(make_pair(open[j], i - 1));
            open[j] = -1;
        }
    }
    for (int i = 0; i < n - 1; i++) {
        if (open[i] != -1) {
            ivals[i].push_back(make_pair(open[i], m - 1));
        }
    }
    build(0, -1);
    for (int i = 0; i < q; i++) {
        int j;
        cin >> j;
        j--;
        cout << ans[j] << endl;
    }

    return 0;
}
