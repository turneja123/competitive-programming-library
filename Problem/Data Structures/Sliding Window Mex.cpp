//https://cses.fi/problemset/task/3219
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int freq[N];
int segtree[4 * N];

int query(int l, int r, int node) {
    if (l == r) {
        return l;
    }
    int mid = (l + r) / 2;
    if (segtree[2 * node + 1] < mid - l + 1) {
        return query(l, mid, 2 * node + 1);
    } else {
        return query(mid + 1, r, 2 * node + 2);
    }
}

void update(int l, int r, int node, int ind, int val) {

    if (l == r) {
        segtree[node] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        update(l, mid, 2 * node + 1, ind, val);
    } else {
        update(mid + 1, r, 2 * node + 2, ind, val);
    }
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] = min(a[i], 200002);
    }
    for (int i = 0; i < k; i++) {
        freq[a[i]]++;
        if (freq[a[i]] == 1) {
            update(0, n - 1, 0, a[i], 1);
        }
    }
    cout << query(0, n - 1, 0) << " ";
    for (int i = k; i < n; i++) {
        freq[a[i - k]]--;
        if (freq[a[i - k]] == 0) {
            update(0, n - 1, 0, a[i - k], 0);
        }

        freq[a[i]]++;
        if (freq[a[i]] == 1) {
            update(0, n - 1, 0, a[i], 1);
        }
        cout << query(0, n - 1, 0) << " ";
    }
    return 0;
}
