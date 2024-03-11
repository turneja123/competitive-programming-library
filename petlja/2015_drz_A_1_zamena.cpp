#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e7 + 5;
int dp[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < N; i++) {
        dp[i] = -1;
    }
    int sol = 0;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int best = 0;
        for (int j = 0; j < s.size(); j++) {
            char c = s[j];
            for (int k = 0; k < 10; k++) {
                if (k == 0 && j == 0 && s.size() != 1) {
                    continue;
                }
                if ('0' + k == c) {
                    continue;
                }
                s[j] = '0' + k;
                int cur = stoi(s);
                if (dp[cur] == -1) {
                    continue;
                }
                best = max(best, dp[cur] + abs(c - '0' - k));
            }
            s[j] = c;
        }
        dp[stoi(s)] = best;
        sol = max(sol, best);
    }
    cout << sol;
    return 0;

}
