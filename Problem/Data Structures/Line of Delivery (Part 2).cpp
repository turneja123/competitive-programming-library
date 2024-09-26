//https://www.facebook.com/codingcompetitions/hacker-cup/2024/practice-round/problems/D2
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    int key;
    int priority;
    int cnt;
    int lazy;
    Node* left;
    Node* right;

    Node(int key) : key(key), priority(generator()), cnt(1), lazy(0), left(nullptr), right(nullptr) {}
};

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

void upd_cnt(Node* node) {
    if (node) {
        node->cnt = 1 + get_cnt(node->left) + get_cnt(node->right);
    }
}

void apply(Node* node) {
    if (node && node->lazy != 0) {
        node->key += node->lazy;
        if (node->left) {
            node->left->lazy += node->lazy;
        }
        if (node->right) {
            node->right->lazy += node->lazy;
        }
        node->lazy = 0;
    }
}

void split(Node* node, int key, Node*& left, Node*& right) {
    if (!node) {
        left = right = nullptr;
        return;
    }
    apply(node);
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
    if (!left || !right)
        return left ? left : right;
    if (left->priority > right->priority) {
        apply(left);
        left->right = merge(left->right, right);
        upd_cnt(left);
        return left;
    } else {
        apply(right);
        right->left = merge(left, right->left);
        upd_cnt(right);
        return right;
    }
}

Node* insert(Node* root, Node* node) {
    if (!root) {
        return node;
    }
    apply(root);
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

int query(Node* root, int key) {
    if (!root)
        return 0;
    apply(root);
    if (root->key > key) {
        return query(root->left, key);
    } else {
        return 1 + get_cnt(root->left) + query(root->right, key);
    }
}

Node* inc_update(Node* root, int k) {
    Node* left = nullptr;
    Node* right = nullptr;
    split(root, k, left, right);
    if (left) {
        left->lazy -= 1;
    }
    root = merge(left, right);
    return root;
}

int main(){
    IOS;
    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        Node* root = nullptr;
        int n, s;
        cin >> n >> s;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            int l = n, r = 1e7, ans = 1e7;
            while (l <= r) {
                int mid = (l + r) / 2;
                int k = query(root, mid);
                if (mid - k >= a) {
                    ans = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            inc_update(root, ans);
            root = insert(root, new Node(ans));
        }
        int lf, rt;
        int k = query(root, s);
        if (k == 0) {
            lf = -1;
        } else {
            int l = 0, r = s, ans = 0;
            while (l <= r) {
                int mid = (l + r) / 2;
                int x = query(root, mid);
                if (x != k) {
                    ans = max(ans, mid + 1);
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            lf = ans;
        }
        if (k == n) {
            rt = -1;
        } else {
            int l = s, r = 1e7, ans = 1e7;
            while (l <= r) {
                int mid = (l + r) / 2;
                int x = query(root, mid);
                if (x != k) {
                    ans = min(ans, mid);
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            rt = ans;
        }
        cout << "Case #" << tt << ": ";
        int ct = n - k, ans;
        if (lf == -1) {
            ans = rt - s;
        } else if (rt == -1) {
            ans = s - lf;
        } else {
            ans = min(rt - s, s - lf);
        }
        if (ans == 0) {
            ct++;
        } else if (lf != -1 && rt != -1 && s - lf < rt - s) {
            ct++;
        }
        cout << max(1, ct) << " " << ans << endl;
    }
    return 0;
}
