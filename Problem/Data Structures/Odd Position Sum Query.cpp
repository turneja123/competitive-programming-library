//https://atcoder.jp/contests/abc403/tasks/abc403_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9;

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    pair<int, int> key;
    int priority;
    int cnt;
    int val;
    long long sum;
    Node* left;
    Node* right;

    Node(pair<int, int> key) : key(key), priority(generator()), cnt(1), val(key.first), sum(key.first), left(nullptr), right(nullptr) {}
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
        node->sum = node->val + get_sum(node->left) + get_sum(node->right);
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
    Node* all = nullptr;
    Node* even = nullptr;
    Node* odd = nullptr;
    int q;
    cin >> q;
    long long last = 0;
    for (int i = 0; i < q; i++) {
        long long x;
        cin >> x;
        x = (x + last) % M + 1;
        Node* a, *b;
        split(all, make_pair(x, i), a, b);
        int ct = get_cnt(a);
        all = merge(a, b);
        Node *A, *B, *C, *D;
        split(even, make_pair(x, i), A, B);
        split(odd, make_pair(x, i), C, D);
        even = merge(A, D);
        odd = merge(C, B);
        if (ct % 2 == 0) {
            odd = insert(odd, new Node(make_pair(x, i)));
        } else {
            even = insert(even, new Node(make_pair(x, i)));
        }
        all = insert(all, new Node(make_pair(x, i)));
        last = get_sum(odd);
        cout << last << endl;
    }
    return 0;
}
