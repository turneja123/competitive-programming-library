//https://atcoder.jp/contests/abc282/tasks/abc282_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;
int M;

int a[N];
int parent[N];
int sz[N];

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

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
    parent[b] = a;
}

int main() {
    IOS;
    int n;
    cin >> n >> M;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        parent[i] = i;
        sz[i] = 1;
    }
    vector<tuple<ll, int, int>> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edges.push_back(make_tuple((modPow(a[i], a[j]) + modPow(a[j], a[i])) % M, i, j));
        }
    }
    sort(edges.begin(), edges.end());
    reverse(edges.begin(), edges.end());
    ll ans = 0;
    for (auto [wt, u, v] : edges) {
        u = dsu_find(u), v = dsu_find(v);
        if (u != v) {
            ans += wt;
            dsu_unite(u, v);
        }
    }
    cout << ans;
    return 0;
}
