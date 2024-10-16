//https://codeforces.com/problemset/problem/863/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    int val;
    int priority;
    int cnt;
    int lazy;
    Node* left;
    Node* right;

    Node(int val) : val(val), priority(generator()), cnt(1), lazy(0), left(nullptr), right(nullptr) {}
};

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

void upd_cnt(Node* node) {
    if (node) {
        node->cnt = 1 + get_cnt(node->left) + get_cnt(node->right);
    }
}

void apply(Node* node) {
    if (node && node->lazy != 0) {
        swap(node->left, node->right);
        if (node->left) {
            node->left->lazy ^= node->lazy;
        }
        if (node->right) {
            node->right->lazy ^= node->lazy;
        }
        node->lazy = 0;
    }
}

void split(Node* node, int k, Node*& left, Node*& right) {
    if (!node) {
        left = right = nullptr;
        return;
    }
    apply(node);
    if (get_cnt(node->left) >= k) {
        split(node->left, k, left, node->left);
        right = node;
    } else {
        split(node->right, k - get_cnt(node->left) - 1, node->right, right);
        left = node;
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

int get_kth(Node* node, int k) {
    apply(node);
    if (!node) {
        return -1;
    }
    int left_cnt = get_cnt(node->left);
    if (k < left_cnt) {
        return get_kth(node->left, k);
    } else if (k == left_cnt) {
        return node->val;
    } else {
        return get_kth(node->right, k - left_cnt - 1);
    }
}

class Treap {
public:
    Node* root;

    Treap() : root(nullptr) {}

    int size() {
        return get_cnt(root);
    }

    int get_element(int k) {
        return get_kth(root, k);
    }

    void insert(int x, int j) {
        Node* new_node = new Node(x);
        Node *left, *right;
        split(root, j, left, right);
        root = merge(merge(left, new_node), right);
    }

    void rev_update(int l, int r) {
        Node *a, *b, *c, *d;
        split(root, l, a, b);
        split(b, r - l + 1, c, d);
        if (c) {
            c->lazy ^= 1;
        }
        root = merge(merge(a, c), d);
    }

    void shift(int l, int r) {
        if (l == r) {
            return;
        }
        Node *a, *b, *c, *d, *e, *f;
        split(root, l, a, b);
        split(b, r - l, c, d);
        split(d, 1, e, f);
        root = merge(merge(a, e), merge(c, f));
    }

};

int main() {
    IOS;
    Treap tr;
    int n, q, m;
    cin >> n >> q >> m;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        tr.insert(a, tr.size());
    }
    for (int i = 0; i < q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        l--, r--;
        if (t == 1) {
            tr.shift(l, r);
        } else {
            tr.rev_update(l, r);
        }
    }
    for (int i = 0; i < m; i++) {
        int j;
        cin >> j;
        j--;
        cout << tr.get_element(j) << " ";
    }
    return 0;
}
