//https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const long long M = 998244353;

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

long long a[N];

struct Node {
    long long val;
    long long sum;
    long long b;
    long long c;
    bool setValid;
    int priority;
    int cnt;
    int lazy;
    Node* left;
    Node* right;

    Node(int val) : val(val), sum(val), b(1), c(0), setValid(false), priority(generator()), cnt(1), lazy(0), left(nullptr), right(nullptr) {}
};

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

long long get_sum(Node* node) {
    return node ? node->sum : 0;
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
    if (node && node->setValid) {
        node->sum = (node->sum * node->b + node->c * get_cnt(node)) % M;
        node->val = (node->val * node->b + node->c) % M;
        if (node->left) {
            node->left->b = node->left->b * node->b % M;
            node->left->c = (node->left->c * node->b % M + node->c) % M;
            node->left->setValid = true;
        }
        if (node->right) {
            node->right->b = node->right->b * node->b % M;
            node->right->c = (node->right->c * node->b % M + node->c) % M;
            node->right->setValid = true;
        }
        node->b = 1;
        node->c = 0;
        node->setValid = false;
    }
}

void upd_cnt(Node* node) {
    if (node) {
        apply(node->left);
        apply(node->right);
        node->cnt = 1 + get_cnt(node->left) + get_cnt(node->right);
        node->sum = (node->val + get_sum(node->left) + get_sum(node->right)) % M;
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

void heapify(Node* node) {
    if (!node) {
        return;
    }
    Node* mx = node;
    if (node->left && node->left->priority > mx->priority) {
        mx = node->left;
    }
    if (node->right && node->right->priority > mx->priority) {
        mx = node->right;
    }
    if (mx != node) {
        swap(node->priority, mx->priority);
        heapify(mx);
    }
    return;
}

Node* build(long long a[], int l, int n) {
    if (n == 0) {
        return nullptr;
    }
    int mid = n / 2;
    Node *node = new Node(a[l + mid]);
    node->left = build(a, l, mid);
    node->right = build(a, l + mid + 1, n - mid - 1);
    heapify(node);
    upd_cnt(node);
    return node;
}

class Treap {
public:
    Node* root;

    Treap() : root(nullptr) {}

    int size() {
        return get_cnt(root);
    }

    void insert(int x, int j) {
        Node* new_node = new Node(x);
        Node *left, *right;
        split(root, j, left, right);
        root = merge(merge(left, new_node), right);
    }

    void erase(int j) {
        int n = size();
        if (j < 0 || j >= n) {
            return;
        }
        Node *left, *mid, *right;
        split(root, j, left, right);
        split(right, 1, mid, right);
        root = merge(left, right);
    }

    void create(long long a[], int n) {
        root = build(a, 0, n);
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

    void affine_update(int l, int r, long long i_b, long long i_c) {
        Node *a, *b, *c, *d;
        split(root, l, a, b);
        split(b, r - l + 1, c, d);
        if (c) {
            c->b = c->b * i_b % M;
            c->c = (c->c * i_b % M + i_c) % M;
            c->setValid = true;
        }
        root = merge(merge(a, c), d);
    }

    long long query(int l, int r) {
        Node *a, *b, *c, *d;
        split(root, l, a, b);
        split(b, r - l + 1, c, d);
        long long ans = ((c) ? c->sum : 0);
        root = merge(merge(a, c), d);
        return ans;
    }
};

int main() {
    IOS;
    Treap tr;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    tr.create(a, n);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int j, x;
            cin >> j >> x;
            tr.insert(x, j);
        } else if (t == 1) {
            int j;
            cin >> j;
            tr.erase(j);
        } else if (t == 2) {
            int l, r;
            cin >> l >> r;
            r--;
            tr.rev_update(l, r);
        } else if (t == 3) {
            int l, r; long long b, c;
            cin >> l >> r >> b >> c;
            r--;
            tr.affine_update(l, r, b, c);
        } else {
            int l, r;
            cin >> l >> r;
            r--;
            cout << tr.query(l, r) << endl;
        }

    }
    return 0;
}
