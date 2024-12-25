//https://atcoder.jp/contests/abc314/tasks/abc314_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 998244353;

set<int> st[N];
long long ans[N];
long long group[N];
int parent[N];

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
    int n = st[a].size(), m = st[b].size();
    if (n > m) {
        swap(a, b);
        swap(n, m);
    }

    group[a] = (group[a] + (long long)n * modPow(n + m, M - 2)) % M;
    group[b] = (group[b] + (long long)m * modPow(n + m, M - 2)) % M;
    for (int x : st[a]) {
        ans[x] = (ans[x] + group[a] - group[b] + M) % M;
        st[b].insert(x);
    }
    parent[a] = b;
    return;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        st[i].insert(i);
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        dsu_unite(dsu_find(u), dsu_find(v));
    }
    for (int i = 0; i < n; i++) {
        if (parent[i] == i) {
            for (int x : st[i]) {
                ans[x] = (ans[x] + group[i]) % M;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
