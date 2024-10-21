//https://csacademy.com/contest/archive/task/strings/statement/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;
const long long M = 1e9 + 7;
const long long P = 26, INV_P = 576923081;
const long long Q = 53, INV_Q = 56603774;

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

long long pw_p[N], inv_p[N];
long long pw_q[N], inv_q[N];

struct Node {
    int val;
    long long pref_p;
    long long pref_q;
    long long suf_p;
    long long suf_q;
    int priority;
    int cnt;
    int lazy;
    Node* left;
    Node* right;

    Node(int val) : val(val), pref_p(val), pref_q(val), suf_p(val), suf_q(val), priority(generator()), cnt(1), lazy(0), left(nullptr), right(nullptr) {}
};

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

pair<long long, long long> get_p(Node* node) {
    return node ? make_pair(node->pref_p, node->suf_p) : make_pair(0ll, 0ll);
}

pair<long long, long long> get_q(Node* node) {
    return node ? make_pair(node->pref_q, node->suf_q) : make_pair(0ll, 0ll);
}

void apply(Node* node) {
    if (node && node->lazy != 0) {
        swap(node->left, node->right);
        swap(node->pref_p, node->suf_p);
        swap(node->pref_q, node->suf_q);
        if (node->left) {
            node->left->lazy ^= node->lazy;
        }
        if (node->right) {
            node->right->lazy ^= node->lazy;
        }
        node->lazy = 0;
    }
}

void upd_cnt(Node* node) {
    if (node) {
        apply(node->left);
        apply(node->right);
        node->cnt = 1 + get_cnt(node->left) + get_cnt(node->right);
        pair<long long, long long> lf_p = get_p(node->left);
        pair<long long, long long> lf_q = get_q(node->left);
        pair<long long, long long> rt_p = get_p(node->right);
        pair<long long, long long> rt_q = get_q(node->right);

        node->pref_p = (lf_p.first + pw_p[get_cnt(node->left)] * node->val + pw_p[1 + get_cnt(node->left)] * rt_p.first) % M;
        node->pref_q = (lf_q.first + pw_q[get_cnt(node->left)] * node->val + pw_q[1 + get_cnt(node->left)] * rt_q.first) % M;
        node->suf_p = (rt_p.second + pw_p[get_cnt(node->right)] * node->val + pw_p[1 + get_cnt(node->right)] * lf_p.second) % M;
        node->suf_q = (rt_q.second + pw_q[get_cnt(node->right)] * node->val + pw_q[1 + get_cnt(node->right)] * lf_q.second) % M;
    }
}

void split(Node* node, int k, Node*& left, Node*& right) {
    if (!node) {
        left = right = nullptr;
        return;
    }
    apply(node);
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

void dfs(Node *node) {
    if (!node) {
        return;
    }
    apply(node);
    if (node->left) {
        dfs(node->left);
    }
    cout << (char)('a' + node->val);
    if (node->right) {
        dfs(node->right);
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

    void splice(int l, int r, int k) {
        Node *a, *b, *c, *d, *e, *f, *t;
        split(root, l, a, b);
        split(b, r - l + 1, c, d);
        t = merge(a, d);
        split(t, k, e, f);
        root = merge(e, merge(c, f));

    }

    void rev_update(int l, int r) {
        Node *a, *b, *c, *d;
        split(root, l, a, b);
        split(b, r - l + 1, c, d);
        if (c) {
            c->lazy ^= 1;
        }
        root = merge(merge(a, c), d);
    }

    void print() {
        dfs(root);
        cout << endl;
    }

    string query(int l, int r) {
        Node *a, *b, *c, *d;
        split(root, l, a, b);
        split(b, r - l + 1, c, d);
        string ans;
        if (c->pref_p == c->suf_p && c->pref_q == c->suf_q) {
            ans = "YES";
        } else {
            ans = "NO";
        }
        root = merge(merge(a, c), d);
        return ans;
    }
};

int main() {
    IOS;
    pw_p[0] = 1, inv_p[0] = 1;
    pw_q[0] = 1, inv_q[0] = 1;
    for (int i = 1; i < N; i++) {
        pw_p[i] = pw_p[i - 1] * P % M;
        pw_q[i] = pw_q[i - 1] * Q % M;
        inv_p[i] = inv_p[i - 1] * INV_P % M;
        inv_q[i] = inv_q[i - 1] * INV_Q % M;
    }
    Treap tr;
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    for (int i = 0; i < n; i++) {
        tr.insert(s[i] - 'a', tr.size());
    }
    for (int i = 0; i < q; i++) {
        char c;
        cin >> c;
        if (c == 'Q') {
            int l, r;
            cin >> l >> r;
            l--, r--;
            cout << tr.query(l, r) << endl;
        } else {
            int t;
            cin >> t;
            if (t == 1) {
                int l, r, k;
                cin >> l >> r >> k;
                l--, r--;
                tr.splice(l, r, k);
            } else if (t == 2) {
                int l, r;
                cin >> l >> r;
                l--, r--;
                tr.rev_update(l, r);
            } else {
                int j; char c;
                cin >> j >> c;
                j--;
                tr.insert(c - 'a', j);

            }
        }
    }
    return 0;
}
