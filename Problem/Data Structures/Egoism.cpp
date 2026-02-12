//https://atcoder.jp/contests/abc440/tasks/abc440_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

pair<int, int> a[N];

mt19937 gene(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    pair<int, int> key;
    ll sum;
    int priority;
    int cnt;
    Node* left;
    Node* right;

    Node(pair<int, int> key) : key(key), sum(-key.first), priority(gene()), cnt(1), left(nullptr), right(nullptr) {}
};

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

ll get_sum(Node* node) {
    return node ? node->sum : 0;
}

void upd_cnt(Node* node) {
    if (node) {
        node->cnt = 1 + get_cnt(node->left) + get_cnt(node->right);
        node->sum = -node->key.first + get_sum(node->left) + get_sum(node->right);
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

Node* erase(Node* root, pair<int, int> key) {
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

multiset<int> st[2];

int main() {
    IOS;
    Node* root = nullptr;
    int n, q;
    cin >> n >> q;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        a[i].second--;
        ans += a[i].first;
        root = insert(root, new Node({-a[i].first, i}));
        st[a[i].second].insert(a[i].first);
    }
    for (int i = 0; i < q; i++) {
        int j, x, y;
        cin >> j >> x >> y;
        j--, y--;
        st[a[j].second].erase(st[a[j].second].find(a[j].first));
        ans -= a[j].first;
        root = erase(root, make_pair(-a[j].first, j));

        a[j] = {x, y};
        ans += a[j].first;
        root = insert(root, new Node({-a[j].first, j}));
        st[a[j].second].insert(a[j].first);
        if (st[1].empty()) {
            cout << ans << endl;
            continue;
        }
        if (st[0].empty()) {
            cout << ans + root->sum - *st[1].begin() << endl;
            continue;
        }
        int m = st[1].size();
        Node *l, *r;
        split_by_ind(root, m, l, r);
        if (*st[1].begin() >= *st[0].rbegin()) {
            cout << ans + l->sum - *st[1].begin() + *st[0].rbegin() << endl;
        } else {
            cout << ans + l->sum << endl;
        }
        root = merge(l, r);
    }

    return 0;
}
