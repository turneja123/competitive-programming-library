//https://codeforces.com/contest/911/problem/G
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
    int priority;
    int cnt;
    Node* left;
    Node* right;

    Node(int key) : key(key), priority(generator()), cnt(1), left(nullptr), right(nullptr) {}
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
        //delete root;
        return temp;
    }
    upd_cnt(root);
    return root;
}

Node* tr_union(Node *left, Node *right) {
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

void dfs(Node* node, int n) {
    if (!node) {
        return;
    }
    if (node->left) {
        dfs(node->left, n);
    }
    ans[node->key] = n;
    if (node->right) {
        dfs(node->right, n);
    }
}

int main(){
    IOS;
    for (int i = 0; i < MAX; i++) {
        root[i] = nullptr;
    }
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        root[a] = insert(root[a], new Node(i));
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        l--, r--;
        if (x == y) {
            continue;
        }
        Node *ax, *bx, *cx, *dx;
        split(root[x], l, ax, bx);
        split(bx, r + 1, cx, dx);
        Node *ay, *by, *cy, *dy;
        split(root[y], l, ay, by);
        split(by, r + 1, cy, dy);
        cy = tr_union(cx, cy);
        root[x] = merge(ax, dx);
        root[y] = merge(ay, merge(cy, dy));
    }
    for (int i = 0; i < MAX; i++) {
        dfs(root[i], i);
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
