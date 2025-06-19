//https://codeforces.com/contest/2117/problem/H
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int INF = 1e9;

int a[N];

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    int key;
    int priority;
    int cnt;
    Node* left;
    Node* right;
    int best[2];
    int pref[2];
    int suf[2];
    int l;
    int r;
    int sum;

    Node(int _key) {
        key = _key;
        priority = generator();
        cnt = 1;
        left = nullptr;
        right = nullptr;
        best[1] = 1, best[0] = -INF;
        pref[1] = 1, pref[0] = -INF;
        suf[1] = 1, suf[0] = -INF;
        l = _key;
        r = _key;
        sum = 1;
    }
};

Node* root[N];

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

void upd_cnt(Node* node) {
    if (!node) {
        return;
    }
    Node* left = node->left;
    Node* right = node->right;
    node->cnt = 1 + get_cnt(left) + get_cnt(right);
    node->best[1] = 1, node->best[0] = -INF;
    node->pref[1] = -INF, node->pref[0] = -INF;
    node->suf[1] = -INF, node->suf[0] = -INF;
    node->sum = 1;
    node->l = node->key, node->r = node->key;
    if (!left) {
        node->pref[1] = 1;
    }
    if (!right) {
        node->suf[1] = 1;
    }
    if (left) {
        int A = (left->r - left->l + 1) % 2;
        int distA = node->key - left->r - 1;
        for (int i = 0; i < 2; i++) {
            node->pref[i] = max(node->pref[i], left->pref[i]);
            node->best[i] = max(node->best[i], left->best[i]);
        }

        node->pref[(A + 1 + distA) % 2] = max(node->pref[(A + 1 + distA) % 2], left->sum + 1 - distA);
        if (!right) {
            for (int i = 0; i < 2; i++) {
                node->suf[(1 + distA + i) % 2] = max(node->suf[(1 + distA + i) % 2], left->suf[i] + 1 - distA);
            }
        }
        for (int i = 0; i < 2; i++) {
            node->best[(i + 1 + distA) % 2] = max(node->best[(i + 1 + distA) % 2], left->suf[i] + 1 - distA);
        }
        node->l = min(node->l, left->l);
        node->r = max(node->r, left->r);
        node->sum += left->sum - distA;
    }
    if (right) {
        int B = (right->r - right->l + 1) % 2;
        int distB = right->l - node->key - 1;
        for (int i = 0; i < 2; i++) {
            node->suf[i] = max(node->suf[i], right->suf[i]);
            node->best[i] = max(node->best[i], right->best[i]);
        }

        if (!left) {
            for (int i = 0; i < 2; i++) {
                node->pref[(i + 1 + distB) % 2] = max(node->pref[(i + 1 + distB) % 2], right->pref[i] + 1 - distB);
            }
        }
        node->suf[(B + 1 + distB) % 2] = max(node->suf[(B + 1 + distB) % 2], right->sum + 1 - distB);
        for (int i = 0; i < 2; i++) {
            node->best[(i + 1 + distB) % 2] = max(node->best[(i + 1 + distB) % 2], right->pref[i] + 1 - distB);
       }

        node->l = min(node->l, right->l);
        node->r = max(node->r, right->r);
        node->sum += right->sum - distB;
    }
    if (left && right) {
        int A = (left->r - left->l + 1) % 2;
        int distA = node->key - left->r - 1;
        int B = (right->r - right->l + 1) % 2;
        int distB = right->l - node->key - 1;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                node->best[(i + j + 1 + distA + distB) % 2] = max(node->best[(i + j + 1 + distA + distB) % 2], left->suf[i] - distA + 1 - distB + right->pref[j]);
            }
        }
        for (int i = 0; i < 2; i++) {
            node->suf[(B + 1 + i + distA + distB) % 2] = max(node->suf[(B + 1 + i + distA + distB) % 2], right->sum - distB + 1 - distA + left->suf[i]);
        }
        for (int j = 0; j < 2; j++) {
            node->pref[(A + 1 + j + distA + distB) % 2] = max(node->pref[(A + 1 + j + distA + distB) % 2], left->sum - distA + 1 - distB + right->pref[j]);
        }

    }
    node->best[0] = max({node->best[0], node->pref[0], node->suf[0]});
    node->best[1] = max({node->best[1], node->pref[1], node->suf[1]});
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
        delete root;
        return temp;
    }
    upd_cnt(root);
    return root;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            root[i] = nullptr;
        }
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
            root[a[i]] = insert(root[a[i]], new Node(i));
        }
        multiset<int> st;
        for (int i = 0; i < n; i++) {
            if (root[i] != nullptr) {
                int x = max(root[i]->best[0] / 2, (root[i]->best[1] - 1) / 2);
                st.insert(x);
            }
        }
        for (int j = 0; j < q; j++) {
            int i, v;
            cin >> i >> v;
            i--, v--;
            int x = max(root[a[i]]->best[0] / 2, (root[a[i]]->best[1] - 1) / 2);
            st.erase(st.find(x));
            root[a[i]] = erase(root[a[i]], i);
            if (root[a[i]] != nullptr) {
                x = max(root[a[i]]->best[0] / 2, (root[a[i]]->best[1] - 1) / 2);
                st.insert(x);
            }

            a[i] = v;
            if (root[a[i]] != nullptr) {
                x = max(root[a[i]]->best[0] / 2, (root[a[i]]->best[1] - 1) / 2);
                st.erase(st.find(x));
            }
            root[a[i]] = insert(root[a[i]], new Node(i));
            x = max(root[a[i]]->best[0] / 2, (root[a[i]]->best[1] - 1) / 2);
            st.insert(x);
            cout << *st.rbegin() << " ";
        }
        cout << endl;
        for (int i = 0; i < n; i++) {
            root[i] = nullptr;
        }
    }

    return 0;
}
