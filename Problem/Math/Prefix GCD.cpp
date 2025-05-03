//https://codeforces.com/contest/2013/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

vector<int> divs[N];
int ct[N];
int dp[N];
int a[N];
int go[N];

int main() {
    IOS;
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            divs[j].push_back(i);
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int mx = 0, g = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            g = (g == 0 ? a[i] : __gcd(g, a[i]));
            mx = max(mx, a[i]);
        }
        for (int i = 0; i < n; i++) {
            a[i] /= g;
            for (int j : divs[a[i]]) {
                ct[j]++;
            }
        }
        for (int i = 1; i <= mx; i++) {
            for (int j : divs[i]) {
                dp[j] = ct[j];
            }
            for (int j = divs[i].size() - 1; j >= 0; j--) {
                for (int k = j + 1; k < divs[i].size(); k++) {
                    if (divs[i][k] % divs[i][j] == 0) {
                        dp[divs[i][j]] -= dp[divs[i][k]];
                    }
                }
            }
            go[i] = i;
            for (int j : divs[i]) {
                if (dp[j]) {
                    go[i] = min(go[i], j);
                }
            }
        }
        long long best = 1e18;
        for (int i = 0; i < n; i++) {
            long long cur = a[i];
            int val = a[i];
            for (int j = 1; j < n; j++) {
                if (val == 1) {
                    cur += n - j;
                    break;
                }
                val = go[val];
                cur += val;
            }
            best = min(best, cur);
        }
        cout << best * g << endl;
        for (int i = 0; i <= mx; i++) {
            ct[i] = 0;
        }
    }
    return 0;
}
