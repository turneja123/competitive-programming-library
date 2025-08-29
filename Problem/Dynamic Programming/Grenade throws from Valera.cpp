//https://basecamp.eolymp.com/en/problems/12198
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int SQ = 700;
const int M = 1e9 + 7;

int a[N];

int pos[SQ];
int prefmn[SQ];
int prefdp[N][SQ];
int dp[SQ];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < SQ; i++) {
        pos[i] = -1;
    }
    for (int i = 0; i < n; i++) {

        if (a[i] < SQ) {
            pos[a[i]] = max(pos[a[i]], i);
        }
        prefmn[0] = pos[0];
        for (int j = 1; j < SQ; j++) {
            prefmn[j] = min(prefmn[j - 1], pos[j]);
        }
        if (pos[0] == -1) {
            dp[0] = 1;
        } else {
            dp[0] = 0;
        }
        for (int j = 1; j < SQ; j++) {
            dp[j] = 0;
            if (prefmn[j - 1] == -1) {
                break;
            }
            int l = pos[j], r = prefmn[j - 1];
            if (l >= r) {
                continue;
            }
            dp[j] = (r - 1 < 0 ? 0 : prefdp[r - 1][j - 1]);
            if (l - 1 >= 0) {
                dp[j] = (dp[j] - prefdp[l - 1][j - 1] + M) % M;
            }
        }
        for (int j = 0; j < SQ; j++) {
            prefdp[i][j] = ((i == 0 ? 0 : prefdp[i - 1][j]) + dp[j]) % M;
        }
    }
    int ans = 0;
    for (int j = 0; j < SQ; j++) {
        ans = (ans + dp[j]) % M;
    }
    cout << ans;
    return 0;
}
