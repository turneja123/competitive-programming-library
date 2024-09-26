//https://www.spoj.com/problems/ORDERSET/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int ind, exists, cnt;
mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    int key;
    int priority;
    int cnt;
    Node* left;
    Node* right;

    Node(int key) : key(key), priority(generator()), cnt(1), left(nullptr), right(nullptr) {}
};

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

void upd_cnt(Node* node) {
    if (node) {
        node->cnt = 1 + get_cnt(node->left) + get_cnt(node->right);
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

void kth(Node* root, int k) {
    if (!root) {
        return;
    }
    int x = k - get_cnt(root->left);
    if (x <= 0) {
        kth(root->left, k);
    } else if (x == 1) {
        ind = root->key;
        return;
    } else {
        kth(root->right, x - 1);
    }
}

void find(Node* root, int key) {
    if (!root) {
        return;
    }
    if (root->key == key) {
        exists = 1;
        cnt += get_cnt(root->left);
        return;
    }
    if (root->key > key) {
        find(root->left, key);
    } else {
        cnt += 1 + get_cnt(root->left);
        find(root->right, key);
    }

}

int main(){
    IOS;
    Node* root = nullptr;
    int n;
    cin >> n;
    while (n--) {
        char c; int n;
        cin >> c >> n;
        if (c == 'I') {
            exists = 0, cnt = 0;
            find(root, n);
            if (!exists) {
                root = insert(root, new Node(n));
            }
        } else if (c == 'D') {
            root = erase(root, n);
        } else if (c == 'K') {
            if (n > get_cnt(root)) {
                cout << "invalid" << endl;
            } else {
                ind = -1;
                kth(root, n);
                cout << ind << endl;
            }
        } else {
            exists = 0, cnt = 0;
            find(root, n);
            cout << cnt << endl;
        }
    }
    return 0;
}
