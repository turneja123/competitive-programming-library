//https://codeforces.com/contest/2033/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int a[N];
bool vis[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                int u = i, ct = 0;
                while (!vis[u]) {
                    vis[u] = true;
                    ct++;
                    u = a[u];
                }
                ans += (ct - 1) / 2;
            }
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            vis[i] = 0;
        }
    }
    return 0;
}
