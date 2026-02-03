//https://ocpc2026w.eolymp.space/en/compete/r1t2e978517l1a1e5a39p463hs/problem/11
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const ll M = 1e9 + 7;

int a[N];
ll pref[N];

vector<int> pos[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pref[i] = pref[i - 1] + a[i];
    }
    if (pref[n] < 0) {
        for (int i = 1; i <= n; i++) {
            pref[i] *= -1;
            a[i] *= -1;
        }
    }
    if (pref[n] == 0) {
        ll ans = 1;
        for (int i = 1; i < n; i++) {
            if (pref[i] == 0) {
                ans = ans * 2 % M;
            }
        }
        cout << ans;
    } else {
        vector<ll> compr;
        for (int i = 0; i <= n; i++) {
            compr.push_back(pref[i]);
        }
        sort(compr.begin(), compr.end());
        compr.erase(unique(compr.begin(), compr.end()), compr.end());
        for (int i = 0; i <= n; i++) {
            int j = lower_bound(compr.begin(), compr.end(), pref[i]) - compr.begin();
            pos[j].push_back(i);
        }

        ll ans = 1;
        for (int i = 2; i <= n; i++) {
            if (pref[n] % i == 0) {


                ll s = pref[n] / i;

                vector<int> ids;
                int skip = 0;
                for (int j = 1; j < i; j++) {
                    int id = lower_bound(compr.begin(), compr.end(), s * j) - compr.begin();
                    if (id == compr.size() || compr[id] != s * j) {
                        skip = 1;
                        break;
                    }
                    ids.push_back(id);
                }
                if (skip) {
                    continue;
                }
                vector<ll> dp(n + 1, 0);
                for (int k : pos[ids[0]]) {
                    dp[k] = 1;
                }
                for (int j = 1; j < ids.size(); j++) {
                    ll sum = 0;
                    for (int r = 0, l = 0; r < pos[ids[j]].size(); r++) {
                        while (l < pos[ids[j - 1]].size() && pos[ids[j - 1]][l] < pos[ids[j]][r]) {
                            sum = (sum + dp[pos[ids[j - 1]][l]]) % M;
                            l++;
                        }
                        dp[pos[ids[j]][r]] = sum;
                    }
                }
                for (int k : pos[ids.back()]) {
                    ans = (ans + dp[k]) % M;
                }
            }
        }
        cout << ans;
    }

    return 0;
}
