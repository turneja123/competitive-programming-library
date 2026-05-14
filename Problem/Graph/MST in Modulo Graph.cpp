//https://codeforces.com/contest/2081/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int parent[N];
int sz[N];

vector<pair<int, int>> edges[N];

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
        int n, m = 0;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            m = max(m, a[i]);
        }
        vector<int> freq(m + 1, 0), nx(m + 1, 0);
        iota(parent, parent + m + 1, 0);
        fill(sz, sz + m + 1, 1);

        for (int i = 0; i < n; i++) {
            freq[a[i]] = 1;
        }
        int last = m + 1;
        for (int i = m; i > 0; i--) {
            if (freq[i]) {
                last = i;
            }
            nx[i] = last;
        }
        for (int i = 1; i <= m; i++) {
            if (!freq[i]) {
                continue;
            }
            int k = (i + 1 > m ? m + 1 : nx[i + 1]);
            if (k <= m) {
                edges[k % i].push_back({i, k});
            }
            for (int j = 2 * i; j <= m; j += i) {
                int k = nx[j];
                if (nx[j] > m) {
                    break;
                }
                edges[k % i].push_back({i, k});
            }
        }
        ll ans = 0;
        for (int i = 0; i <= m; i++) {
            for (auto [u, v] : edges[i]) {
                u = dsu_find(u), v = dsu_find(v);
                if (u != v) {
                    ans += i;
                    dsu_unite(u, v);
                }
            }
            edges[i].clear();
        }
        cout << ans << endl;
    }
    return 0;
}
