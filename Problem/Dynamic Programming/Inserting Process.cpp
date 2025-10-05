//https://atcoder.jp/contests/abc425/tasks/abc425_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 22;
const ll M = 998244353;

int ptr[1 << K];
ll dp[1 << K];
int seen[1 << K];
int restore[1 << K];
pair<string, int> v[1 << K];

int main() {
    IOS;
    int n;
    cin >> n;
    string s;
    cin >> s;
    map<string, int> mp;
    for (int i = 0; i < 1 << n; i++) {
        string x = "";
        for (int j = 0; j < n; j++) {
            int c = i & (1 << j);
            if (c) {
                x += s[j];
            }
        }
        v[i] = {x, i};
    }
    sort(v, v + (1 << n));
    string x = ""; int last = 0;
    for (int i = 1; i < 1 << n; i++) {
        if (v[i].first != x) {
            x = v[i].first;
            last = v[i].second;
        }
        ptr[v[i].second] = last;
    }
    dp[0] = 1;

    for (int i = 1; i < 1 << n; i++) {
        int m = 0;
        for (int j = 0; j < n; j++) {
            int c = i & (1 << j);
            if (c) {
                int cur = ptr[i ^ (1 << j)];
                if (!seen[cur]) {
                    seen[cur] = true;
                    restore[m++] = cur;
                }
            }
        }
        for (int k = 0; k < m; k++) {
            int j = restore[k];
            dp[i] = (dp[i] + dp[j]) % M;
            seen[j] = false;
        }
    }
    cout << dp[(1 << n) - 1];
    return 0;
}
