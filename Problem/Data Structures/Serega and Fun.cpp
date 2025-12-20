//https://codeforces.com/contest/455/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int SQ = 1000;

int freq[N / SQ + 5][N];
int bl[N];
int pass[N];
int a[N];

mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    int val;
    int priority;
    int cnt;
    Node* left;
    Node* right;

    Node(int val) : val(val), priority(gen()), cnt(1), left(nullptr), right(nullptr) {}
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

Node* root = nullptr;

void insert(int x, int j) {
    Node* new_node = new Node(x);
    Node *left, *right;
    split(root, j, left, right);
    root = merge(merge(left, new_node), right);
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

int dfs(Node* node, int k) {
    int ans = node->val == k;
    if (node->left) {
        ans += dfs(node->left, k);
    }
    if (node->right) {
        ans += dfs(node->right, k);
    }
    return ans;
}


int main() {
    IOS;
    int n;
    cin >> n;
    vector<int> pos;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        insert(a[i], i);
        bl[i] = i / SQ;
        if (i != 0 && bl[i] != bl[i - 1]) {
            pass[i - 1] = 1;
            pos.push_back(i - 1);
        }
        freq[bl[i]][a[i]]++;
    }
    int q;
    cin >> q;
    int lastans = 0;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int L, R;
            cin >> L >> R;
            int l = (L + lastans - 1) % n;
            int r = (R + lastans - 1) % n;
            if (l > r) {
                swap(l, r);
            }

            if (bl[l] != bl[r]) {
                int j = lower_bound(pos.begin(), pos.end(), l) - pos.begin();
                while (j != pos.size()) {
                    int ind = pos[j];
                    if (ind > r) {
                        break;
                    }
                    int val = get_kth(root, ind);
                    freq[j][val]--;
                    if (ind + 1 <= r) {
                        freq[j + 1][val]++;
                    } else {
                        freq[l / SQ][val]++;
                    }
                    j++;
                }
                if (!pass[r]) {
                    int val = get_kth(root, r);
                    freq[r / SQ][val]--;
                    freq[l / SQ][val]++;
                }
            }

            Node *a, *b, *c, *d, *e, *f;
            split(root, l, a, b);
            split(b, r - l, c, d);
            split(d, 1, e, f);

            root = merge(a, merge(e, merge(c, f)));

        } else {
            int L, R, K;
            cin >> L >> R >> K;
            int l = (L + lastans - 1) % n;
            int r = (R + lastans - 1) % n;
            int k = (K + lastans - 1) % n;
            if (l > r) {
                swap(l, r);
            }
            if (bl[l] == bl[r]) {
                Node *a, *b, *c, *d;
                split(root, l, a, b);
                split(b, r - l + 1, c, d);
                lastans = dfs(c, k);
                root = merge(a, merge(c, d));
            } else {
                int lbl = bl[l] + 1, rbl = bl[r] - 1;
                int ans = 0;
                for (int i = lbl; i <= rbl; i++) {
                    ans += freq[i][k];
                }
                int L = lbl * SQ - 1, R = (rbl + 1) * SQ;

                Node *a, *b, *c, *d;
                split(root, l, a, b);
                split(b, L - l + 1, c, d);
                ans += dfs(c, k);
                root = merge(a, merge(c, d));

                a = nullptr, b = nullptr, c = nullptr, d = nullptr;
                split(root, R, a, b);
                split(b, r - R + 1, c, d);
                ans += dfs(c, k);
                root = merge(a, merge(c, d));

                lastans = ans;
            }
            cout << lastans << endl;

        }
    }
    return 0;
}
