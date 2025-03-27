//https://atcoder.jp/contests/abc213/tasks/abc213_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    pair<int, int> key;
    int priority;
    int cnt;
    int ct;
    long long sum;
    Node* left;
    Node* right;

    Node(pair<int, int> key) : key(key), priority(generator()), cnt(1), ct(key.second), sum((long long)key.first * key.second), left(nullptr), right(nullptr) {}
};

int get_cnt(Node* node) {
    return node ? node->cnt : 0;
}

int get_ct(Node* node) {
    return node ? node->ct : 0;
}

long long get_sum(Node* node) {
    return node ? node->sum : 0;
}

void upd_cnt(Node* node) {
    if (node) {
        node->cnt = 1 + get_cnt(node->left) + get_cnt(node->right);
        node->ct = node->key.second + get_ct(node->left) + get_ct(node->right);
        node->sum = (long long)node->key.first * node->key.second + get_sum(node->left) + get_sum(node->right);
    }
}

void split(Node* node, pair<int, int> key, Node*& left, Node*& right) {
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

struct SuffixArray {
	string S; int n;
	vector<int> sa, isa, lcp;
	void init(string _S) {
	     S = _S;
	     n = S.size() + 1;
	     genSa(); genLcp();
    }
	void genSa() {
		sa = vector<int>(n);
		isa = vector<int>(n);
		sa[0] = n - 1;
		iota(1 + sa.begin(), sa.end(), 0);
		sort(1 + sa.begin(), sa.end(), [&](int a, int b) { return S[a] < S[b]; });
		for (int i = 1; i < n; i++) {
            int a = sa[i - 1], b = sa[i];
			isa[b] = i > 1 && S[a] == S[b] ? isa[a] : i;
        }
		for (int len = 1; len < n; len *= 2) {
			vector<int> s(sa), is(isa), pos(n);
			iota(pos.begin(), pos.end(), 0);
			for (int t : s) {
                int T = t - len;
                if (T >= 0) {
                    sa[pos[isa[T]]++] = T;
                }
            }
			for (int i = 1; i < n; i++) {
                int a = sa[i - 1], b = sa[i];
				isa[b] = is[a] == is[b] && is[a + len] == is[b + len] ? isa[a] : i;
            }
		}
	}
	void genLcp() {
		lcp = vector<int>(n - 1); int h = 0;
		for (int b = 0; b < n - 1; b++) {
            int a = sa[isa[b] - 1];
			while (a + h < n - 1 && S[a + h] == S[b + h]) {
                ++h;
			}
			lcp[isa[b] - 1] = h;
			if (h) {
                h--;
			}
        }
	}
};

int main() {
    IOS;
    Node* root = nullptr;
    SuffixArray sa;
    int n;
    cin >> n;
    string s;
    cin >> s;
    sa.init(s);
    vector<long long> ans(n, 0);
    for (int i = n; i > 0; i--) {
        int sz = n - sa.sa[i];
        int l = (i == n ? 0 : sa.lcp[i] + 1);
        Node *a = nullptr;
        Node *b = nullptr;
        split(root, make_pair(l, -1), a, b);
        if (a) {
            ans[sa.sa[i]] += a->sum;
        }
        if (b) {
            ans[sa.sa[i]] += (long long)b->ct * (l - 1);
            root = a;
            root = insert(root, new Node(make_pair(l - 1, b->ct)));
        } else {
            root = a;
        }
        root = insert(root, new Node(make_pair(sz, 1)));
    }

    for (int i = 1; i <= n; i++) {
        int sz = n - sa.sa[i];
        int l = sa.lcp[i - 1] + 1;
        Node *a = nullptr;
        Node *b = nullptr;
        split(root, make_pair(l, -1), a, b);
        if (a) {
            ans[sa.sa[i]] += a->sum;
        }
        if (b) {
            ans[sa.sa[i]] += (long long)b->ct * (l - 1);
            root = a;
            root = insert(root, new Node(make_pair(l - 1, b->ct)));
        } else {
            root = a;
        }
        root = insert(root, new Node(make_pair(sz, 1)));
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] + n - i << endl;
    }

    return 0;
}
