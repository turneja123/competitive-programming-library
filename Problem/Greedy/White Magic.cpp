//https://codeforces.com/contest/2067/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;

int segtree[4 * N];

int query(int l, int r, int node) {
    if (l == r) {
        return l;
    }
    int mid = (l + r) / 2;
    if (segtree[2 * node + 1] < mid - l + 1) {
        return query(l, mid, 2 * node + 1);
    }
    return query(mid + 1, r, 2 * node + 2);
}

void update(int l, int r, int ind, int node) {
    if (l == r) {
        segtree[node] = 0;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, 2 * node + 2);
    }
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
}


void build(int l, int r, int node, vector<int> &freq) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = min(1, freq[l]);
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1, freq);
    build(mid + 1, r, 2 * node + 2, freq);
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int z = 0;
        vector<int> a;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            if (x) {
                a.push_back(x);
            } else if (!z) {
                z = 1;
                a.push_back(x);
            }
        }
        n = a.size();
        if (!z) {
            cout << n << endl;
            continue;
        }
        int ans = n - 1;
        int can = 1;
        vector<int> freq(n, 0);
        for (int i = 0; i < n; i++) {
            if (a[i] < n) {
                freq[a[i]]++;
            }
        }
        build(0, n - 1, 0, freq);
        int mn = a[0];
        for (int i = 0; i < n - 1; i++) {
            if (a[i] < n) {
                freq[a[i]]--;
                mn = min(mn, a[i]);
                if (freq[a[i]] == 0) {
                    update(0, n - 1, a[i], 0);
                }
            }
            int x = query(0, n - 1, 0);
            if (mn < x) {
                can = 0;
            }
        }
        cout << ans + can << endl;
    }

    return 0;
}
