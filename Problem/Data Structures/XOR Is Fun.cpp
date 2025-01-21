//https://toph.co/p/xor-is-fun
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 30;
const int MAX = 5e6 + 5;
const long long M = 1e9 + 7;

long long inv[N];
long long fact[N];
long long factinv[N];

long long binomial(long long n, long long k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}


struct Node {
    int ct;
    int left;
    int right;
    vector<int> v;
    Node() {
        ct = 0;
        left = -1;
        right = -1;
        v.resize(K, 0);
    }
};

Node nodes[MAX];

int a[N];
int root[N];

int idx = 0;

int get_left(int node) {
    if (node == -1) {
        return -1;
    }
    return nodes[node].left;
}

int get_right(int node) {
    if (node == -1) {
        return -1;
    }
    return nodes[node].right;
}

int get_ct(int node) {
    if (node == -1) {
        return 0;
    }
    return nodes[node].ct;
}

pair<long long, long long> query(int node_l, int node_r, int d, int val, int k, long long sum) {
    if (d == -1) {
        int r = node_r, l = node_l;
        for (int j = 0; j < K; j++) {
            int C = val & (1 << j);
            int add = 0;
            if (r != -1) {
                if (C) {
                    add += nodes[r].ct - nodes[r].v[j];
                } else {
                    add += nodes[r].v[j];
                }
            }
            if (l != -1) {
                if (C) {
                    add -= nodes[l].ct - nodes[l].v[j];
                } else {
                    add -= nodes[l].v[j];
                }
            }
            sum += (long long)min(k, add) * (1 << j);
        }
        int ct = get_ct(r) - get_ct(l);
        return make_pair(sum, binomial(ct, k));
    }
    int c = val & (1 << d);
    if (c != 0) {
        int l = get_left(node_l), r = get_left(node_r);

        int ct = get_ct(r) - get_ct(l);
        if (ct < k) {
            for (int j = 0; j < K; j++) {
                int C = val & (1 << j);
                int add = 0;
                if (r != -1) {
                    if (C) {
                        add += nodes[r].ct - nodes[r].v[j];
                    } else {
                        add += nodes[r].v[j];
                    }
                }
                if (l != -1) {
                    if (C) {
                        add -= nodes[l].ct - nodes[l].v[j];
                    } else {
                        add -= nodes[l].v[j];
                    }
                }
                sum += (long long)add * (1 << j);
            }
            return query(get_right(node_l), get_right(node_r), d - 1, val, k - ct, sum);
        } else {
            return query(l, r, d - 1, val, k, sum);
        }
    } else {
        int l = get_right(node_l), r = get_right(node_r);

        int ct = get_ct(r) - get_ct(l);
        if (ct < k) {
            for (int j = 0; j < K; j++) {
                int C = val & (1 << j);
                int add = 0;
                if (r != -1) {
                    if (C) {
                        add += nodes[r].ct - nodes[r].v[j];
                    } else {
                        add += nodes[r].v[j];
                    }
                }
                if (l != -1) {
                    if (C) {
                        add -= nodes[l].ct - nodes[l].v[j];
                    } else {
                        add -= nodes[l].v[j];
                    }
                }
                sum += (long long)add * (1 << j);
            }
            return query(get_left(node_l), get_left(node_r), d - 1, val, k - ct, sum);
        } else {
            return query(l, r, d - 1, val, k, sum);
        }
    }
}

void add(int node_prev, int node, int d, int val) {
    if (d < 0) {
        return;
    }
    int c = val & (1 << d);
    if (c == 0) {
        nodes[node].left = idx;
        nodes[idx++] = Node();
        nodes[nodes[node].left].ct = 1;
        for (int j = 0; j < K; j++) {
            int C = val & (1 << j);
            if (C) {
                nodes[nodes[node].left].v[j] = 1;
            }
        }
        if (node_prev != -1) {
            nodes[nodes[node].left].ct += (nodes[node_prev].left == -1 ? 0 : nodes[nodes[node_prev].left].ct);
            for (int j = 0; j < K; j++) {
                nodes[nodes[node].left].v[j] += (nodes[node_prev].left == -1 ? 0 : nodes[nodes[node_prev].left].v[j]);
            }
            nodes[node].right = nodes[node_prev].right;
        }
        add((node_prev == -1 ? -1 : nodes[node_prev].left), nodes[node].left, d - 1, val);
        return;
    } else {
        nodes[node].right = idx;
        nodes[idx++] = Node();
        nodes[nodes[node].right].ct = 1;
        for (int j = 0; j < K; j++) {
            int C = val & (1 << j);
            if (C) {
                nodes[nodes[node].right].v[j] = 1;
            }
        }
        if (node_prev != -1) {
            nodes[nodes[node].right].ct += (nodes[node_prev].right == -1 ? 0 : nodes[nodes[node_prev].right].ct);
            for (int j = 0; j < K; j++) {
                nodes[nodes[node].right].v[j] += (nodes[node_prev].right == -1 ? 0 : nodes[nodes[node_prev].right].v[j]);
            }
            nodes[node].left = nodes[node_prev].left;
        }
        add((node_prev == -1 ? -1 : nodes[node_prev].right), nodes[node].right, d - 1, val);
        return;
    }
}

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    nodes[idx++] = Node();
    int last = 0;
    for (int i = 0; i < n; i++) {
        root[i] = idx;
        nodes[idx++] = Node();
        add(last, root[i], K - 1, a[i]);
        last = root[i];
    }
    for (int i = 0; i < q; i++) {
        int l, r, k, x;
        cin >> l >> r >> k >> x;
        l--, r--;
        pair<long long, long long> ans = query((l == 0 ? -1 : root[l - 1]), root[r], K - 1, x, k, 0);
        cout << ans.first << " " << ans.second << endl;
    }
    return 0;
}
