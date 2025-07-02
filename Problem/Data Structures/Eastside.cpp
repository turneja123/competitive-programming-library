//https://ocpc2025s.eolymp.space/en/compete/995jqjr9ep1vr04atvo1l2ifr0/problem/2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int a[N];

mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    pair<long long, int> key;
    int mx;
    int priority;
    int cnt;
    Node* left;
    Node* right;

    Node(pair<long long, int> key) : key(key), mx(key.second), priority(gen()), cnt(1), left(nullptr), right(nullptr) {}
};

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

int get_mx(Node* node) {
    return node ? node->mx : -1;
}

void upd_cnt(Node* node) {
    if (node) {
        node->cnt = 1 + get_cnt(node->left) + get_cnt(node->right);
        node->mx = max({node->key.second, get_mx(node->left), get_mx(node->right)});
    }
}

void split(Node* node, pair<long long, int> key, Node*& left, Node*& right) {
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
    Node* root = nullptr;
    int n;
    cin >> n;
    long long pref = 0, inc = 0, mn = 0; int ans = -1;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pref += a[i];
        root = insert(root, new Node({pref, i}));
    }
    pref = 0;
    for (int i = 0; i < n; i++) {
        inc += -a[i];
        pref += a[i];
        long long best = pref - mn;
        if (best > 0) {
            Node* x = nullptr;
            Node* y = nullptr;
            pair<long long, int> v = {best - inc, N};
            split(root, v, x, y);
            Node* p = nullptr;
            Node* q = nullptr;
            v = {-inc, N};
            split(x, v, p, q);
            ans = max(ans, get_mx(q) - i);
            root = merge(merge(p, q), y);
        }
        mn = min(mn, pref);
    }
    if (ans == 0) {
        ans = -1;
    }
    cout << ans;


    return 0;
}
