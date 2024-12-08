//https://codeforces.com/problemset/problem/1857/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 998244353;

int parent[N];
int sz[N];

tuple<int, int, int> edges[N];

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

void dsu_unite(int a, int b) {
    a = dsu_find(a);
    b = dsu_find(b);
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    parent[b] = a;
}

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

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n; long long s;
        cin >> n >> s;
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            sz[i] = 1;
        }
        for (int i = 0; i < n - 1; i++) {
            int u, v, wt;
            cin >> u >> v >> wt;
            u--, v--;
            edges[i] = make_tuple(wt, u, v);
        }
        sort(edges, edges + n - 1);
        long long ans = 1;
        for (int i = 0; i < n - 1; i++) {
            auto [wt, u, v] = edges[i];
            int p1 = dsu_find(u);
            int p2 = dsu_find(v);

            ans = ans * modPow(s - wt + 1, (long long)sz[p1] * sz[p2] - 1) % M;
            dsu_unite(p1, p2);
        }
        cout << ans << endl;
    }
    return 0;
}
