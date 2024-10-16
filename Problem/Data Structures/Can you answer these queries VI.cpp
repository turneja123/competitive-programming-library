//https://www.spoj.com/problems/GSS6/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());
const long long INF = 1e10;

struct Node {
    long long val;
    long long mx;
    long long best;
    long long pref;
    long long suf;
    long long sum;
    int priority;
    int cnt;
    Node* left;
    Node* right;

    Node(long long val) : val(val), mx(val), best(val), pref(val), suf(val), sum(val), priority(generator()), cnt(1), left(nullptr), right(nullptr) {}
};

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

long long get_sum(Node* node) {
    return node ? node->sum : 0;
}

long long get_mx(Node* node) {
    return node ? node->mx : -INF;
}

long long get_pref(Node* node) {
    return node ? node->pref : -INF;
}

long long get_suf(Node* node) {
    return node ? node->suf : -INF;
}

long long get_best(Node* node) {
    return node ? node->best: -INF;
}

void upd_cnt(Node* node) {
    if (node) {
        node->cnt = 1 + get_cnt(node->left) + get_cnt(node->right);
        node->sum = node->val + get_sum(node->left) + get_sum(node->right);
        node->mx = max({node->val, get_mx(node->left), get_mx(node->right)});
        if (node->left) {
            node->pref = max({node->left->pref, node->left->sum + node->val, node->left->sum + node->val + get_pref(node->right)});
        } else {
            node->pref = max({node->val, node->val + get_pref(node->right)});
        }
        if (node->right) {
            node->suf = max({node->right->suf, node->right->sum + node->val, node->right->sum + node->val + get_suf(node->left)});
        } else {
            node->suf = max({node->val, node->val + get_suf(node->left)});
        }
        node->best = max({node->mx, get_best(node->left), get_best(node->right), node->val + get_pref(node->right), get_suf(node->left) + node->val, get_suf(node->left) + node->val + get_pref(node->right), node->suf, node->pref});
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

class Treap {
public:
    Node* root;

    Treap() : root(nullptr) {}

    int size() {
        return get_cnt(root);
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

    long long query(int l, int r) {
        Node *a, *b, *c, *d;
        split(root, l, a, b);
        split(b, r - l + 1, c, d);
        long long ans = ((c) ? c->best : -INF);
        root = merge(merge(a, c), d);
        return ans;
    }
};

int main() {
    IOS;
    Treap tr;
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        tr.insert(a, tr.size());
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        char t;
        cin >> t;
        if (t == 'I') {
            int j, x;
            cin >> j >> x;
            j--;
            tr.insert(x, j);
        } else if (t == 'D') {
            int j;
            cin >> j;
            j--;
            tr.erase(j);
        } else if (t == 'R') {
            int j, x;
            cin >> j >> x;
            j--;
            tr.erase(j);
            tr.insert(x, j);
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            cout << tr.query(l, r) << endl;
        }
    }
    return 0;
}
