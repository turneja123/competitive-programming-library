//https://codeforces.com/contest/2063/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int a[N];
int parent[N];
int depth[N];
vector<int> adj[N];
multiset<int> st[N];

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    int key;
    int priority;
    int cnt;
    int val;
    long long sum;
    int lazy;
    Node* left;
    Node* right;

    Node(int key) : key(key), priority(generator()), cnt(1), val(1), sum(2 * key - 1), lazy(0), left(nullptr), right(nullptr) {}
};

Node* root[N];
long long ans = 0;

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

long long get_sum(Node* node) {
    return node ? node->sum : 0;
}

void upd_cnt(Node* node) {
    if (node) {
        node->cnt = node->val + get_cnt(node->left) + get_cnt(node->right);
        node->sum = node->val * (2 * node->key - 1) + get_sum(node->left) + get_sum(node->right);
    }
}

void apply(Node* node) {
    if (node && node->lazy != 0) {
        node->key += node->lazy;
        node->sum += 2 * (node->lazy);
        if (node->left) {
            node->left->lazy += node->lazy;
        }
        if (node->right) {
            node->right->lazy += node->lazy;
        }
        node->lazy = 0;
    }
}

void split(Node* node, int key, Node*& left, Node*& right) {
    if (!node) {
        left = right = nullptr;
        return;
    }
    apply(node);
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
        apply(left);
        left->right = merge(left->right, right);
        upd_cnt(left);
        return left;
    } else {
        apply(right);
        right->left = merge(left, right->left);
        upd_cnt(right);
        return right;
    }
}

Node* insert(Node* root, Node* node) {
    if (!root) {
        return node;
    }
    apply(root);
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
    apply(root);
    if (key < root->key) {
        root->left = erase(root->left, key);
    } else if (key > root->key) {
        root->right = erase(root->right, key);
    } else {
        Node* temp = merge(root->left, root->right);
        //delete root;
        return temp;
    }
    upd_cnt(root);
    return root;
}

Node* find(Node* root, int key) {
    if (!root) {
        return root;
    }
    apply(root);
    if (root->key == key) {
        root->val += 1;
        upd_cnt(root);
        return root;
    }
    Node *ret;
    if (root->key > key) {
        ret = find(root->left, key);
    } else {
        ret = find(root->right, key);
    }
    upd_cnt(root);
    return ret;
}


int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b, int l) {
    if (st[a].size() > st[b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    for (auto it = st[a].begin(); it != st[a].end(); ++it) {
        int x = *it - depth[l];
        Node* lf = nullptr;
        Node* rt = nullptr;
        split(root[b], x, lf, rt);
        if (lf) {
            ans += lf->sum;
        }
        if (rt) {
            ans += (long long)rt->cnt * (2 * x - 1);
        }
        root[b] = merge(lf, rt);
    }
    for (auto it = st[a].begin(); it != st[a].end(); ++it) {
        st[b].insert(*it);
        int x = *it - depth[l];
        Node *y = find(root[b], x);
        if (!y) {
            root[b] = insert(root[b], new Node(x));
        }
    }
    return;
}

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
    for (int v : adj[u]) {
        if (v != p) {
            int a = dsu_find(u), b = dsu_find(v);
            root[b]->lazy += 1;
            dsu_merge(a, b, u);
        }
    }
    int a = dsu_find(u);
    st[a].insert(depth[u]);
    root[a] = insert(root[a], new Node(0));
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            root[i] = nullptr;
        }

        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        dfs(0, -1);
        cout << ans << endl;
        ans = 0;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            st[i].clear();
        }
    }

    return 0;
}
