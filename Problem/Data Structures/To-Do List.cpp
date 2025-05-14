//https://dmoj.ca/problem/ccc25s5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 3;

long long a[N];

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct Data {
    long long st;
    long long en;
    Data() {}
    Data(long long _st, long long _en) {
        st = _st;
        en = _en;
    }
};


struct Node {
    pair<long long, int> key;
    Data data_self;
    Data data;
    int priority;
    int cnt;
    Node* left;
    Node* right;

    Node(long long st, long long en, int i) : key(make_pair(st, i)), data_self(st, en), data(st, en), priority(generator()), cnt(1), left(nullptr), right(nullptr) {}
};

Data combine(Data &a, Data &b) {
    Data d;
    d.en = a.en + b.en;
    if (a.st + a.en >= b.st) {
        d.st = a.st;
    } else {
        d.st = b.st - a.en;
    }
    return d;
}

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

void upd_cnt(Node* node) {
    if (node) {
        node->cnt = 1 + get_cnt(node->left) + get_cnt(node->right);
        if (node->left) {
            node->data = combine(node->left->data, node->data_self);
        } else {
            node->data = node->data_self;
        }
        if (node->right) {
            node->data = combine(node->data, node->right->data);
        }
    }
}

void split(Node* node, pair<long long, int> key, Node*& left, Node*& right) {
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

Node* erase(Node* root, pair<long long, int> key) {
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
    Node* root = nullptr;
    int n, m = 0;
    long long last = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        if (c == 'A') {
            long long st, en;
            cin >> st >> en;
            st = (st + last) % N, en = (en + last) % N;
            a[m] = st;
            root = insert(root, new Node(st, en, m));
            m++;
        } else {
            long long j;
            cin >> j;
            j = (j + last) % N;
            j--;
            root = erase(root, make_pair(a[j], j));
        }

        last = root->data.st + root->data.en - 1;
        cout << last << endl;
    }
    return 0;
}
