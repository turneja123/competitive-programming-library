//https://dmoj.ca/problem/noi05p2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());
const int INF = 1e8;

vector<int> a;

struct Node {
    int val;
    int mx;
    int best;
    int pref;
    int suf;
    int sum;

    int lazy;
    int setVal;
    bool setValid;
    int priority;
    int cnt;
    Node* left;
    Node* right;

    Node(int val) : val(val), mx(val), best(val), pref(val), suf(val), sum(val), lazy(0), setVal(0), setValid(false), priority(generator()), cnt(1), left(nullptr), right(nullptr) {}
};

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

int get_sum(Node* node) {
    return node ? node->sum : 0;
}

int get_mx(Node* node) {
    return node ? node->mx : -INF;
}

int get_pref(Node* node) {
    return node ? node->pref : -INF;
}

int get_suf(Node* node) {
    return node ? node->suf : -INF;
}

int get_best(Node* node) {
    return node ? node->best: -INF;
}

void apply(Node* node) {
    if (!node) {
        return;
    }
    if (node->setValid) {
        node->lazy = 0;
        node->mx = node->setVal;
        node->val = node->setVal;
        int s = get_cnt(node);
        node->sum = node->val * s;
        if (node->val < 0) {
            s = 1;
        }
        node->best = node->val * s;
        node->pref = node->val * s;
        node->suf = node->val * s;


        if (node->left) {
            node->left->setValid = true;
            node->left->setVal = node->setVal;
        }
        if (node->right) {
            node->right->setValid = true;
            node->right->setVal = node->setVal;
        }
        node->setValid = false;
        node->setVal = 0;
        return;
    }
    if (node->lazy != 0) {
        swap(node->pref, node->suf);
        swap(node->left, node->right);
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
    apply(node);
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

void heapify(Node* node) {
    if (!node) {
        return;
    }
    Node* mx = node;
    if (node->left && node->left->priority > mx->priority) {
        mx = node->left;
    }
    if (node->right && node->right->priority > mx->priority) {
        mx = node->right;
    }
    if (mx != node) {
        swap(node->priority, mx->priority);
        heapify(mx);
    }
    return;
}

Node* build(vector<int> &a, int l, int n) {
    if (n == 0) {
        return nullptr;
    }
    int mid = n / 2;
    Node *node = new Node(a[l + mid]);
    node->left = build(a, l, mid);
    node->right = build(a, l + mid + 1, n - mid - 1);
    heapify(node);
    upd_cnt(node);
    return node;
}

void dfs(Node* node) {
    if (node->left) {
        dfs(node->left);
    }
    if (node->right) {
        dfs(node->right);
    }
    delete node;
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

    void insert_sequence(int l, Node* node) {
        Node *a, *b;
        split(root, l, a, b);
        root = merge(merge(a, node), b);
    }

    void erase(int l, int r) {
        Node *a, *b, *c, *d;
        split(root, l, a, b);
        split(b, r - l + 1, c, d);
        dfs(c);
        root = merge(a, d);
    }

    void create(vector<int> &a, int n) {
        root = build(a, 0, n);
    }

    void set_update(int l, int r, int x) {
        Node *a, *b, *c, *d;
        split(root, l, a, b);
        split(b, r - l + 1, c, d);
        if (c) {
            c->setVal = x;
            c->setValid = true;
        }
        root = merge(merge(a, c), d);
        return;
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

    int query(int l, int r) {
        Node *a, *b, *c, *d;
        split(root, l, a, b);
        split(b, r - l + 1, c, d);
        int ans = ((c) ? c->sum : 0);
        root = merge(merge(a, c), d);
        return ans;
    }

    int get_best() {
        apply(root);
        return root->best;
    }
};

int main() {
    IOS;
    Treap tr;
    int n, q;
    cin >> n >> q;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    tr.create(a, n);
    for (int i = 0; i < q; i++) {
        string t;
        cin >> t;
        if (t == "INSERT") {
            int posi, tot;
            cin >> posi >> tot;
            if (tot == 0) {
                continue;
            }
            vector<int> v(tot, 0);
            for (int j = 0; j < tot; j++) {
                cin >> v[j];
            }
            Node* nw = build(v, 0, tot);
            tr.insert_sequence(posi, nw);
        } else if (t == "DELETE") {
            int posi, tot;
            cin >> posi >> tot;
            posi--;
            if (tot == 0) {
                continue;
            }
            tr.erase(posi, posi + tot - 1);

        } else if (t == "MAKE-SAME") {
            int posi, tot, x;
            cin >> posi >> tot >> x;
            if (tot == 0) {
                continue;
            }
            posi--;
            tr.set_update(posi, posi + tot - 1, x);
        } else if (t == "REVERSE") {
            int posi, tot;
            cin >> posi >> tot;
            if (tot == 0) {
                continue;
            }
            posi--;
            tr.rev_update(posi, posi + tot - 1);
        } else if (t == "GET-SUM") {
            int posi, tot;
            cin >> posi >> tot;
            if (tot == 0) {
                cout << 0 << endl;
                continue;
            }
            posi--;
            cout << tr.query(posi, posi + tot - 1) << endl;
        } else {
            cout << tr.get_best() << endl;
        }
    }
    return 0;
}
