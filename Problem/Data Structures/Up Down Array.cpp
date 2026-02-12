//https://tlx.toki.id/contests/troc-43/problems/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

mt19937 gene(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    pair<int, int> key;
    ll sum[2];
    int priority;
    int cnt;
    Node* left;
    Node* right;

    Node(pair<int, int> _key) {
        key = _key;
        sum[0] = key.first;
        sum[1] = 0;
        priority = gene();
        cnt = 1;
        left = nullptr;
        right = nullptr;
    }
};

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

ll get_sum(Node* node, int i) {
    return node ? node->sum[i] : 0;
}

void upd_cnt(Node* node) {
    if (node) {
        node->cnt = 1 + get_cnt(node->left) + get_cnt(node->right);

        if (get_cnt(node->left) % 2 == 0) {
            node->sum[0] = get_sum(node->left, 0) + node->key.first + get_sum(node->right, 1);
            node->sum[1] = get_sum(node->left, 1) + get_sum(node->right, 0);
        } else {
            node->sum[0] = get_sum(node->left, 0) + get_sum(node->right, 0);
            node->sum[1] = get_sum(node->left, 1) + node->key.first + get_sum(node->right, 1);
        }
    }
}

void split(Node* node, pair<int, int> key, Node*& left, Node*& right) {
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
    } else if (node->key < root->key) {
        root->left = insert(root->left, node);
    } else {
        root->right = insert(root->right, node);
    }
    upd_cnt(root);
    return root;
}

int kth(Node* root, int k) {
    if (!root) {
        return -1;
    }
    int x = k - get_cnt(root->left);
    if (x <= 0) {
        return kth(root->left, k);
    } else if (x == 1) {
        return root->key.first;
    } else {
        return kth(root->right, x - 1);
    }
}

int main() {
    IOS;
    Node* root = nullptr;
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        root = insert(root, new Node({a, i}));
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 2) {
            int x;
            cin >> x;
            root = insert(root, new Node({x, i + n}));
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            Node *a, *b, *c, *d;
            split_by_ind(root, l, a, b);
            split_by_ind(b, r - l + 1, c, d);

            if (r == l) {
                cout << c->sum[0] << endl;
            } else {
                int x = kth(c, 1);
                int z = kth(c, r - l + 1);
                if ((r - l + 1) % 2 == 0) {
                    ll ans = max(c->sum[1], c->sum[0] + z - x);
                    cout << ans << endl;
                } else {
                    ll ans = max(c->sum[0], c->sum[1] + z);
                    cout << ans << endl;
                }
            }
            root = merge(a, merge(c, d));
        }
    }

    return 0;
}
