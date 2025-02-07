//https://codeforces.com/contest/1398/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    int key;
    int priority;
    int cnt;
    long long sum;
    Node* left;
    Node* right;

    Node(int key) : key(key), priority(generator()), cnt(1), sum(-key), left(nullptr), right(nullptr) {}
};

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

long long get_sum(Node* node) {
    return node ? node->sum : 0;
}

void upd_cnt(Node* node) {
    if (node) {
        node->cnt = 1 + get_cnt(node->left) + get_cnt(node->right);
        node->sum = -node->key + get_sum(node->left) + get_sum(node->right);
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

void split_by_ind(Node* node, int k, Node*& left, Node*& right) {
    if (!node) {
        left = right = nullptr;
        return;
    }
    if (get_cnt(node->left) >= k) {
        split_by_ind(node->left, k, left, node->left);
        right = node;
    } else {
        split_by_ind(node->right, k - get_cnt(node->left) - 1, node->right, right);
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

int main() {
    IOS;
    Node* a = nullptr;
    int n;
    cin >> n;
    set<int> st;
    int m = 0;
    while (n--) {
        int t, x;
        cin >> t >> x;
        if (t == 0) {
            if (x < 0) {
                x = -x;
                a = erase(a, -x);
                m--;
            } else {
                a = insert(a, new Node(-x));
                m++;
            }
        } else {
            if (x < 0) {
                x = -x;
                a = erase(a, -x);
                st.erase(x);
                m--;
            } else {
                a = insert(a, new Node(-x));
                st.insert(x);
                m++;
            }
        }
        if (st.empty()) {
            cout << get_sum(a) << endl;
            continue;
        }
        x = *st.begin();
        a = erase(a, -x);
        long long ans = x;
        Node* lf = nullptr;
        Node* rt = nullptr;
        m--;
        if (m == st.size() - 1) {
            ans += 2 * get_sum(a);
        } else {
            int s = st.size();
            split_by_ind(a, s, lf, rt);
            ans += get_sum(lf) * 2 + get_sum(rt);
            a = merge(lf, rt);
        }
        m++;
        a = insert(a, new Node(-x));
        cout << ans << endl;

    }
    return 0;
}
