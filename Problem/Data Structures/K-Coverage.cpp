//https://qoj.ac/contest/2567/problem/14716
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1500000;
const int K = 21;
const int INF = 1e9;

int pref[N][3];
int diff[N];
int a[N];
int gain[N];

int table[K][N];

void build(int n) {
    for (int i = 1; i <= n; i++) {
        table[0][i] = gain[i - 1];
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            table[k][i] = max(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
        }
    }
    return;
}

int query(int l, int r) {
    if (l > r) {
        return -INF;
    }
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    return max(table[k][l], table[k][r - (1 << k) + 1]);
}

int sum(int l, int r, int j) {
    return pref[r][j] - (l == 0 ? 0 : pref[l - 1][j]);
}

int id1[N];
int id2[N];

struct Node {
    int sum1;
    int suf1;
    int sum2;
    int pref2;
    bool sentinel;

    Node()  {
        sentinel = 1;

    }
    Node(int x, int y) {
        sentinel = 0;
        sum1 = x;
        suf1 = x;
        sum2 = y;
        pref2 = y;
    }
};

Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    if (left.sentinel) {
        return right;
    }
    if (right.sentinel) {
        return left;
    }
    node.sentinel = 0;
    node.sum1 = left.sum1 + right.sum1;
    node.sum2 = left.sum2 + right.sum2;
    node.suf1 = max(right.suf1, left.suf1 + right.sum1);
    node.pref2 = max(left.pref2, left.sum2 + right.pref2);

    node.sum1 = max(node.sum1, -INF);
    node.sum2 = max(node.sum2, -INF);

    return node;
}

Node query_seg(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        Node sentinel = Node();
        return sentinel;
    }

    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    int mid = (l + r) / 2;
    return combine(query_seg(l, mid, lq, rq, 2 * node + 1), query_seg(mid + 1, r, lq, rq, 2 * node + 2));
}

void build_seg(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(id1[l], id2[l]);
        return;
    }

    int mid = (l + r) / 2;
    build_seg(l, mid, 2 * node + 1);
    build_seg(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, len, k;
        cin >> n >> len >> k;
        int m = n;
        vector<pair<int, int>> ivals;
        for (int i = 0; i < m; i++) {
            int l;
            cin >> l;
            int r = l + len - 1;
            diff[l]++;
            diff[r + 1]--;
            n = max(n, 2 * r + 2 + len);
            ivals.push_back({l, r});
        }
        int s = 0, ans = 0, best = 0;
        for (int i = 0; i < n; i++) {
            s += diff[i];
            a[i] = s;
            if (s == k) {
                ans++;
            }
        }
        for (int i = 0; i < n; i++) {
            if (a[i] == k - 1) {
                pref[i][0]++;
            } else if (a[i] == k) {
                pref[i][1]++;
            } else if (a[i] == k + 1) {
                pref[i][2]++;
            }
            if (i != 0) {
                pref[i][0] += pref[i - 1][0];
                pref[i][1] += pref[i - 1][1];
                pref[i][2] += pref[i - 1][2];
            }
            if (i - len + 1 >= 0) {
                gain[i] = sum(i - len + 1, i, 0) - sum(i - len + 1, i, 1);
            } else {
                gain[i] = -INF;
            }
            if (i - len < 0) {
                id1[i] = -INF;
            } else {
                id1[i] = 0;
                if (a[i] == k) {
                    id1[i]--;
                } else if (a[i] == k + 1) {
                    id1[i]++;
                }
                if (a[i - len] == k) {
                    id1[i]--;
                } else if (a[i - len] == k - 1) {
                    id1[i]++;
                }
            }
            if (i + len >= n) {
                id2[i] = -INF;
            } else {
                id2[i] = 0;
                if (a[i] == k) {
                    id2[i]--;
                } else if (a[i] == k + 1) {
                    id2[i]++;
                }
                if (a[i + len] == k) {
                    id2[i]--;
                } else if (a[i + len] == k - 1) {
                    id2[i]++;
                }
            }
        }
        build(n);
        build_seg(0, n - 1, 0);
        best = ans;
        for (auto [l, r] : ivals) {
            int rem = sum(l, r, 2) - sum(l, r, 1);
            if (l != 0) {
                ans = max(ans, best + query(0, l - 1) + rem);
            }
            ans = max(ans, best + query(r + len, n - 1) + rem);

            if (l != 0 && len > 1) {
                Node mov_left = query_seg(0, n - 1, l + 1, r, 0);
                ans = max(ans, best + mov_left.suf1);
            }
            if (len > 1) {
                Node mov_right = query_seg(0, n - 1, l, r - 1, 0);
                ans = max(ans, best + mov_right.pref2);
            }
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            pref[i][0] = 0, pref[i][1] = 0, pref[i][2] = 0;
            gain[i] = 0;
            diff[i] = 0;
        }

    }
    return 0;
}
