//https://cses.fi/problemset/task/3152/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int val[N];
int inv[N];

struct BIT {
    int n;
    vector<int> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void upd(int i, int val) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    void upd(int l, int r, int val) {
        upd(l, val);
        upd(r + 1, -val);
    }
    int query(int i) {
        int ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

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

void print(Node* node) {
    if (node->left) {
        print(node->left);
    }
    cout << node->val << " ";
    if (node->right) {
        print(node->right);
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
};

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i;
    }
    sort(v.begin(), v.end());
    int last = -1, m = -1;
    for (int i = 0; i < n; i++) {
        if (last != v[i].first) {
            m++;
            last = v[i].first;
        }
        a[v[i].second] = m;
        val[m] = v[i].first;
    }
    m++;
    BIT bit(m);
    vector<pair<int, int>> items;
    for (int i = 0; i < n; i++) {
        inv[i] = (a[i] == m ? 0 : bit.query(a[i] + 1, m));
        bit.upd(a[i], 1);
        items.push_back({a[i], i});
    }
    sort(items.begin(), items.end(), [](pair<int, int> &a, pair<int, int> &b) {
         if (a.first != b.first) {
            return a.first > b.first;
         }
         return a.second > b.second;
    });
    Treap tr;
    for (auto [x, j] : items) {
        x = val[x];
        j = max(0, inv[j] - k);
        tr.insert(x, j);
    }
    print(tr.root);
    return 0;
}
