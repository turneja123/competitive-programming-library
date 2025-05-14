//https://cses.fi/problemset/task/3411/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    pair<int, int> key;
    int priority;
    int cnt;
    long long sum;
    Node* left;
    Node* right;

    Node(pair<int, int> key) : key(key), priority(generator()), cnt(1), sum(key.first), left(nullptr), right(nullptr) {}
};

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

long long get_sum(Node* node) {
    return node ? node->sum : 0;
}

void upd_cnt(Node* node) {
    if (node) {
        node->cnt = 1 + get_cnt(node->left) + get_cnt(node->right);
        node->sum = node->key.first + get_sum(node->left) + get_sum(node->right);
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

int main() {
    IOS;
    Node* tr_x = nullptr;
    Node* tr_y = nullptr;
    int n;
    cin >> n;
    __int128 ans = 0;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        Node *a = nullptr, *b, *c, *d;
        split(tr_x, make_pair(x, i), a, b);
        ans += (long long)get_cnt(a) * x - get_sum(a) + get_sum(b) - (long long)get_cnt(b) * x;
        split(tr_y, make_pair(y, i), c, d);
        ans += (long long)get_cnt(c) * y - get_sum(c) + get_sum(d) - (long long)get_cnt(d) * y;
        tr_x = merge(a, b);
        tr_y = merge(c, d);
        tr_x = insert(tr_x, new Node(make_pair(x, i)));
        tr_y = insert(tr_y, new Node(make_pair(y, i)));
    }
    vector<int> p;
    while (ans > 0) {
        p.push_back(ans % 10);
        ans /= 10;
    }
    while (p.size()) {
        cout << p.back();
        p.pop_back();
    }
    return 0;
}
