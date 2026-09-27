//https://codeforces.com/contest/1000/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int a[N];
int pos[N];
int ans[N];
vector<pair<int, int>> queries[N];

mt19937 gene(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    int key;
    int priority;
    int val;
    int mx;
    Node* left;
    Node* right;

    Node(pair<int, int> key) : key(key.first), priority(gene()), val(key.second), mx(key.second), left(nullptr), right(nullptr) {}
};

int get_mx(Node* node) {
    return node ? node->mx : -1;
}

void upd_mx(Node* node) {
    if (node) {
        node->mx = max(node->val, max(get_mx(node->left), get_mx(node->right)));
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
    upd_mx(node);
}

Node* merge(Node* left, Node* right) {
    if (!left || !right) {
        return left ? left : right;
    }
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        upd_mx(left);
        return left;
    } else {
        right->left = merge(left, right->left);
        upd_mx(right);
        return right;
    }
}

Node* insert(Node* root, Node* node) {
    if (!root) {
        return node;
    }
    if (node->priority > root->priority) {
        split(root, node->key, node->left, node->right);
        upd_mx(node);
        return node;
    } else if (node->key < root->key) {
        root->left = insert(root->left, node);
    } else {
        root->right = insert(root->right, node);
    }
    upd_mx(root);
    return root;
}

Node* erase(Node* root, int key) {
    if (!root) {
        return root;
    }
    if (key < root->key) {
        root->left = erase(root->left, key);
    } else if (key > root->key) {
        root->right = erase(root->right, key);
    } else {
        Node* temp = merge(root->left, root->right);
        delete root;
        return temp;
    }
    upd_mx(root);
    return root;
}

int query(Node* node, int k) {
    if (!node || node->mx < k) {
        return 0;
    }
    if (node->key > k) {
        return query(node->left, k);
    }
    if (node->val >= k) {
        return a[node->key];
    }
    if (get_mx(node->left) >= k) {
        return query(node->left, k);
    }
    return query(node->right, k);
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]] = n;
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        queries[l].push_back(make_pair(r, i));
    }
    Node* root = nullptr;
    for (int i = n - 1; i >= 0; i--) {
        int x = a[i];
        if (pos[x] != n) {
            root = erase(root, pos[x]);
        }
        root = insert(root, new Node(make_pair(i, pos[x] - 1)));
        pos[x] = i;
        for (auto [r, j] : queries[i]) {
            ans[j] = query(root, r);
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
