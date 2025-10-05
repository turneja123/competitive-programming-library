//https://codeforces.com/contest/2152/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

//#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;
const int M = 10005;

int a[N][M];
int sz[N];
int vis[M];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int m = n * n + 1;
        bool can = false;
        for (int i = 0; i < n && !can; i++) {
            cout << "? " << m << " ";
            for (int j = 0; j < n * n + 1; j++) {
                if (!vis[j]) {
                    cout << j + 1 << " ";
                }
            }
            cout << endl;
            cin >> sz[i];
            for (int j = 0; j < sz[i]; j++) {
                cin >> a[i][j];
                a[i][j]--;
                vis[a[i][j]] = 1;
            }
            if (sz[i] >= n + 1) {
                cout << "! ";
                for (int j = 0; j < n + 1; j++) {
                    cout << a[i][j] + 1 << " ";
                }
                cout << endl;
                can = true;
            }
            m -= sz[i];
        }
        if (!can) {
            int last;
            for (int i = n * n; i >= 0; i--) {
                if (!vis[i]) {
                    last = i;
                    break;
                }
            }
            vector<int> ans{last};
            for (int i = n - 1; i >= 0; i--) {
                int j = lower_bound(a[i], a[i] + sz[i], last) - a[i] - 1;
                ans.push_back(a[i][j]);
                last = a[i][j];
            }
            reverse(ans.begin(), ans.end());
            cout << "! ";
            for (int j : ans) {
                cout << j + 1 << " ";
            }
            cout << endl;
        }
        for (int i = 0; i < n * n + 1; i++) {
            vis[i] = 0;
        }
    }
    return 0;
}
