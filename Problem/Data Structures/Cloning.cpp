//https://www.codechef.com/problems/CLONEME
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 7;
const long long P = 26, Q = 53;

const int N = 1e5 + 5;
const int MAX = 5e6 + 5;

struct Node {
    int val;
    int left;
    int right;
    long long p;
    long long q;
    Node() : val(0), left(-1), right(-1), p(1), q(1) {}
};

Node nodes[MAX];
int idx = 0;

int root[N];
int a[N];
int ans;
int freq;
int aq, bq, cq, dq;
int n, q;

pair<int, int> adjust;

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
        nodes[node].p = nodes[node_prev].p * (P + ind) % M;
        nodes[node].q = nodes[node_prev].q * (Q + ind) % M;
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
    nodes[node].p = nodes[nodes[node].left].p * nodes[nodes[node].right].p % M;
    nodes[node].q = nodes[nodes[node].left].q * nodes[nodes[node].right].q % M;
    return;
}


void kth(int node_l, int node_r, int l, int r, int k) {
    if (l == r) {
        ans = l;
        return;
    }
    int mid = (l + r) / 2;
    int ct = nodes[nodes[node_r].left].val - nodes[nodes[node_l].left].val;
    if (ct > k) {
        kth(nodes[node_l].left, nodes[node_r].left, l, mid, k);
    } else {
        kth(nodes[node_l].right, nodes[node_r].right, mid + 1, r, k - ct);
    }
    return;
}

void query(int node_l_a, int node_r_a, int node_l_b, int node_r_b, int l, int r) {
    if (l == r) {
        int ct_a = nodes[node_r_a].val - nodes[node_l_a].val;
        int ct_b = nodes[node_r_b].val - nodes[node_l_b].val;
        if (ct_a == ct_b) {
            adjust = make_pair(-1, -1);
        } else if (abs(ct_a - ct_b) > 1) {
            adjust = make_pair(-2, -2);
        } else if (ct_a > ct_b) {
            adjust.first = l;
            freq += ct_b;
            if (freq == n) {
                adjust.second = -1;
            } else {
                kth(root[cq - 1], root[dq], 0, N - 1, freq);
                adjust.second = ans;
            }
        } else {
            adjust.second = l;
            freq += ct_a;
            if (freq == n) {
                adjust.first = -1;
            } else {
                kth(root[aq - 1], root[bq], 0, N - 1, freq);
                adjust.first = ans;
            }
        }
        return;
    }
    int mid = (l + r) / 2;
    long long p_a = nodes[nodes[node_r_a].left].p * modInverse(nodes[nodes[node_l_a].left].p) % M;
    long long q_a = nodes[nodes[node_r_a].left].q * modInverse(nodes[nodes[node_l_a].left].q) % M;

    long long p_b = nodes[nodes[node_r_b].left].p * modInverse(nodes[nodes[node_l_b].left].p) % M;
    long long q_b = nodes[nodes[node_r_b].left].q * modInverse(nodes[nodes[node_l_b].left].q) % M;

    if (!(p_a == p_b && q_a == q_b)) {
        query(nodes[node_l_a].left, nodes[node_r_a].left, nodes[node_l_b].left, nodes[node_r_b].left, l, mid);
    } else {
        freq += nodes[nodes[node_r_a].left].val - nodes[nodes[node_l_a].left].val;
        query(nodes[node_l_a].right, nodes[node_r_a].right, nodes[node_l_b].right, nodes[node_r_b].right, mid + 1, r);
    }
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        idx = 0;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        root[0] = idx;
        nodes[idx++] = Node();
        build(root[0], 0, N - 1);
        for (int i = 0; i < n; i++) {
            root[i + 1] = idx;
            nodes[idx++] = Node();
            update(root[i], root[i + 1], 0, N - 1, a[i]);
        }
        for (int i = 0; i < q; i++) {
            cin >> aq >> bq >> cq >> dq;
            freq = 0;
            query(root[aq - 1], root[bq], root[cq - 1], root[dq], 0, N - 1);
            if (adjust.first == -1 || adjust.second == -1) {
                cout << "YES" << endl;
            } else if (adjust.first == -2) {
                cout << "NO" << endl;
            } else {
                long long p_a = nodes[root[bq]].p * modInverse(nodes[root[aq - 1]].p) % M * modInverse(P + adjust.first) % M;
                long long q_a = nodes[root[bq]].q * modInverse(nodes[root[aq - 1]].q) % M * modInverse(Q + adjust.first) % M;

                long long p_b = nodes[root[dq]].p * modInverse(nodes[root[cq - 1]].p) % M * modInverse(P + adjust.second) % M;
                long long q_b = nodes[root[dq]].q * modInverse(nodes[root[cq - 1]].q) % M * modInverse(Q + adjust.second) % M;
                if (!(p_a == p_b && q_a == q_b)) {
                    cout << "NO" << endl;
                } else {
                    cout << "YES" << endl;
                }
            }
        }
    }
    return 0;
}
