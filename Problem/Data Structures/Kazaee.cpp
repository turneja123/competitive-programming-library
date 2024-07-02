//https://codeforces.com/contest/1746/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int K = 30;

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int a[N];
bool st[K][2 * N];
gp_hash_table<int, int, custom_hash> pos;

int segtree[K][4 * N];

void gen_sets(int n) {
    for (int k = 0; k < K; k++) {
        for (int i = 0; i < n; i++) {
            if (generator() % 2) {
                st[k][i] = true;
            }
        }
    }
}

void query(int l, int r, int lq, int rq, int node, vector<int> &qans) {
    if (lq <= l && rq >= r) {
        for (int k = 0; k < K; k++) {
            qans[k] += segtree[k][node];
        }
        return;
    }

    if (l > rq || r < lq) {
        return;
    }

    int mid = (l + r) / 2;
    query(l, mid, lq, rq, 2 * node + 1, qans);
    query(mid + 1, r, lq, rq, 2 * node + 2, qans);
}

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        for (int k = 0; k < K; k++) {
            if (st[k][val]) {
                segtree[k][node] = 1;
            } else {
                segtree[k][node] = 0;
            }
        }
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
    for (int k = 0; k < K; k++) {
        segtree[k][node] = segtree[k][2 * node + 1] + segtree[k][2 * node + 2];
    }
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        for (int k = 0; k < K; k++) {
            if (st[k][a[l]]) {
                segtree[k][node] = 1;
            } else {
                segtree[k][node] = 0;
            }
        }
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    for (int k = 0; k < K; k++) {
        segtree[k][node] = segtree[k][2 * node + 1] + segtree[k][2 * node + 2];
    }
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (pos.find(a[i]) == pos.end()) {
            pos[a[i]] = pos.size();
        }
        a[i] = pos[a[i]];
    }
    gen_sets(2 * N);
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int j, x;
            cin >> j >> x;
            j--;
            if (pos.find(x) == pos.end()) {
                pos[x] = pos.size();
            }
            x = pos[x];
            update(0, n - 1, j, x, 0);
        } else {
            vector<int> qans(K, 0);
            int l, r, m;
            cin >> l >> r >> m;
            l--, r--;
            query(0, n - 1, l, r, 0, qans);
            string ans = "YES";
            for (int k = 0; k < K; k++) {
                if (qans[k] % m != 0) {
                    ans = "NO";
                    break;
                }
            }
            cout << ans << endl;
        }
    }

    return 0;
}
