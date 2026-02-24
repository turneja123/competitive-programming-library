//https://atcoder.jp/contests/arc196/tasks/arc196_a
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const ll INF = 1e18;

mt19937 gene(chrono::steady_clock::now().time_since_epoch().count());

ll pref[N];
ll suf[N];

struct Node {
    pair<int, int> key;
    ll sum;
    int priority;
    int cnt;
    Node* left;
    Node* right;

    Node(pair<int, int> key) : key(key), sum(key.first), priority(gene()), cnt(1), left(nullptr), right(nullptr) {}
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

int main() {
    IOS;
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    if (n % 2 == 0) {
        sort(a.begin(), a.end());
        ll ans = 0;
        for (int i = 0; i < n / 2; i++) {
            ans -= a[i];
        }
        for (int i = n / 2; i < n; i++) {
            ans += a[i];
        }
        cout << ans;
        return 0;
    }
    Node *root = nullptr;
    for (int i = n - 1; i >= 0; i--) {
        root = insert(root, new Node({a[i], i}));
        if ((n - i) % 2 == 1) {
            suf[i] = -INF;
        } else {
            int m = (n - i) / 2;
            Node *l, *r;
            split_by_ind(root, m, l, r);
            suf[i] = r->sum - l->sum;;
            root = merge(l, r);
        }
    }
    root = nullptr;
    for (int i = 0; i < n; i++) {
        root = insert(root, new Node({a[i], i}));
        if ((i + 1) % 2 == 1) {
            pref[i] = -INF;
        } else {
            int m = (i + 1) / 2;
            Node *l, *r;
            split_by_ind(root, m, l, r);
            pref[i] = r->sum - l->sum;;
            root = merge(l, r);
        }
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, (i == 0 ? 0 : pref[i - 1]) + (i == n - 1 ? 0 : suf[i + 1]));
    }
    cout << ans;



    return 0;
}
