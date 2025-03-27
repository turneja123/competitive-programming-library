//https://codeforces.com/contest/1073/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

const int N = 2e5 + 5;
const int K = 20;

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

int table[K][N];
int freq[N];

void build(int n, vector<int> &a) {
    for (int i = 1; i <= n; i++) {
        table[0][i] = a[i - 1];
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            table[k][i] = min(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
        }
    }
    return;
}

int query(int l, int r) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    return min(table[k][l], table[k][r - (1 << k) + 1]);
}

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


long long solve(vector<pair<int, int>> &all, int n, SuffixArray &sa) {
    long long ans = 0;
    Node* root = nullptr;
    sort(all.begin(), all.end());
    int last = -1;
    for (int i = all.size() - 1; i >= 0; i--) {
        auto [j, f] = all[i];
        if (f == -1) {
            if (last != -1) {
                int d = query(j, last - 1);
                Node* l = nullptr;
                Node* r = nullptr;
                split(root, make_pair(d + 1, -1), l, r);
                root = l;
                if (r) {
                    root = insert(root, new Node(make_pair(d, r->ct)));
                }
            }
            root = insert(root, new Node(make_pair(n - sa.sa[j], 1)));
            last = j;
        } else {
            if (last == -1) {
                continue;
            }
            int d = query(j, last - 1);
            Node* l = nullptr;
            Node* r = nullptr;
            split(root, make_pair(d + 1, -1), l, r);
            if (l) {
                ans += l->sum;
            }
            if (r) {
                ans += (long long)d * r->ct;
            }
            root = merge(l, r);
        }
    }
    return ans;
}


int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    SuffixArray sa;
    string s;
    cin >> s;
    sa.init(s);
    build(n, sa.lcp);
    for (int t = 0; t < q; t++) {

        int N, M;
        cin >> N >> M;
        long long ans = 0;
        vector<int> a(N), b(M);
        vector<pair<int, int>> all;
        for (int j = 0; j < N; j++) {
            cin >> a[j];
            a[j]--;
            all.push_back(make_pair(sa.isa[a[j]], 0));
            freq[a[j]]++;
        }
        for (int j = 0; j < M; j++) {
            cin >> b[j];
            b[j]--;
            ans += (long long)freq[b[j]] * (n - b[j]);
            all.push_back(make_pair(sa.isa[b[j]], -1));
        }
        ans += solve(all, n, sa);
        for (int i = 0; i < all.size(); i++) {
            if (all[i].second == 0) {
                all[i].second = -1;
            } else {
                all[i].second = 0;
            }
        }
        ans += solve(all, n, sa);
        for (int j = 0; j < N; j++) {
            freq[a[j]]--;
        }
        cout << ans << endl;
    }
    return 0;
}
