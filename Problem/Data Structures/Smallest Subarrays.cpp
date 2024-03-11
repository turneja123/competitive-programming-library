//solution for https://www.hackerearth.com/challenges/competitive/april-circuits-21/algorithm/smallest-subarray-2-d6530e0b/
#pragma GCC target ("avx2")
#pragma GCC optimization ("Ofast")
#pragma GCC optimization ("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int INF = 1e9;

int a[N];
int b[N];
vector<int> segtree[4 * N];

vector<int> treeMerge(vector<int> &v1, vector<int>& v2) {
    vector<int> v;
    int i = 0, j = 0;
    while (i < v1.size() && j < v2.size()) {
        if (v1[i] <= v2[j]) {
            v.push_back(v1[i]);
            i++;
        }
        else {
            v.push_back(v2[j]);
            j++;
        }
    }
    for (int k = i; k < v1.size(); k++)
        v.push_back(v1[k]);
    for (int k = j; k < v2.size(); k++)
        v.push_back(v2[k]);
    return v;
}

int query(int l, int r, int lq, int rq, int node, int k) {
    if (l > rq || r < lq) {
        return 0;
    }

    if (lq <= l && rq >= r) {
        return segtree[node].size() -
               (lower_bound(segtree[node].begin(), segtree[node].end(), k) - segtree[node].begin());
    }

    int mid = (l + r) / 2;
    return query(l, mid, lq, rq, 2 * node + 1, k) +
           query(mid + 1, r, lq, rq, 2 * node + 2, k);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node].push_back(a[l]);
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = treeMerge(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int bin(int l, int r, int val, int target, int n) {
    int i = l;
    int mn = INF;
    while (l <= r) {
        int mid = (l + r) / 2;
        int ct = query(0, n - 1, i, mid, 0, val);
        if (ct >= target) {
            mn = min(mn, mid);
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return mn;
}

int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    build(0, n - 1, 0);

    for (int i = 0; i < n; i++) {
        int s = bin(i, n - 1, a[i], b[i], n);
        if (s == INF) {
            cout << -1 << " ";
        } else {
            cout << s - i + 1 << " ";
        }
    }
    return 0;
}
