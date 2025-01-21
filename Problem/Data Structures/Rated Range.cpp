//https://atcoder.jp/contests/abc389/tasks/abc389_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());
int ct[N];
int ans[N];

struct Node {
    int key;
    int priority;
    int cnt;
    int val;
    int lazy;
    Node* left;
    Node* right;

    Node(int key, int val) : key(key), priority(generator()), cnt(1), val(val), lazy(0), left(nullptr), right(nullptr) {}
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
        node->key += node->lazy;
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
        return root;
    }
    if (root->key > key) {
        return find(root->left, key);
    } else {
        return find(root->right, key);
    }
}

void inorder(Node* node) {
    if (!node) {
        return;
    }
    apply(node);
    ct[node->key] = node->val;
    inorder(node->left);
    inorder(node->right);
}

int main() {
    IOS;
    Node* root = nullptr;
    for (int i = 1; i < N; i++) {
        root = insert(root, new Node(i, 1));
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        Node* node = find(root, r);
        if (node != nullptr) {
            int x = node->val;
            root = erase(root, r);
            Node* after = find(root, r + 1);
            if (after != nullptr) {
                after->val += x;
            } else {
                root = insert(root, new Node(r + 1, x));
            }
        }
        if (l == r) {
            continue;
        }
        Node* a = nullptr;
        Node* b = nullptr;
        Node* c = nullptr;
        Node* d = nullptr;
        split(root, l, a, b);
        split(b, r, c, d);
        if (c != nullptr) {
            c->lazy += 1;
        }
        root = merge(a, merge(c, d));
    }
    inorder(root);
    int j = 1;
    for (int i = 1; i < N; i++) {
        for (int k = 0; k < ct[i]; k++) {
            ans[j++] = i;
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        cout << ans[x] << endl;
    }
    return 0;
}
