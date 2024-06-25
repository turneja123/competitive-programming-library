//https://atcoder.jp/contests/abc359/tasks/abc359_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1500;
const long long M = 998244353;

int a[N];
bool is_pal[N];

long long dp[N][N];

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    int bits = 1 << k;
    for (int i = 0; i < bits; i++) {
        is_pal[i] = true;
        vector<int> c;
        for (int j = 0; j < k; j++) {
            int l = 1 << j;
            int cl = i & l;
            if (cl == 0) {
                c.push_back(0);
            } else {
                c.push_back(1);
            }
        }
        for (int j = 0; j < k / 2; j++) {
            if (c[j] != c[k - 1 - j]) {
                is_pal[i] = false;
            }
        }
    }
    set<int> st;
    st.insert(0);
    for (int i = 0; i < k; i++) {
        set<int> nw_st;
        for (int x : st) {
            if (s[i] == 'A') {
                nw_st.insert(x * 2);
            } else if (s[i] == 'B') {
                nw_st.insert(x * 2 + 1);
            } else {
                nw_st.insert(x * 2);
                nw_st.insert(x * 2 + 1);
            }
        }
        st = nw_st;
    }
    for (int x : st) {
        if (!is_pal[x]) {
            dp[k - 1][x] = 1;
        }
    }
    for (int i = k; i < n; i++) {
        for (int j = 0; j < bits; j++) {
            if (is_pal[j]) {
                continue;
            }
            int nw = 0;
            for (int p = k - 2; p >= 0; p--) {
                int b = 1 << p, c = j & b;
                if (c != 0) {
                    nw += b * 2;
                }
            }
            if (s[i] == 'A') {
                if (!is_pal[nw]) {
                    dp[i][nw] = (dp[i][nw] + dp[i - 1][j]) % M;
                }
            } else if (s[i] == 'B') {
                if (!is_pal[nw + 1]) {
                    dp[i][nw + 1] = (dp[i][nw + 1] + dp[i - 1][j]) % M;
                }
            } else {
                if (!is_pal[nw]) {
                    dp[i][nw] = (dp[i][nw] + dp[i - 1][j]) % M;
                }
                if (!is_pal[nw + 1]) {
                    dp[i][nw + 1] = (dp[i][nw + 1] + dp[i - 1][j]) % M;
                }

            }
        }
    }
    long long ans = 0;
    for (int j = 0; j < bits; j++) {
        ans += dp[n - 1][j];
    }
    cout << ans % M;



    return 0;
}
