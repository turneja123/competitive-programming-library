//https://www.spoj.com/problems/TLPNGEM/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5;

int dp[N];
int pref[N];

vector<int> pos;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            pref[i] = ((i == 0) ? 0 : pref[i - 1]);
            if (s[i] == '@') {
                pos.push_back(i);
            } else if (s[i] == '*') {
                pref[i]++;
            }
        }
        int j = ((s[0] == '@') ? 1 : 0), ans = n;
        if (pref[n - 1] == 1 && s[0] == '*') {
            ans = 0;
        }
        dp[0] = 0;
        for (int i = 1; i < n; i++) {
            dp[i] = dp[i - 1] + 1;
            if (j < pos.size() && pos[j] == i) {
                for (int k = max(0, j - 3); k < j; k++) {
                    if (pref[pos[k]] == pref[i]) {
                        dp[i] = min(dp[i], dp[pos[k]] + 3);
                    }
                }
                j++;
            }
            if (pref[i] == pref[n - 1]) {
                ans = min(ans, dp[i]);
            }
        }
        cout << ans << endl;
        pos.clear();
    }

    return 0;
}
