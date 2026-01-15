//https://www.codechef.com/START221A/problems/LMP6
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
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> x(n, vector<int>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> x[i][j];
                x[i][j]--;
            }
        }
        vector<int> c = {0, m - 1, (n - 1) * m, n * m - 1};
        int l = 1, r = n * m + 1, ans = 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            for (int i = 0; i < n * m; i++) {
                sz[i] = 1;
                parent[i] = i;
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    int u = i * m + j;
                    for (int v : c) {
                        ll d = (ll)(abs(i - v / m) + 1) * (abs(j - v % m) + 1);
                        int a = dsu_find(u), b = dsu_find(v);
                        if (d >= mid && a != b) {
                            dsu_unite(a, b);
                        }
                    }
                }
            }
            int ok = 1;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    int a = dsu_find(i * m + j), b = dsu_find(x[i][j]);
                    if (a != b) {
                        ok = 0;
                    }
                }
            }
            if (ok) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
