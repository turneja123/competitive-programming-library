//https://codeforces.com/contest/1253/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int parent[N];
int sz[N];
int mx[N];

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

int dsu_unite(int a, int b) {
    a = dsu_find(a);
    b = dsu_find(b);
    if (a == b) {
        return 0;
    }

    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    parent[b] = a;
    return 1;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
        mx[i] = i;
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        if (l > r) {
            swap(l, r);
        }
        mx[l] = max(mx[l], r);
        dsu_unite(l, r);
    }
    int j = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        j = max(j, mx[i]);
        ans += dsu_unite(i, j);
    }
    cout << ans;



    return 0;
}
