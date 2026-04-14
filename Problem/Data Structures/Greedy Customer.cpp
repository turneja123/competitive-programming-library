//https://atcoder.jp/contests/arc217/tasks/arc217_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e7 + 5;

int add[N];
int up[N];
char vis[N];

void dfs(int u) {
    if (vis[u]) {
        return;
    }
    vis[u] = 1;
    if (up[u] == u) {
        return;
    }
    dfs(up[u]);
    add[u] += add[up[u]];
    return;
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i <= m; i++) {
            vis[i] = 0;
            add[i] = 0;
            up[i] = i;
        }
        int mx = m, lazy = 0;
        for (int i = 0; i < n; i++) {
            int x = a[i];
            if (mx < x) {
                continue;
            }
            if (2 * x > mx) {
                for (int i = x + lazy; i <= mx + lazy && i <= m; i++) {
                    up[i] = i - x;
                    add[i] = x;
                }
                mx = max(x - 1, mx - x);
            } else {
                for (int i = lazy; i < x + lazy && i + x <= m; i++) {
                    up[i] = i + x;
                    add[i] = -x;

                }
                lazy += x;
                mx -= x;
            }
        }
        ll s = 0;
        for (int i = 0; i <= m; i++) {
            if (!vis[i]) {
                dfs(i);
            }
            s ^= (ll)i * (add[i] + lazy);
        }
        cout << s << endl;

    }


    return 0;
}
