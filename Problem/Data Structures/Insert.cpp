//https://atcoder.jp/contests/abc392/tasks/abc392_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;
const int MAX = 1e5 + 5;

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    int val;
    int priority;
    int cnt;
    Node* left;
    Node* right;

    Node(int val) : val(val), priority(generator()), cnt(1), left(nullptr), right(nullptr) {}
};

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

void upd_cnt(Node* node) {
    if (node) {
        node->cnt = 1 + get_cnt(node->left) + get_cnt(node->right);
    }
}

void split(Node* node, int k, Node*& left, Node*& right) {
    if (!node) {
        left = right = nullptr;
        return;
    }
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
        left->right = merge(left->right, right);
        upd_cnt(left);
        return left;
    } else {
        right->left = merge(left, right->left);
        upd_cnt(right);
        return right;
    }
}

int get_kth(Node* node, int k) {
    if (!node) {
        return -1;
    }
    int left_cnt = get_cnt(node->left);
    if (k < left_cnt) {
        return get_kth(node->left, k);
    } else if (k == left_cnt) {
        return node->val;
    } else {
        return get_kth(node->right, k - left_cnt - 1);
    }
}

void print_treap(Node *node) {
    if (!node) {
        return;
    }
    print_treap(node->left);
    cout << node->val << " ";
    print_treap(node->right);
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

    void in_order() {
        print_treap(root);
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
};

int main() {
    IOS;
    Treap tr;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int pos;
        cin >> pos;
        tr.insert(i, pos - 1);
    }
    tr.in_order();
    return 0;
}
