//https://judge.yosupo.jp/problem/point_add_rectangle_sum
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int MAX = 1e7 + 5;
const int R = 1e9 + 5;

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct TreapNode {
    pair<int, int> key;
    int priority;
    int cnt;
    long long val;
    long long sum;
    TreapNode* left;
    TreapNode* right;

    TreapNode(pair<int, int> key, long long val) : key(key), priority(generator()), cnt(1), val(val), sum(val), left(nullptr), right(nullptr) {}
};

int get_cnt(TreapNode* node) {
    return node ? node->cnt : 0;
}

long long get_sum(TreapNode* node) {
    return node ? node->sum : 0;
}

void upd_cnt(TreapNode* node) {
    if (node) {
        node->cnt = 1 + get_cnt(node->left) + get_cnt(node->right);
        node->sum = node->val + get_sum(node->left) + get_sum(node->right);
    }
}

void split(TreapNode* node, pair<int, int> key, TreapNode*& left, TreapNode*& right) {
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

TreapNode* merge(TreapNode* left, TreapNode* right) {
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

TreapNode* insert(TreapNode* root, TreapNode* node) {
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

TreapNode* erase(TreapNode* root, pair<int, int> key) {
    if (!root)
        return root;
    if (key < root->key) {
        root->left = erase(root->left, key);
    } else if (key > root->key) {
        root->right = erase(root->right, key);
    } else {
        TreapNode* temp = merge(root->left, root->right);
        //delete root;
        return temp;
    }
    upd_cnt(root);
    return root;
}

TreapNode* find(TreapNode* root, pair<int, int> key) {
    if (!root)
        return root;
    if (key < root->key) {
        return find(root->left, key);
    } else if (key > root->key) {
        return find(root->right, key);
    } else {
        return root;
    }
}

struct Node {
    TreapNode* treap;
    int left;
    int right;
    Node() : treap(nullptr), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

long long query(int node, int l, int r, int lq, int rq, int y1, int y2) {
    if (r < lq || l > rq) {
        return 0;
    }
    if (lq <= l && rq >= r) {
        TreapNode* a = nullptr;
        TreapNode* b = nullptr;
        TreapNode* c = nullptr;
        TreapNode* d = nullptr;
        split(nodes[node].treap, make_pair(y1, -1), a, b);
        split(b, make_pair(y2 + 1, -1), c, d);
        long long ans = get_sum(c);
        nodes[node].treap = merge(a, merge(c, d));
        return ans;
    }
    int mid = (l + r) / 2;
    long long ans = 0;
    if (nodes[node].left != -1) {
        ans += query(nodes[node].left, l, mid, lq, rq, y1, y2);
    }
    if (nodes[node].right != -1) {
        ans += query(nodes[node].right, mid + 1, r, lq, rq, y1, y2);
    }
    return ans;

}

void update(int node, int l, int r, int row, int col, long long val) {
    if (l == r) {
        TreapNode* treapnode = find(nodes[node].treap, make_pair(col, row));
        if (treapnode) {
            val += treapnode->val;
            nodes[node].treap = erase(nodes[node].treap, make_pair(col, row));
        }
        nodes[node].treap = insert(nodes[node].treap, new TreapNode(make_pair(col, row), val));
        return;
    }
    int mid = (l + r) / 2;
    if (row <= mid) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        update(nodes[node].left, l, mid, row, col, val);
    } else {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        update(nodes[node].right, mid + 1, r, row, col, val);
    }
    TreapNode* treapnode = find(nodes[node].treap, make_pair(col, row));
    if (treapnode) {
        val += treapnode->val;
        nodes[node].treap = erase(nodes[node].treap, make_pair(col, row));
    }
    nodes[node].treap = insert(nodes[node].treap, new TreapNode(make_pair(col, row), val));
}

int main() {
    IOS;
    nodes[idx++] = Node();
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int r, c; long long x;
        cin >> r >> c >> x;
        update(0, 0, R - 1, r, c, x);
    }

    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int r, c; long long x;
            cin >> r >> c >> x;
            update(0, 0, R - 1, r, c, x);
        } else {
            int p, q, u, v;
            cin >> p >> q >> u >> v;
            u--, v--;
            cout << query(0, 0, R - 1, p, u, q, v) << endl;
        }
    }

    return 0;
}
