//https://codeforces.com/contest/1600/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 50;

int b[N][N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    n = min(n, N);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (u < n && v < n) {
            b[u][v] = 1;
            b[v][u] = 1;
        }
    }
    int ok = 0;
    for (int i1 = 0; i1 < n && !ok; i1++) {
        for (int i2 = i1 + 1; i2 < n && !ok; i2++) {
            for (int i3 = i2 + 1; i3 < n && !ok; i3++) {
                for (int i4 = i3 + 1; i4 < n && !ok; i4++) {
                    for (int i5 = i4 + 1; i5 < n && !ok; i5++) {
                        vector<int> v{i1, i2, i3, i4, i5};
                        int s = 0;
                        for (int i = 0; i < 5; i++) {
                            for (int j = i + 1; j < 5; j++) {
                                s += b[v[i]][v[j]];
                            }
                        }
                        if (s == 0 || s == 10) {
                            cout << i1 + 1 << " " << i2 + 1 << " " << i3 + 1 << " " << i4 + 1 << " " << i5 + 1;
                            ok = 1;
                        }
                    }
                }
            }
        }
    }
    if (!ok) {
        cout << -1;
    }
    return 0;
}
