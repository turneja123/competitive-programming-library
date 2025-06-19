//https://www.codechef.com/problems/GRIDPATHHD
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const ll INF = 1e18;

string s[2];

long long sum[2][N];

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    int key;
    int priority;
    int cnt;
    long long sum;
    Node* left;
    Node* right;

    Node(int key) : key(key), sum(abs(key)), priority(generator()), cnt(1), left(nullptr), right(nullptr) {}
};

Node *t1 = nullptr;
Node *t2 = nullptr;

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

ll get_sum(Node* node) {
    return node ? node->sum : 0;
}

void upd_cnt(Node* node) {
    if (node) {
        node->cnt = 1 + get_cnt(node->left) + get_cnt(node->right);
        node->sum = abs(node->key) + get_sum(node->left) + get_sum(node->right);
    }
}

void split(Node* node, int key, Node*& left, Node*& right) {
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

long long split_cnt(Node* node, int k) {
    if (!node) {
        return 0;
    }
    long long ans = 0;
    if (get_cnt(node->left) >= k) {
        ans += split_cnt(node->left, k);
    } else {
        ans += get_sum(node->left) + abs(node->key);
        ans += split_cnt(node->right, k - get_cnt(node->left) - 1);
    }
    return ans;
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

Node* insert(Node* root, Node* node) {
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

Node* erase(Node* root, int key) {
    if (!root)
        return root;
    if (key < root->key) {
        root->left = erase(root->left, key);
    } else if (key > root->key) {
        root->right = erase(root->right, key);
    } else {
        Node* temp = merge(root->left, root->right);
        //delete root;
        return temp;
    }
    upd_cnt(root);
    return root;
}


int ct1 = 0, ct2 = 0;

long long calc(int k, int n) {
    long long ans = 0;
    ans += split_cnt(t1, k);
    ans -= split_cnt(t2, n - k + 1);
    ans += sum[1][k - 1] - sum[0][k - 1];
    return ans;

}

long long solve(int n) {

    int l = max(1, n - ct2 + 1), r = ct1;
    while (r - l >= 3) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;

        long long f1 = -calc(m1, n);
        long long f2 = -calc(m2, n);

        if (f1 < f2) {
            l = m1 + 1;
        } else {
            r = m2 - 1;
        }
    }
    long long ans = 1e18;
    for (; l <= r; l++) {
        ans = min(ans, calc(l, n));
    }
    if (ans == INF) {
        ans = -1;
    }
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        cin >> s[0] >> s[1];

        for (int i = 0; i < n; i++) {
            sum[0][i] = (i == 0 ? 0 : sum[0][i - 1]) + i;
            if (s[0][i] == '1') {
                t1 = insert(t1, new Node(i));
                ct1++;
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            sum[1][i] = (i == n - 1 ? 0 : sum[1][i + 1]) + i;
            if (s[1][i] == '1') {
                t2 = insert(t2, new Node(-i));
                ct2++;
            }
        }

        cout << solve(n) << endl;

        for (int k = 0; k < q; ++k) {
            int i, j;
            cin >> i >> j;
            i--, j--;
            if (i == 0 && s[i][j] == '0') {
                t1 = insert(t1, new Node(j));
                s[i][j] = '1';
                ct1++;
            } else if (i == 0 && s[i][j] == '1') {
                t1 = erase(t1, j);
                s[i][j] = '0';

                ct1--;
            } else if (i == 1 && s[i][j] == '0') {
                t2 = insert(t2, new Node(-j));
                s[i][j] = '1';
                ct2++;
            } else {
                t2 = erase(t2, -j);
                s[i][j] = '0';

                ct2--;
            }
            cout << solve(n) << endl;
        }
        t1 = nullptr;
        t2 = nullptr;
        ct1 = 0, ct2 = 0;

    }
    return 0;
}
