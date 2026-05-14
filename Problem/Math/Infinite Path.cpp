//https://codeforces.com/contest/1327/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int c[N];
vector<int> divs[N];

int main() {
    IOS;
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            divs[j].push_back(i);
        }
    }

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
        }
        for (int i = 0; i < n; i++) {
            int b;
            cin >> b;
            c[a[i]] = b;
        }
        vector<int> vis(n, 0);
        int best = n;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                vector<int> cyc;
                int u = i;
                while (!vis[u]) {
                    vis[u] = 1;
                    cyc.push_back(a[u]);
                    u = a[u];
                }
                int m = cyc.size();
                for (int d : divs[m]) {
                    for (int i = 0; i < d; i++) {
                        int ok = c[cyc[i]];
                        for (int j = i; j < m; j += d) {
                            if (ok != c[cyc[j]]) {
                                ok = -1;
                            }
                        }
                        if (ok != -1) {
                            best = min(best, d);
                        }
                    }
                }
            }
        }
        cout << best << endl;
    }

    return 0;
}
