//bbc16
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


const int N = 4e5 + 5;

const ll M = 1e9 + 7;
const ll P = 26, INV_P = 576923081;
const ll Q = 53, INV_Q = 56603774;

ll pw_p[N], pw_q[N];
ll inv_p[N], inv_q[N];

mt19937 gene(3);

struct Node {
    int key;
    int priority;
    int ct;

    pair<ll, ll> lazy_falling;
    pair<ll, ll> lazy_rising;

    pair<ll, ll> val_falling;
    pair<ll, ll> val_rising;

    pair<ll, ll> sum_falling;
    pair<ll, ll> sum_rising;

    Node *left;
    Node *right;
    Node(pair<ll, ll> falling, pair<ll, ll> rising) {
        priority = gene();
        ct =1;
        lazy_falling = {1, 1};
        lazy_rising = {1, 1};
        val_falling = falling;
        val_rising = rising;
        sum_falling = falling;
        sum_rising = rising;

        left = nullptr;
        right = nullptr;
    }
};

void apply(Node *node) {
    if (!node) {
        return;
    }
    node->sum_falling.first = node->sum_falling.first * node->lazy_falling.first % M;
    node->sum_falling.second = node->sum_falling.second * node->lazy_falling.second % M;
    node->val_falling.first = node->val_falling.first * node->lazy_falling.first % M;
    node->val_falling.second = node->val_falling.second * node->lazy_falling.second % M;

    node->sum_rising.first = node->sum_rising.first * node->lazy_rising.first % M;
    node->sum_rising.second = node->sum_rising.second * node->lazy_rising.second % M;
    node->val_rising.first = node->val_rising.first * node->lazy_rising.first % M;
    node->val_rising.second = node->val_rising.second * node->lazy_rising.second % M;

    if (node->left) {
        node->left->lazy_falling.first = node->left->lazy_falling.first * node->lazy_falling.first % M;
        node->left->lazy_falling.second = node->left->lazy_falling.second * node->lazy_falling.second % M;

        node->left->lazy_rising.first = node->left->lazy_rising.first * node->lazy_rising.first % M;
        node->left->lazy_rising.second = node->left->lazy_rising.second * node->lazy_rising.second % M;
    }
    if (node->right) {
        node->right->lazy_falling.first = node->right->lazy_falling.first * node->lazy_falling.first % M;
        node->right->lazy_falling.second = node->right->lazy_falling.second * node->lazy_falling.second % M;

        node->right->lazy_rising.first = node->right->lazy_rising.first * node->lazy_rising.first % M;
        node->right->lazy_rising.second = node->right->lazy_rising.second * node->lazy_rising.second % M;
    }
    node->lazy_falling = {1, 1};
    node->lazy_rising = {1, 1};

}

void pull(Node *node) {
    apply(node->left);
    apply(node->right);

    node->ct = 1 + (node->left ? node->left->ct : 0) + (node->right ? node->right->ct : 0);

    node->sum_falling.first = (node->val_falling.first + (node->left ? node->left->sum_falling.first : 0) + (node->right ? node->right->sum_falling.first : 0)) % M;
    node->sum_falling.second = (node->val_falling.second + (node->left ? node->left->sum_falling.second : 0) + (node->right ? node->right->sum_falling.second : 0)) % M;

    node->sum_rising.first = (node->val_rising.first + (node->left ? node->left->sum_rising.first : 0) + (node->right ? node->right->sum_rising.first : 0)) % M;
    node->sum_rising.second = (node->val_rising.second + (node->left ? node->left->sum_rising.second : 0) + (node->right ? node->right->sum_rising.second : 0)) % M;
}

void split(Node *node, int k, Node *&left, Node *&right) { //k idu levo
    if (!node) {
        left = nullptr;
        right = nullptr;
        return;
    }
    apply(node);
    int sz = 1 + (node->left ? node->left->ct : 0);
    if (k >= sz) {
        split(node->right, k - sz, node->right, right);
        left = node;
        pull(left);
    } else {
        split(node->left, k, left, node->left);
        right = node;
        pull(right);
    }
}


Node* merge(Node *left, Node *right) {
    if (!left) {
        return right;
    }
    if (!right) {
        return left;
    }
    if (right->priority > left->priority) {
        apply(right);
        right->left = merge(left, right->left);
        pull(right);
        return right;
    } else {
        apply(left);
        left->right = merge(left->right, right);
        pull(left);
        return left;
    }
}

int main() {
    IOS;
    pw_p[0] = 1, pw_q[0] = 1;
    inv_p[0] = 1, inv_q[0] = 1;
    for (int i = 1; i < N; i++) {
        pw_p[i] = pw_p[i - 1] * P % M;
        pw_q[i] = pw_q[i - 1] * Q % M;
        inv_p[i] = inv_p[i - 1] * INV_P % M;
        inv_q[i] = inv_q[i - 1] * INV_Q % M;
    }
    int n;
    cin >> n;
    string s;
    cin >> s;
    Node *root = nullptr;
    for (int i = 0; i < n; i++) {
        if (root) {
            root->lazy_falling.first = root->lazy_falling.first * P % M;
            root->lazy_falling.second = root->lazy_falling.second * Q  % M;
        }
        int c = s[i] - 'a' + 1;
        root = merge(root, new Node(make_pair(c, c), make_pair(c * pw_p[i] % M, c * pw_q[i] % M)));
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            char ch; int j;
            cin >> ch >> j;
            int c = ch - 'a' + 1;
            int n = root->ct;
            Node *a, *b;
            split(root, j, a, b);
            if (a) {
                a->lazy_falling.first = a->lazy_falling.first * P % M;
                a->lazy_falling.second = a->lazy_falling.second * Q  % M;
            }
            if (b) {
                b->lazy_rising.first = b->lazy_rising.first * P % M;
                b->lazy_rising.second = b->lazy_rising.second * Q  % M;
            }
            root = merge(a, merge(new Node(make_pair(c * pw_p[n - j] % M, c * pw_q[n - j] % M), make_pair(c * pw_p[j] % M, c * pw_q[j] % M)), b));

        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            int n = root->ct;
            Node *a, *b, *c, *d;
            split(root, l, a, b);
            split(b, r - l + 1, c, d);
            apply(c);

            auto h_rising = c->sum_rising;
            auto h_falling = c->sum_falling;

            h_rising.first = h_rising.first * inv_p[l] % M;
            h_rising.second = h_rising.second * inv_q[l] % M;

            h_falling.first = h_falling.first * inv_p[n - 1 - r] % M;
            h_falling.second = h_falling.second * inv_q[n - 1 - r] % M;

            if (h_rising == h_falling) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
            root = merge(a, merge(c, d));
        }
    }

    return 0;
}
