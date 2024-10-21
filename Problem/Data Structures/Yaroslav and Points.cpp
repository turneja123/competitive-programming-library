//https://codeforces.com/contest/295/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

int a[N];

struct Node {
    int key;
    long long sum;
    long long ans;
    int priority;
    int cnt;
    Node* left;
    Node* right;

    Node(int key) : key(key), sum(key), ans(0), priority(generator()), cnt(1), left(nullptr), right(nullptr) {}
};

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

long long get_sum(Node* node) {
    return node ? node->sum : 0;
}

long long get_ans(Node *node) {
    return node ? node->ans : 0;
}

void upd_cnt(Node* node) {
    if (node) {
        node->cnt = 1 + get_cnt(node->left) + get_cnt(node->right);
        node->sum = get_sum(node->left) + get_sum(node->right) + node->key;
        node->ans = (long long)node->key * get_cnt(node->left) - get_sum(node->left) + get_sum(node->right) - (long long)node->key * get_cnt(node->right) + get_ans(node->left) + get_ans(node->right) + get_sum(node->right) * get_cnt(node->left) - get_sum(node->left) * get_cnt(node->right);
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

int main(){
    IOS;
    Node* root = nullptr;
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        root = insert(root, new Node(a[i]));
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int j, d;
            cin >> j >> d;
            j--;
            root = erase(root, a[j]);
            a[j] += d;
            root = insert(root, new Node(a[j]));
        } else {
            int l, r;
            cin >> l >> r;
            Node *a, *b, *c, *d;
            split(root, l, a, b);
            split(b, r + 1, c, d);
            cout << ((c) ? c->ans : 0) << endl;
            root = merge(a, merge(c, d));
        }
    }

    return 0;
}
