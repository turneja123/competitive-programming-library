//https://codeforces.com/contest/809/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    int key;
    int lazy;
    int inc;
    int ans;
    int mx;
    int priority;
    int cnt;
    Node* left;
    Node* right;

    Node(int key, int ans) : key(key), lazy(0), inc(0), ans(ans), mx(ans), priority(generator()), cnt(1), left(nullptr), right(nullptr) {}
    Node(int key) : key(key), lazy(0), inc(0), ans(0), mx(0), priority(generator()), cnt(1), left(nullptr), right(nullptr) {}
};

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

int get_mx(Node* node) {
    return node ? node->mx : 0;
}

void apply(Node* node) {
    if (node && (node->lazy != 0 || node->inc != 0)) {
        node->key += node->lazy;
        node->ans += node->inc;
        node->mx += node->inc;
        if (node->left) {
            node->left->lazy += node->lazy;
            node->left->inc += node->inc;
        }
        if (node->right) {
            node->right->lazy += node->lazy;
            node->right->inc += node->inc;
        }
        node->lazy = 0;
        node->inc = 0;
    }
}

void upd_cnt(Node* node) {
    if (node) {
        apply(node->left);
        apply(node->right);
        node->cnt = 1 + get_cnt(node->left) + get_cnt(node->right);
        node->mx = max({node->ans, get_mx(node->left), get_mx(node->right)});
    }
}

void split(Node* node, int key, Node*& left, Node*& right) {
    apply(node);
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
    apply(root);
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
    apply(root);
    if (!root)
        return root;
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

int dfs(Node* node) {
    if (!node) {
        return 0;
    }
    apply(node);
    int mx = node->ans;
    if (node->left) {
        mx = max(mx, dfs(node->left));
    }
    if (node->right) {
        mx = max(mx, dfs(node->right));
    }
    return mx;
}

int main() {
    IOS;
    Node* root = nullptr;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        Node *a, *b, *c, *d;
        split(root, l, a, b);
        int nw = (a ? a->mx + 1 : 1);
        if (l != r) {
            split(b, r, c, d);
            if (c) {
                c->lazy++;
                c->inc++;
            }
            Node *e, *f;
            split(d, r + 1, e, f);
            Node *ff, *ee;
            split(c, r + 1, ff, ee);
            Node *rr;
            if (!ee) {
                rr = e;
            } else if (!e) {
                rr = ee;
            } else if (e->ans > ee->ans) {
                rr = e;
            } else {
                rr = ee;
            }
            root = merge(merge(a, merge(c, rr)), f);
        } else {
            root = merge(a, b);
        }
        Node *node = new Node(l, nw);
        Node *aa, *bb, *cc, *dd;
        split(root, l, aa, bb);
        split(bb, l + 1, cc, dd);
        if (cc && cc->ans > node->ans) {
            node = cc;
        }
        root = merge(a, merge(node, dd));
    }
    cout << dfs(root);
    return 0;
}
