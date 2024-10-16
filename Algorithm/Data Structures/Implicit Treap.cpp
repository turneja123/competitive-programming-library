//https://www.spoj.com/problems/ADALIST/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

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
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        tr.insert(a, tr.size());
    }
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int k, x;
            cin >> k >> x;
            k--;
            tr.insert(x, k);
        } else if (t == 2) {
            int k;
            cin >> k;
            k--;
            tr.erase(k);
        } else {
            int k;
            cin >> k;
            k--;
            cout << tr.get_element(k) << endl;
        }
    }
    return 0;
}
