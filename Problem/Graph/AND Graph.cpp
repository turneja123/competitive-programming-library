//https://codeforces.com/contest/986/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1 << 22;

int parent[N];
int a[N];
int sz[N];
int val[N];
int sos[N];

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

void dsu_unite(int a, int b) {
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    val[a] += val[b];
    parent[b] = a;
}

void dfs_unite(int j, int mask, int n) {
    if (!sos[j]) {
        return;
    }
    if (j != mask) {
        int a = dsu_find(j), b = dsu_find(mask);
        if (a == b) {
            return;
        }
        dsu_unite(a, b);
    }
    for (int i = 0; i < n; i++) {
        int c = (1 << i) & j;
        if (c) {
            dfs_unite(j ^ (1 << i), mask, n);
        }
    }
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> a[i];
        val[a[i]] = 1;
        sos[a[i]] = 1;
    }


    for (int i = 0; i < 1 << n; i++) {
        parent[i] = i;
        sz[i] = 1;
        for (int j = 0; j < n; j++) {
            int c = i & (1 << j);
            if (c) {
                sos[i] |= sos[i ^ (1 << j)];
            }
        }
    }
    for (int i = 0; i < m; i++) {
        int cmpl = ((1 << n) - 1) ^ a[i];
        dfs_unite(cmpl, cmpl, n);
        int x = dsu_find(a[i]), y = dsu_find(cmpl);
        if (x != y) {
            dsu_unite(x, y);
        }
    }
    int ans = 0;
    for (int i = 0; i < 1 << n; i++) {
        int x = dsu_find(i);
        if (x == i && val[x] > 0) {
            ans++;
        }
    }
    cout << ans;

    return 0;
}
