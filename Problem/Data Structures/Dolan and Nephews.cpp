//https://www.spoj.com/problems/CARDFLIP/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    int val;
    Node* parent;
    int dir;
    int priority;
    int cnt;
    int lazy;
    Node* left;
    Node* right;

    Node(int val) : val(val), parent(nullptr), priority(generator()), cnt(1), lazy(0), left(nullptr), right(nullptr) {}
};

int a[N];
Node* ptr[N];

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
        if (left) {
            left->parent = nullptr;
        }
        if (node->left) {
            node->left->parent = node;
        }
        right = node;
    } else {
        split(node->right, k - get_cnt(node->left) - 1, node->right, right);
        if (right) {
            right->parent = nullptr;
        }
        if (node->right) {
            node->right->parent = node;
        }
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
        left->right->parent = left;
        upd_cnt(left);
        return left;
    } else {
        apply(right);
        right->left = merge(left, right->left);
        right->left->parent = right;
        upd_cnt(right);
        return right;
    }
}

int get_kth(Node* node, int k) {
    apply(node);
    if (!node) {
        return -1;
    }
    apply(node->left);
    apply(node->right);
    int left_cnt = get_cnt(node->left);
    if (k < left_cnt) {
        return get_kth(node->left, k);
    } else if (k == left_cnt) {
        return node->val;
    } else {
        return get_kth(node->right, k - left_cnt - 1);
    }
}

int dfs(vector<Node*> &v, int i, int k) {
    Node* node = v[i];
    apply(node);
    if (i == v.size() - 1) {
        return k + get_cnt(node->left);
    }
    if (v[i + 1] == node->left) {
        return dfs(v, i + 1, k);
    }
    return dfs(v, i + 1, k + 1 + get_cnt(node->left));
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

Node* build(int a[], int l, int n) {
    if (n == 0) {
        return nullptr;
    }
    int mid = n / 2;
    Node *node = new Node(a[l + mid]);
    ptr[a[l + mid]] = node;
    node->left = build(a, l, mid);
    node->right = build(a, l + mid + 1, n - mid - 1);
    if (node->left) {
        node->left->parent = node;
    }
    if (node->right) {
        node->right->parent = node;
    }
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

    int get_element(int k) {
        return get_kth(root, k);
    }

    void create(int a[], int n) {
        root = build(a, 0, n);
    }

    int get_pos(int x) {
        Node* node = ptr[x];
        vector<Node*> v{node};
        while (node != root) {
            node = node->parent;
            v.push_back(node);
            if (node == root) {
                break;
            }
        }
        reverse(v.begin(), v.end());
        return dfs(v, 0, 0);
    }

    void insert(int x, int j) {
        Node* new_node = new Node(x);
        ptr[x] = new_node;
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
};

int main() {
    IOS;
    Treap tr;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
    tr.create(a, n);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            tr.rev_update(l, r);
        } else if (t == 2) {
            int k;
            cin >> k;
            k--;
            cout << tr.get_element(k) + 1 << endl;
        } else {
            int k;
            cin >> k;
            k--;
            cout << tr.get_pos(k) + 1 << endl;
        }
    }
    return 0;
}
