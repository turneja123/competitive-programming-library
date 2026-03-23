//https://evaluator.hsin.hr/events/coci26_6/tasks/HONI252668ucionica/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;

int a[N][N];
int cur[N];
int lim[N];


struct Node {
    int sum;
    int lazy;
    Node() {
        lazy = 0;
    }
    Node(int x) {
        sum = x;
        lazy = 0;
    }
};

Node segtree[4 * N];

void apply(int node, int l, int r) {
    segtree[node].sum += segtree[node].lazy;
    if (l != r) {
        segtree[2 * node + 1].lazy += segtree[node].lazy;
        segtree[2 * node + 2].lazy += segtree[node].lazy;
    }
    segtree[node].lazy = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, ll add) {
    if (l >= lq && r <= rq) {
        segtree[node].lazy += add;
        apply(node, l, r);
        return;
    }
    apply(node, l, r);
    if (l > rq || lq > r) {
        return;
    }
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
    segtree[node].sum = min(segtree[2 * node + 1].sum, segtree[2 * node + 2].sum);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(lim[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node].lazy = 0;
    segtree[node].sum = min(segtree[2 * node + 1].sum, segtree[2 * node + 2].sum);
}

int main() {
    IOS;
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> our(k);
    for (int i = 0; i < k; i++) {
        cin >> our[i];
        lim[i] = k - i - 1;
    }
    sort(our.begin(), our.end());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        build(0, k - 1, 0);
        int z = 0;
        for (int j = 0; j < m; j++) {
            if (a[i][j] != 0) {
                z++;
            }
            int ord = upper_bound(our.begin(), our.end(), cur[j]) - our.begin() - 1;
            if (ord >= 0) {
                incUpdate(0, 0, k - 1, 0, ord, -1);
            }

            if (j >= k) {
                if (a[i][j - k] != 0) {
                    z--;
                }
                int ord = upper_bound(our.begin(), our.end(), cur[j - k]) - our.begin() - 1;
                if (ord >= 0) {
                    incUpdate(0, 0, k - 1, 0, ord, 1);
                }
            }
            apply(0, 0, k - 1);
            if (j >= k - 1 && segtree[0].sum >= 0 && z == 0) {
                ans++;
            }
        }
        for (int j = 0; j < m; j++) {
            cur[j] = max(cur[j], a[i][j]);
        }
    }
    cout << ans;


    return 0;
}

