//https://codeforces.com/contest/2027/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

long long a[N];
long long val[N];

bool vis[N];

long long ans;
set<long long> seen;
map<long long, vector<int>> mp;

void dfs(int i, long long k, long long n) {
    ans = max(ans, n - k);
    if (seen.find(k) != seen.end()) {
        return;
    }
    seen.insert(k);
    vector<int> start = mp[k];
    for (int j : start) {
        if (!vis[j]) {
            vis[j] = true;
            dfs(j, k - (j - 1), n);
        }
    }
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            val[i] = n + 1 - a[i] - i;
            mp[val[i]].push_back(i);
            vis[i] = false;
        }
        seen.insert(0);
        vector<int> start = mp[0];
        ans = n;
        for (int i : start) {
            if (!vis[i]) {
                vis[i] = true;
                dfs(i, -(i - 1), n);
            }
        }
        cout << ans << endl;
        seen.clear();
        mp.clear();
    }
    return 0;
}
