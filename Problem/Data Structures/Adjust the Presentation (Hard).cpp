//https://codeforces.com/contest/2021/problem/C2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int x[N];
int pos[N];

set<int> st[N];
mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());
tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> tr;

struct Node {
    int val;
    int priority;
    int cnt;
    Node* left;
    Node* right;

    Node(int val) : val(val), priority(generator()), cnt(1), left(nullptr), right(nullptr) {}
};

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

void upd_cnt(Node* node) {
    if (node) {
        node->cnt = 1 + get_cnt(node->left) + get_cnt(node->right);
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

int get_kth(Node* node, int k) {
    if (!node) {
        return -1;
    }
    int left_cnt = get_cnt(node->left);
    if (k < left_cnt) {
        return get_kth(node->left, k);
    } else if (k == left_cnt) {
        return node->val;
    } else {
        return get_kth(node->right, k - left_cnt - 1);
    }
}

class Treap {
public:
    Node* root;
    int inversion_count;

    Treap() : root(nullptr), inversion_count(0) {}

    int size() {
        return get_cnt(root);
    }

    int get_element(int k) {
        return get_kth(root, k);
    }

    void insert(int x, int j) {
        int n = size();
        int left_val = (j > 0) ? get_element(j - 1) : -1;
        int right_val = (j < n) ? get_element(j) : 1e9;
        if (j > 0 && j < n && left_val > right_val) {
            inversion_count--;
        }
        Node* new_node = new Node(x);
        Node *left, *right;
        split(root, j, left, right);
        root = merge(merge(left, new_node), right);
        if (j > 0) {
            if (left_val > x) {
                inversion_count++;
            }
        }
        if (j < n) {
            if (x > right_val) {
                inversion_count++;
            }
        }
    }
    void erase(int j) {
        int n = size();
        if (j < 0 || j >= n) {
            return;
        }
        int left_val = (j > 0) ? get_element(j - 1) : -1;
        int erased_val = get_element(j);
        int right_val = (j < n - 1) ? get_element(j + 1) : 1e9;
        if (j > 0) {
            if (left_val > erased_val) {
                inversion_count--;
            }
        }
        if (j < n - 1) {
            if (erased_val > right_val) {
                inversion_count--;
            }
        }

        if (j > 0 && j < n - 1) {
            if (left_val > right_val) {
                inversion_count++;
            }
        }
        Node *left, *mid, *right;
        split(root, j, left, right);
        split(right, 1, mid, right);
        root = merge(left, right);
    }

    bool is_sorted() const {
        return inversion_count == 0;
    }
};

int main() {
    IOS;
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n, m, q;
        cin >> n >> m >> q;
        Treap seq;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
            pos[a[i]] = i;
        }
        for (int i = 0; i < m; i++) {
            cin >> x[i];
            x[i]--;
            st[pos[x[i]]].insert(i);
        }
        for (int i = 0; i < n; i++) {
            st[i].insert(m + i);
            int k = tr.order_of_key(*st[i].begin());
            seq.insert(i, k);
            tr.insert(*st[i].begin());
        }
        cout << ((seq.is_sorted()) ? "YA" : "TIDAK") << endl;
        for (int i = 0; i < q; i++) {
            int j, p;
            cin >> j >> p;
            j--, p--;
            if (*st[pos[x[j]]].begin() == j) {
                auto it = st[pos[x[j]]].begin();
                int k = tr.order_of_key(*it);
                seq.erase(k);
                tr.erase(*it);
                it++;
                k = tr.order_of_key(*it);
                seq.insert(pos[x[j]], k);
                tr.insert(*it);
            }
            st[pos[x[j]]].erase(j);
            x[j] = p;
            if (*st[pos[x[j]]].begin() > j) {
                auto it = st[pos[x[j]]].begin();
                int k = tr.order_of_key(*it);
                seq.erase(k);
                tr.erase(*it);
                k = tr.order_of_key(j);
                seq.insert(pos[x[j]], k);
                tr.insert(j);
            }
            st[pos[x[j]]].insert(j);
            cout << ((seq.is_sorted()) ? "YA" : "TIDAK") << endl;
        }
        tr.clear();
        for (int i = 0; i < n; i++) {
            st[i].clear();
        }
    }
    return 0;
}
