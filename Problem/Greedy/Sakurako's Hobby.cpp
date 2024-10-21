//https://codeforces.com/contest/2008/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int ans[N];
int parent[N];
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
        string s;
        cin >> s;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                int u = i, ct = 0;
                while (!vis[u]) {
                    vis[u] = true;
                    if (s[u] == '0') {
                        ct++;
                    }
                    parent[u] = i;
                    u = a[u];
                }
                ans[i] = ct;
            }
        }
        for (int i = 0; i < n; i++) {
            cout << ans[parent[i]]  << " ";
        }
        cout << endl;
        for (int i = 0; i < n; i++) {
            ans[i] = 0;
            parent[i] = 0;
            vis[i] =0;
        }
    }
    return 0;
}
