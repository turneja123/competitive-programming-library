//https://www.codechef.com/problems/EQUXOR
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int rt[N];
long long dp[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        map<int, vector<int>> mp;
        int pref = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            rt[i] = n;
        }
        for (int i = 0; i < n; i++) {
            int need = pref ^ a[i];
            auto it = mp.find(need);
            if (it != mp.end()) {
                for (int j = 0; j < (it->second).size(); j++) {
                    rt[(it->second)[j]] = i;
                }
                (it->second).clear();
            }
            auto f = mp.find(pref);
            if (f == mp.end()) {
                vector<int> v{i};
                mp[pref] = v;
            } else {
                mp[pref].push_back(i);
            }
            pref ^= a[i];
        }
        long long ans = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (rt[i] == n) {
                dp[i] = a[i];
            } else {
                dp[i] = a[i] + dp[rt[i]];
            }
            ans = max(ans, dp[i]);
        }
        cout << ans << endl;
    }

    return 0;
}
