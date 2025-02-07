//https://atcoder.jp/contests/abc349/tasks/abc349_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 18;
const int N = 2e5 + 5;

struct DSU {
    vector<int> parent;
    vector<int> sz;

    DSU() {}

    DSU(int n) {
        parent.resize(n);
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
        parent[b] = a;
    }
};

DSU dsu[K];
vector<int> ban[N];
int ans[N];
int color[N];


void calc(int a, int b, int k) {
    int A = dsu[k].dsu_find(a), B = dsu[k].dsu_find(b);
    if (A != B) {
        dsu[k].dsu_unite(A, B);
        if (k != 0) {
            k--;
            calc(a, b + (1 << k), k);
            calc(a + (1 << k), b, k);
        }
    }
    return;
}


int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < K; i++) {
        dsu[i] = DSU(n);
    }
    for (int i = 0; i < n; i++) {
        int d;
        cin >> d;
        if (d == 0) {
            if (i - 1 >= 0 && i + 1 < n) {
                ban[i - 1].push_back(i + 1);
                ban[i + 1].push_back(i - 1);
            }
            continue;
        }
        int a = i - d, b = i + 1;
        if (a - 1 >= 0 && b + d < n) {
            ban[a - 1].push_back(b + d);
            ban[b + d].push_back(a - 1);
        }
        int k = 31 - __builtin_clz(d);
        calc(a, b + d - (1 << k), k);
        calc(a + d - (1 << k), b, k);
    }
    for (int i = 0; i < n; i++) {
        for (int j : ban[i]) {
            if (dsu[0].dsu_find(i) == dsu[0].dsu_find(j)) {
                cout << "No";
                return 0;
            }
        }
    }
    cout << "Yes" << endl;
    for (int i = 0; i < n; i++) {
        int a = dsu[0].dsu_find(i);
        if (color[a] != 0) {
            ans[i] = color[a];
            cout << ans[i] << " ";
            continue;
        }
        set<int> mex;
        for (int j : ban[i]) {
            if (ans[j] != 0) {
                mex.insert(ans[j]);
            }
        }
        int j = 1;
        for (int x : mex) {
            if (x != j) {
                break;
            }
            j++;
        }
        color[a] = j;
        ans[i] = color[a];
        cout << ans[i] << " ";
    }
    return 0;
}
