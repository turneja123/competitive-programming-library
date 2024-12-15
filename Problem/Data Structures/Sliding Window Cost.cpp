//https://cses.fi/problemset/task/1077
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    pair<int, int> key;
    int priority;
    int cnt;
    int mx;
    long long sum;
    Node* left;
    Node* right;

    Node(pair<int, int> key) : key(key), priority(generator()), cnt(1), mx(key.first), sum(key.first), left(nullptr), right(nullptr) {}
};

int a[N];

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

int get_mx(Node* node) {
    return node ? node->mx : 0;
}

long long get_sum(Node* node) {
    return node ? node->sum : 0;
}

void upd_cnt(Node* node) {
    if (node) {
        node->cnt = 1 + get_cnt(node->left) + get_cnt(node->right);
        node->sum = node->key.first + get_sum(node->left) + get_sum(node->right);
        node->mx = max({node->key.first, get_mx(node->left), get_mx(node->right)});
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

Node* erase(Node* root, pair<int, int> key) {
    if (!root)
        return root;
    if (key < root->key) {
        root->left = erase(root->left, key);
    } else if (key > root->key) {
        root->right = erase(root->right, key);
    } else {
        Node* temp = merge(root->left, root->right);
        delete root;
        return temp;
    }
    upd_cnt(root);
    return root;
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


int main() {
    IOS;
    Node* root = nullptr;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        cin >> a[i];
        root = insert(root, new Node(make_pair(a[i], i)));
    }
    long long ans = 1e18;
    for (int mid = (k - 1) / 2; mid <= (k - 1) / 2 + 2; mid++) {
        if (mid == 0 || mid > n) {
            continue;
        }
        Node *left, *right;
        split_by_ind(root, mid, left, right);
        ans = min(ans, (long long)get_cnt(left) * get_mx(left) - get_sum(left) + get_sum(right) - (long long)get_cnt(right) * get_mx(left));
        root = merge(left, right);
    }
    cout << ans << " ";

    for (int i = k; i < n; i++) {
        cin >> a[i];
        root = erase(root, make_pair(a[i - k], i - k));
        root = insert(root, new Node(make_pair(a[i], i)));
        long long ans = 1e18;
        for (int mid = (k - 1) / 2; mid <= (k - 1) / 2 + 2; mid++) {
            if (mid == 0 || mid > n) {
                continue;
            }
            Node *left, *right;
            split_by_ind(root, mid, left, right);
            ans = min(ans, (long long)get_cnt(left) * get_mx(left) - get_sum(left) + get_sum(right) - (long long)get_cnt(right) * get_mx(left));
            root = merge(left, right);
        }
        cout << ans << " ";
    }

    return 0;
}
