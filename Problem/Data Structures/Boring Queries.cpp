//https://codeforces.com/contest/1422/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int SQ = 90;
const int MAX = 1e7 + 5;
const long long M = 1e9 + 7;

int spf[N];
bool is_prime[N];

int a[N];

int factors[SQ][N];
int segtree[SQ][2 * N];
long long pw[SQ][32];
int cur[SQ];

vector<pair<int, int>> segtree_v[2 * N];

struct Node {
    long long prod;
    int left;
    int right;
    Node() : left(-1), right(-1), prod(1) {}
};

Node nodes[MAX];
int idx = 0;

int root[N];

int pos[N];
long long val[N];
int last[N];
int prime_ct = 0;

long long modInverse(long long a) {
    long long res = 1;
    long long y = M - 2;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

void sieve(int n){
    for (int i = 1; i < n; i++) {
        spf[i] = i;
        is_prime[i] = true;
    }
    is_prime[1] = false;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            pos[i] = prime_ct;
            val[prime_ct] = i;
            prime_ct++;
            for (int j = 2 * i; j < n; j += i) {
                is_prime[j] = false;
                spf[j] = min(spf[j], i);
            }
        }
    }
}

void build_heavy(int node, int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    nodes[node].left = idx;
    nodes[idx++] = Node();
    nodes[node].right = idx;
    nodes[idx++] = Node();
    build_heavy(nodes[node].left, l, mid);
    build_heavy(nodes[node].right, mid + 1, r);
    return;
}

void update_heavy(int node_prev, int node, int l, int r, int ind, long long x) {
    if (l == r) {
        nodes[node].prod = nodes[node_prev].prod * x % M;
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        nodes[node].left = idx;
        nodes[idx++] = Node();
        nodes[node].right = nodes[node_prev].right;
        update_heavy(nodes[node_prev].left, nodes[node].left, l, mid, ind, x);
    } else {
        nodes[node].right = idx;
        nodes[idx++] = Node();
        nodes[node].left = nodes[node_prev].left;
        update_heavy(nodes[node_prev].right, nodes[node].right, mid + 1, r, ind, x);
    }
    nodes[node].prod = nodes[nodes[node].left].prod * nodes[nodes[node].right].prod % M;
}

long long query_heavy(int node_l, int node_r, int l, int r, int lq, int rq) {
    if (lq > r || rq < l) {
        return 1;
    }
    if (lq <= l && rq >= r) {
        return nodes[node_r].prod * modInverse(nodes[node_l].prod) % M;
    }
    int mid = (l + r) / 2;
    return query_heavy(nodes[node_l].left, nodes[node_r].left, l, mid, lq, rq) * query_heavy(nodes[node_l].right, nodes[node_r].right, mid + 1, r, lq, rq) % M;
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        for (int i = 0; i < SQ; i++) {
            segtree[i][node] = factors[i][l];
            if (segtree[i][node] > 0) {
                segtree_v[node].push_back(make_pair(i, segtree[i][node]));
            }
        }
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    for (int i = 0; i < SQ; i++) {
        segtree[i][node] = max(segtree[i][2 * node + 1], segtree[i][2 * node + 2]);
        if (segtree[i][node] > 0) {
            segtree_v[node].push_back(make_pair(i, segtree[i][node]));
        }
    }
}

void query(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        for (int i = 0; i < segtree_v[node].size(); i++) {
            int p = segtree_v[node][i].first, e = segtree_v[node][i].second;
            cur[p] = max(cur[p], e);
        }
        return;
    }

    if (l > rq || r < lq) {
        return;
    }

    int mid = (l + r) / 2;
    query(l, mid, lq, rq, 2 * node + 1);
    query(mid + 1, r, lq, rq, 2 * node + 2);
}

int main() {
	IOS;
	sieve(N);
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    root[0] = idx;
    nodes[idx++] = Node();
    build_heavy(root[0], 0, n - 1);
    for (int i = 0; i < N; i++) {
        last[i] = -1;
    }
    for (int i = 0; i < SQ; i++) {
        pw[i][0] = 1;
        for (int j = 1; j < 32; j++) {
            pw[i][j] = pw[i][j - 1] * val[i] % M;
        }
    }
    for (int i = 0; i < n; i++) {
        root[i + 1] = idx;
        nodes[idx++] = Node();
        int x = a[i]; bool h = false;
        while (x > 1) {
            int p = spf[x], e = 0;
            while (x % p == 0) {
                x /= p;
                e++;
            }
            int ind = pos[p];
            if (ind >= SQ) {
                update_heavy(root[i], root[i + 1], 0, n - 1, last[ind] + 1, p);
                last[ind] = i;
                h = true;
            } else {
                factors[ind][i] = e;
            }
        }
        if (!h) {
            nodes[root[i + 1]].left = nodes[root[i]].left;
            nodes[root[i + 1]].right = nodes[root[i]].right;
        }
    }
    build(0, n - 1, 0);
    cin >> q;
    long long prev_ans = 0;
    for (int i = 0; i < q; i++) {
        long long l, r;
        cin >> l >> r;
        l = (l + prev_ans) % n, r = (r + prev_ans) % n;
        if (l > r) {
            swap(l, r);
        }
        long long ans = query_heavy(root[l], root[r + 1], 0, n - 1, 0, l);
        query(0, n - 1, l, r, 0);
        for (int j = 0; j < SQ; j++) {
            if (cur[j] > 0) {
                ans = ans * pw[j][cur[j]] % M;
                cur[j] = 0;
            }
        }
        cout << ans << endl;
        prev_ans = ans;
    }

	return 0;
}
