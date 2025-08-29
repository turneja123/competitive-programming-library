//https://codeforces.com/contest/2135/problem/A
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
vector<int> pos[N];
int dp[N];
int ptr[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            pos[a[i]].push_back(i);
        }
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            dp[i] = dp[i - 1];
            if (ptr[a[i]] - a[i] + 1 >= 0) {
                int j = pos[a[i]][ptr[a[i]] - a[i] + 1] - 1;
                dp[i] = max(dp[i], dp[j] + a[i]);
            }
            ptr[a[i]]++;
        }
        cout << dp[n] << endl;
        for (int i = 1; i <= n; i++) {
            ptr[i] = 0;
            pos[i].clear();
        }
    }

    return 0;
}
