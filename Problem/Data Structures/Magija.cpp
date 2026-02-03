//https://evaluator.hsin.hr/events/coci26_4/tasks/HONI252646magija/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 18;

struct DSU {
    vector<int> parent;
    vector<int> sz;
    vector<int> mn;
    vector<int> mx;

    DSU() {}

    DSU(int n, int f) {
        parent.resize(n);
        sz.resize(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        if (f != -1) {
            mn.resize(n);
            mx.resize(n);
            iota(mn.begin(), mn.end(), 0);
            iota(mx.begin(), mx.end(), 0);
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
        parent[b] = a;
        if (mn.size()) {
            mn[a] = min(mn[a], mn[b]);
            mx[a] = max(mx[a], mx[b]);
        }
    }
};

DSU dsu[K];


void calc(int a, int b, int k) {
    int A = dsu[k].dsu_find(a), B = dsu[k].dsu_find(b);
    if (A != B) {
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
        dsu[i] = DSU(n, (i == 0 ? 0 : -1));
    }
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 2) {
            int a, b, d;
            cin >> a >> b >> d;
            a--, b--;
            int k = 31 - __builtin_clz(d);
            calc(a, b, k);
            calc(a + d - (1 << k), b + d - (1 << k), k);
        } else {
            int j;
            cin >> j;
            j--;
            int a = dsu[0].dsu_find(j);
            cout << dsu[0].mn[a] + 1 << " " << dsu[0].mx[a] + 1 << endl;
        }
    }

    return 0;
}
