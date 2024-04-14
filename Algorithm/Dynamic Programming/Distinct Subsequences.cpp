//https://www.spoj.com/problems/DSUBSEQ/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const long long M = 1e9 + 7;
long long dp[N];
int last[26];

string s;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        for (int j = 0; j < 26; j++) {
            last[j] = -1;
        }
        cin >> s;
        dp[0] = 1;
        int n = s.size();
        for (int i = 1; i <= n; i++) {
            dp[i] = (dp[i - 1] * 2) % M;
            if (last[s[i - 1] - 'A'] != -1) {
                dp[i] = (dp[i] - dp[last[s[i - 1] - 'A']] + M) % M;
            }
            last[s[i - 1] - 'A'] = i - 1;
        }
        cout << dp[n] << endl;
    }

    return 0;
}
