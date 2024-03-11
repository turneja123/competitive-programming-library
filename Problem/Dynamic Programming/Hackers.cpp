//https://www.spoj.com/problems/TREEBA/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e4 + 5;
const int K = 25;
const long long M = 1e9 + 7;
const long long P = 26;
const long long Q = 53;

int dp[N][K][2];
string words[N];
set<pair<long long, long long>> st;

int main() {
    IOS;
	int t;
	cin >> t;
	while (t--) {
        int m, k; string s;
        cin >> m >> k >> s;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            for (int u = 0; u <= k; u++) {
                dp[i][u][0] = -1;
                dp[i][u][1] = -1;
            }
        }
        for (int i = 0; i < m; i++) {
            cin >> words[i];
            long long p_pow = 1;
            long long q_pow = 1;
            long long p_pref = 0, q_pref = 0;
            for (int j = 0; j < words[i].size(); j++) {
                long long c_pref = (words[i][j] - 'a') + 1;
                p_pref = (p_pref + c_pref * p_pow) % M;
                q_pref = (q_pref + c_pref * q_pow) % M;
                p_pow = (p_pow * P) % M;
                q_pow = (q_pow * Q) % M;
            }
            pair<long long, long long> word_hash = make_pair(p_pref, q_pref);
            st.insert(word_hash);
        }
        dp[0][1][0] = 0;
        for (int i = 0; i < n; i++) {
            for (int u = 0; u <= k; u++) {
                if (i != 0) {
                    dp[i][u][0] = dp[i - 1][u][0];
                    if (u != 0) {
                        dp[i][u][0] = max(dp[i][u][0], dp[i - 1][u - 1][1]);
                    }
                }
            }
            long long p_pow = 1;
            long long q_pow = 1;
            long long p_suf = 0, q_suf = 0;
            for (int j = i; j >= 0 && j >= i - K; j--) {
                long long c_suf = (s[j] - 'a') + 1;
                p_suf = (p_suf * P + c_suf) % M;
                q_suf = (q_suf * Q + c_suf) % M;
                p_pow = (p_pow * P) % M;
                q_pow = (q_pow * Q) % M;
                pair<long long, long long> sub_hash = make_pair(p_suf, q_suf);
                if (st.find(sub_hash) != st.end()) {
                    for (int u = 0; u <= k; u++) {
                        if (j != 0) {
                            if (dp[j - 1][u][1] != -1) {
                                dp[i][u][1] = max(dp[i][u][1], dp[j - 1][u][1] + 1);
                            }
                            if (dp[j - 1][u][0] != -1) {
                                dp[i][u][1] = max(dp[i][u][1], dp[j - 1][u][0] + 1);
                            }
                        } else {
                            dp[i][0][1] = max(dp[i][0][1], 1);
                        }
                    }
                }
            }
        }
        int ans = 0;
        for (int u = 0; u <= k; u++) {
            ans = max(ans, dp[n - 1][u][0]);
            ans = max(ans, dp[n - 1][u][1]);
        }
        st.clear();
        cout << ans << endl;
	}
    return 0;
}
