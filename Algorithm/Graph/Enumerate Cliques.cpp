//https://judge.yosupo.jp/problem/enumerate_cliques
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;
const long long M = 998244353;

bitset<N> adj[N];
bitset<N> cur;

long long a[N];
long long ans = 0;

void calc(int i, int n, long long prod) {
    if (i == n) {
        ans = (ans + prod) % M;
        return ;
    }
    if ((cur & adj[i]) == cur) {
        cur.set(i);
        calc(i + 1, n, prod * a[i] % M);
        cur.reset(i);
    }
    calc(i + 1, n, prod);
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].set(v);
        adj[v].set(u);
    }
    calc(0, n, 1);
    cout << (ans - 1 + M) % M;
    return 0;
}
