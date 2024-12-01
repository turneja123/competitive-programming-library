//https://cses.fi/problemset/task/1112/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1000;
const long long M = 1e9 + 7;

int prefix[N];
int trans[N][26];
long long dp[N][N];

int main() {
	IOS;
	int n, m;
	string s;
	cin >> n >> s;
	m = s.size();
    int k = 0;
    for (int i = 1; i < m; i++) {
        while (k > 0 && s[k] != s[i]) {
            k = prefix[k - 1];
        }
        if (s[k] == s[i]) {
            k++;
        }
        prefix[i] = k;
    }
	for (int i = 0; i <= m; i++) {
        for (int c = 0; c < 26; c++) {
            char ch = 'A' + c;
            if (i < m && ch == s[i]) {
                trans[i][c] = i + 1;
            } else {
                if (i == 0) {
                    trans[i][c] = 0;
                } else {
                    trans[i][c] = trans[prefix[i - 1]][c];
                }
            }
        }
    }
    long long ans = 0, pw = 26;
	dp[0][0] = 25, dp[0][1] = 1;
	for (int i = 1; i < n; i++) {
        pw = (pw * 26) % M;
        for (int j = 0; j < m; j++) {
            for (int c = 0; c < 26; c++) {
                dp[i][trans[j][c]] = (dp[i][trans[j][c]] + dp[i - 1][j]) % M;
            }
        }
	}
    for (int j = 0; j < m; j++) {
        ans = (ans + dp[n - 1][j]) % M;
    }
    cout << (pw - ans + M) % M;
	return 0;
}
