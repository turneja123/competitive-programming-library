//https://dmoj.ca/problem/egoi22p5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

const int MAX = 101;
const int N = 2e5 + 5;

struct Node {
    int key;
    int lazy;
    int priority;
    int cnt;
    Node* left;
    Node* right;

    Node(int key) : key(key), lazy(0), priority(generator()), cnt(1), left(nullptr), right(nullptr) {}
};

int ans[N];
Node* root[MAX];

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

void split_by_ind(Node* node, int k, Node*& left, Node*& right) {
    apply(node);
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

Node* tr_union(Node *left, Node *right) {
    apply(left);
    apply(right);
    if (!left || !right) {
        return left ? left : right;
    }
    if (left->priority < right->priority) {
        swap(left, right);
    }
    Node *a, *b;
    split(right, left->key + 1, a, b);
    left->right = tr_union(left->right, b);
    left->left = tr_union(a, left->left);
    upd_cnt(left);
    upd_cnt(right);
    return left;
}

void dfs(Node* node) {
    if (!node) {
        return;
    }
    apply(node);
    if (node->left) {
        dfs(node->left);
    }
    cout << -node->key << " ";
    if (node->right) {
        dfs(node->right);
    }
}

int main(){
    IOS;
    Node *root = nullptr;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        root = insert(root, new Node(-a));
    }
    for (int i = 0; i < q; i++) {
        int x, j;
        cin >> x >> j;
        Node *a, *b;
        split_by_ind(root, j, a, b);
        if (a) {
            a->lazy += x;
        }
        root = tr_union(a, b);
    }
    dfs(root);

    return 0;
}
