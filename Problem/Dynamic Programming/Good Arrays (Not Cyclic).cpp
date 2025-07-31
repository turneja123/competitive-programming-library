//https://www.codechef.com/START194A/problems/CNTGOODARRH
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;
const long long M = 1e9 + 7;

bitset<N> b[N];

string s[N];
long long dp[N * N + 5], dp_nx[N * N + 5];
long long add[2 * N + 5];
bool seen[N * N + 5];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        long long ans = 1;
        for (int i = 0; i < n; i++) {
            cin >> s[i];
            for (int j = 0; j < n; j++) {
                if (s[i][j] == '1') {
                    b[i].set(j);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            ans = ans * b[i].count() % M;
        }
        dp[0] = 1;
        vector<int> go{0};
        for (int i = 0; i < n / 2; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    if (s[i][j] == '1' && s[i + n / 2][k] == '1') {
                        add[j - k + N]++;
                    }
                }
            }
            vector<int> go_nx;
            for (int j : go) {
                for (int k = -n + 1; k <= n - 1; k++) {
                    int nx = j + k;
                    if (nx < 0 || nx > n * n || add[k + N] == 0) {
                        continue;
                    }
                    if (!seen[nx]) {
                        go_nx.push_back(nx);
                        seen[nx] = true;
                    }
                    dp_nx[nx] = (dp_nx[nx] + dp[j] * add[k + N]) % M;
                }
                dp[j] = 0;
            }
            go = go_nx;
            for (int j : go) {
                dp[j] = dp_nx[j];
                dp_nx[j] = 0;
                seen[j] = false;
            }
            for (int i = 0; i <= 2 * N; i++) {
                add[i] = 0;
            }
        }
        cout << (ans - dp[0] + M) % M << endl;
        for (int j : go) {
            dp[j] = 0;
        }
        for (int i = 0; i < n; i++) {
            b[i].reset();
        }
    }


    return 0;
}
