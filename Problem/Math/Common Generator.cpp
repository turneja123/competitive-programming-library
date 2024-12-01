//https://codeforces.com/contest/2029/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;

int a[N];
int dp[N];
bool freq[N];
bool vis[N];
bool composite[N];
vector<int> divs[N];

void dfs(int u, int j) {
    dp[u] = j;
    for (int d : divs[u]) {
        int v = u + d;
        if (v < N && dp[v] < j) {
            dfs(v, j);
        }
    }
    return;
}

int main() {
    IOS;
    for (int i = 2; i < N; i++) {
        if (!composite[i]) {
            divs[i].push_back(i);
            for (int j = 2 * i; j < N; j += i) {
                divs[j].push_back(i);
                composite[j] = true;
            }
        }
    }
    for (int i = N - 1; i > 1; i--) {
        if (!composite[i]) {
            dfs(i, i);
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int mx = -1;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (!composite[a[i]]) {
                mx = max(mx, a[i]);
            }
        }
        if (mx == -1) {
            mx = 2;
        }
        bool can = true;
        for (int i = 0; i < n; i++) {
            if (dp[a[i]] < mx) {
                can = false;
            }
        }
        if (!can) {
            cout << -1 << endl;
        } else {
            cout << mx << endl;
        }
    }

    return 0;
}
