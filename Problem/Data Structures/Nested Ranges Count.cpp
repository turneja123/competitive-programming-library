//https://cses.fi/problemset/task/2169/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int R = 1e9 + 5;

pair<pair<int, int>, int> a[N];

int x[N], y[N];

struct Node {
    int val;
    struct Node* left;
    struct Node* right;
};

int query(Node* node, int l, int r, int lq, int rq) {
    if (r < lq || l > rq) {
        return 0;
    }
    if (lq <= l && rq >= r) {
        return node->val;
    }
    int mid = (l + r) / 2, ans = 0;
    if (node->left != nullptr) {
        ans += query(node->left, l, mid, lq, rq);
    }
    if (node->right != nullptr) {
        ans += query(node->right, mid + 1, r, lq, rq);
    }
    return ans;

}

void update(Node* node, int l, int r, int ind, int val) {
    if (l == r) {
        node->val += val;
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        if (node->left == nullptr) {
            node->left = new Node();
        }
        update(node->left, l, mid, ind, val);
    } else {
        if (node->right == nullptr) {
            node->right = new Node();
        }
        update(node->right, mid + 1, r, ind, val);
    }
    node->val = 0;
    if (node->left != nullptr) {
        node->val += node->left->val;
    }
    if (node->right != nullptr) {
        node->val += node->right->val;
    }
}

bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
    if (a.first.first != b.first.first) {
        return a.first.first < b.first.first;
    }
    return a.first.second > b.first.second;
}

int main() {
    IOS;
    struct Node* root = new Node();
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        a[i] = make_pair(make_pair(l, r), i);
        update(root, 0, R - 1, r, 1);
    }
    sort(a, a + n, comp);
    for (int i = 0; i < n; i++) {
        int l = a[i].first.first, r = a[i].first.second;
        update(root, 0, R - 1, r, -1);
        x[a[i].second] = query(root, 0, R - 1, 0, r);
    }
    for (int i = 0; i < n; i++) {
        cout << x[i] << " ";
    }
    cout << endl;
    delete(root);
    root = new Node();
    for (int i = 0; i < n; i++) {
        int l = a[i].first.first, r = a[i].first.second;
        y[a[i].second] = query(root, 0, R - 1, r, R - 1);
        update(root, 0, R - 1, r, 1);
    }
    for (int i = 0; i < n; i++) {
        cout << y[i] << " ";
    }
    return 0;
}
