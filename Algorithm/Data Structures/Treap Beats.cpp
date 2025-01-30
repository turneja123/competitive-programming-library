//https://codeforces.com/gym/102787/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long INF = 1e18;

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    long long val;
    long long lazy;
    long long sum;
    long long mx1;
    long long mx2;
    bool push;
    int mxc;
    int priority;
    int cnt;
    Node* left;
    Node* right;

    Node(long long val) : val(val), lazy(0), sum(val), mx1(val), mx2(-INF), push(false), mxc(1), priority(generator()), cnt(1), left(nullptr), right(nullptr) {}
};

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

long long get_sum(Node* node) {
    return node ? node->sum : 0;
}

tuple<long long, long long, int> combine(Node* left, Node* right) {
    long long mx1, mx2; int mxc;
    if (left->mx1 == right->mx1) {
        mx1 = left->mx1;
        mx2 = max(left->mx2, right->mx2);
        mxc = left->mxc + right->mxc;
    } else if (left->mx1 > right->mx1) {
        mx1 = left->mx1;
        mx2 = max(left->mx2, right->mx1);
        mxc = left->mxc;
    } else {
        mx1 = right->mx1;
        mx2 = max(left->mx1, right->mx2);
        mxc = right->mxc;
    }
    return make_tuple(mx1, mx2, mxc);
}

void apply_add(Node* node, long long val) {
    if (!node || val == 0) {
        return;
    }
    node->sum += val * get_cnt(node);
    node->mx1 += val;
    node->val += val;
    if (node->mx2 != -INF) {
        node->mx2 += val;
    }
    node->lazy += val;
    return;
}

void apply_max(Node* node, long long val) {
    if (!node || node->mx1 <= val) {
        return;
    }
    assert(node->mx2 < val);
    node->sum -= (node->mx1 - val) * node->mxc;
    if (node->val == node->mx1) {
        node->val = val;
    }
    node->mx1 = val;
    node->push = true;
}

void upd_cnt(Node* node) {
    if (node) {
        node->cnt = 1 + get_cnt(node->left) + get_cnt(node->right);
        node->sum = node->val + get_sum(node->left) + get_sum(node->right);
        node->mx1 = node->val;
        node->mx2 = -INF;
        node->mxc = 1;
        if (node->left) {
            auto [mx1, mx2, mxc] = combine(node, node->left);
            node->mx1 = mx1;
            node->mx2 = mx2;
            node->mxc = mxc;
        }
        if (node->right) {
            auto [mx1, mx2, mxc] = combine(node, node->right);
            node->mx1 = mx1;
            node->mx2 = mx2;
            node->mxc = mxc;
        }
    }
}

void compose(Node* node) {
    if (!node) {
        return;
    }
    if (node->left && node->lazy != 0) {
        apply_add(node->left, node->lazy);
    }
    if (node->left && node->push) {
        apply_max(node->left, node->mx1);
    }
    if (node->right && node->lazy != 0) {
        apply_add(node->right, node->lazy);
    }
    if (node->right && node->push) {
        apply_max(node->right, node->mx1);
    }
    node->lazy = 0;
    node->push = false;
    upd_cnt(node);
}

void split(Node* node, int k, Node*& left, Node*& right) {
    if (!node) {
        left = right = nullptr;
        return;
    }
    compose(node);
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
    compose(left);
    compose(right);
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

void update_min(Node* node, long long val) {
    if (!node || node->mx1 <= val) {
        return;
    }
    if (node->mx2 < val) {
        apply_max(node, val);
        return;
    }
    compose(node);
    update_min(node->left, val);
    update_min(node->right, val);
    node->val = min(node->val, val);
    upd_cnt(node);
    return;
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

Node* build(vector<int> &a, int l, int n) {
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

    long long ans() {
        return get_sum(root);
    }

    void create(vector<int> &a, int n) {
        root = build(a, 0, n);
    }

    void insert(int x, int j) {
        Node* new_node = new Node(x);
        Node *left, *right;
        split(root, j, left, right);
        root = merge(merge(left, new_node), right);
    }

    void chmin(int l, int r, long long x) {
        Node *a, *b, *c, *d;
        split(root, l, a, b);
        split(b, r - l + 1, c, d);
        update_min(c, x);
        root = merge(merge(a, c), d);
    }

    void add(int l, int r, long long x) {
        Node *a, *b, *c, *d;
        split(root, l, a, b);
        split(b, r - l + 1, c, d);
        apply_add(c, x);
        root = merge(merge(a, c), d);
    }

    void move(int l, int r) {
        Node *a, *b, *c, *d;
        split(root, l, a, b);
        split(b, r - l + 1, c, d);
        root = merge(merge(a, d), c);
    }
};

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    Treap tr;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    tr.create(a, n);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r; long long x;
            cin >> l >> r >> x;
            l--, r--;
            tr.chmin(l, r, x);
        } else if (t == 2) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            tr.move(l, r);
        } else {
            int l, r; long long x;
            cin >> l >> r >> x;
            l--, r--;
            tr.add(l, r, x);
        }
        cout << tr.ans() << endl;
    }
    return 0;
}
