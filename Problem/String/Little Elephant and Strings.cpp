//https://codeforces.com/problemset/problem/204/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 20;

int table[K][N];
int val[N];
long long ans[N];
string s[N];


const int MAX = 1e7;

struct Node {
    int val;
    int left;
    int right;
    Node() : val(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

int root[N];
int a[N];
int b[N];
int last[N];

void build(int node, int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    nodes[node].left = idx;
    nodes[idx++] = Node();
    nodes[node].right = idx;
    nodes[idx++] = Node();
    build(nodes[node].left, l, mid);
    build(nodes[node].right, mid + 1, r);
    return;
}

void update(int node_prev, int node, int l, int r, int ind) {
    if (l == r) {
        nodes[node].val = nodes[node_prev].val + 1;
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        nodes[node].left = idx;
        nodes[idx++] = Node();
        nodes[node].right = nodes[node_prev].right;
        update(nodes[node_prev].left, nodes[node].left, l, mid, ind);
    } else {
        nodes[node].right = idx;
        nodes[idx++] = Node();
        nodes[node].left = nodes[node_prev].left;
        update(nodes[node_prev].right, nodes[node].right, mid + 1, r, ind);
    }
    nodes[node].val = nodes[nodes[node].left].val + nodes[nodes[node].right].val;
    return;
}

int query(int node_l, int node_r, int l, int r, int lq, int rq) {
    if (lq > r || rq < l) {
        return 0;
    }
    if (lq <= l && rq >= r) {
        return nodes[node_r].val - nodes[node_l].val;
    }
    int mid = (l + r) / 2;
    return query(nodes[node_l].left, nodes[node_r].left, l, mid, lq, rq) + query(nodes[node_l].right, nodes[node_r].right, mid + 1, r, lq, rq);
}


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
			while (a + h < n - 1 && S[a + h] == S[b + h] && S[a + h] != '~') {
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
    SuffixArray sa;
    string S = "";
    int m, k;
    cin >> m >> k;
    vector<int> flg, sz;
    for (int i = 0; i < m; i++) {
        cin >> s[i];
        int n = s[i].size();
        for (int j = 0; j < n; j++) {
            flg.push_back(i);
            sz.push_back(n - j);
        }
        S += s[i];
        S += '~';
        flg.push_back(m);
        sz.push_back(0);
    }
    sa.init(S);
    int n = S.size();
    a[0] = 0;
    for (int i = 1; i <= n; i++) {
        a[i] = flg[sa.sa[i]];
    }
    build(n, sa.lcp);

    for (int i = 0; i <= m; i++) {
        last[i] = -1;
    }
    for (int i = 0; i <= n; i++) {
        b[i] = last[a[i]];
        last[a[i]] = i;
    }
    root[0] = idx;
    nodes[idx++] = Node();
    build(root[0], 0, n);
    for (int i = 0; i <= n; i++) {
        root[i + 1] = idx;
        nodes[idx++] = Node();
        update(root[i], root[i + 1], 0, n, b[i] + 1);
    }



    for (int i = 1; i <= n; i++) {
        int l = 1, r = sz[sa.sa[i]], ct = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            int lf = i, rt = n, R = i;
            while (lf <= rt) {
                int spl = (lf + rt) / 2;
                int s = (i == spl ? sz[sa.sa[i]] : query(i, spl - 1));
                if (s >= mid) {
                    lf = spl + 1;
                    R = spl;
                } else {
                    rt = spl - 1;
                }
            }
            lf = 0, rt = i; int L = i;
            while (lf <= rt) {
                int spl = (lf + rt) / 2;
                int s = (i == spl ? sz[sa.sa[i]] : query(spl, i - 1));
                if (s >= mid) {
                    rt = spl - 1;
                    L = spl;
                } else {
                    lf = spl + 1;
                }
            }
            int z = query(root[L], root[R + 1], 0, n, 0, L);
            if (z >= k) {
                ct = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        ans[flg[sa.sa[i]]] += ct;
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
