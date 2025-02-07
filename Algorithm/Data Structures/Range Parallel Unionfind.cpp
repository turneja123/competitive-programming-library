//https://judge.yosupo.jp/problem/range_parallel_unionfind
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 20;
const long long M = 998244353;

struct DSU {
    vector<int> parent;
    vector<int> sum;
    vector<int> sz;

    DSU() {}

    DSU(int n) {
        parent.resize(n);
        sum.resize(n, 0);
        sz.resize(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
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
        sum[a] = (sum[a] + sum[b]) % M;
        parent[b] = a;
    }
};

DSU dsu[K];

long long ans = 0;

void calc(int a, int b, int k) {
    int A = dsu[k].dsu_find(a), B = dsu[k].dsu_find(b);
    if (A != B) {
        if (k == 0) {
            ans = (ans + (long long)dsu[k].sum[A] * dsu[k].sum[B]) % M;
        }
        dsu[k].dsu_unite(A, B);
        if (k != 0) {
            k--;
            calc(a, b, k);
            calc(a + (1 << k), b + (1 << k), k);
        }
    }
    return;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < K; i++) {
        dsu[i] = DSU(n);
    }
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        dsu[0].sum[i] = x;
    }
    for (int i = 0; i < q; i++) {
        int d, a, b;
        cin >> d >> a >> b;
        if (d == 0 || a == b) {
            cout << ans << endl;
            continue;
        }
        int k = 31 - __builtin_clz(d);
        calc(a, b, k);
        calc(a + d - (1 << k), b + d - (1 << k), k);
        cout << ans << endl;
    }
    return 0;
}
