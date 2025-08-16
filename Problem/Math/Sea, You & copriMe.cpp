//https://codeforces.com/contest/2131/problem/H
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int a[N];
bool is_prime[N];
int dp[N];

vector<int> divs[N];
int ans[4];
bool flag = false;


int main() {
    IOS;
    for (int i = 2; i < N; i++) {
        is_prime[i] = true;
    }
    for (int i = 2; i < N; i++) {
        if (is_prime[i]) {
            divs[i].push_back(i);
            for (int j = 2 * i; j < N; j += i) {
                is_prime[j] = false;
                divs[j].push_back(i);
            }
        }
    }
    int t;
    cin >> t;
    while (t--) {
        ans[0] = -1, ans[1] = -1, ans[2] = -1, ans[3] = -1;
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            int m = divs[a[i]].size();
            for (int j = 0; j < 1 << m; j++) {
                int prod = 1;
                for (int k = 0; k < m; k++) {
                    int c = (1 << k) & j;
                    if (c) {
                        prod *= divs[a[i]][k];
                    }
                }
                dp[prod]++;
            }
        }
        vector<pair<int, int>> v;
        for (int i = 0; i < n; i++) {
            int m = divs[a[i]].size();
            int s = 0;
            for (int j = 0; j < 1 << m; j++) {
                int mul = 1;
                if (__builtin_popcount(j) % 2 == 1) {
                    mul *= -1;
                }
                int prod = 1;
                for (int k = 0; k < m; k++) {
                    int c = (1 << k) & j;
                    if (c) {
                        prod *= divs[a[i]][k];
                    }
                }
                s += mul * dp[prod];
            }
            s -= a[i] == 1;
            v.push_back({s, i});
        }
        sort(v.begin(), v.end());
        reverse(v.begin(), v.end());
        ans[0] = v[0].second;
        for (int i = n - 1; i > 0; i--) {
            if (__gcd(a[ans[0]], a[v[i].second]) == 1) {
                ans[1] = v[i].second;
                break;
            }
        }
        if (ans[1] != -1) {
            for (int i = 0; i < n; i++) {
                if (__gcd(a[ans[0]], a[v[i].second]) == 1) {
                    v[i].first--;
                }
                if (__gcd(a[ans[1]], a[v[i].second]) == 1) {
                    v[i].first--;
                }
                if (v[i].second != ans[0] && v[i].second != ans[1] && v[i].first > 0) {
                    ans[2] = v[i].second;
                }
            }
            if (ans[2] != -1) {
                for (int i = 0; i < n; i++) {
                    if (v[i].second != ans[0] && v[i].second != ans[1] && v[i].second != ans[2] && __gcd(a[ans[2]], a[v[i].second]) == 1) {
                        ans[3] = v[i].second;
                        break;
                    }
                }
            }
        }
        if (ans[3] != -1) {
            cout << ans[0] + 1 << " " << ans[1] + 1 << " " << ans[2] + 1 << " " << ans[3] + 1 << endl;
        } else {
            cout << 0 << endl;
        }

        for (int i = 0; i < n; i++) {
            int m = divs[a[i]].size();
            for (int j = 0; j < 1 << m; j++) {
                int prod = 1;
                for (int k = 0; k < m; k++) {
                    int c = (1 << k) & j;
                    if (c) {
                        prod *= divs[a[i]][k];
                    }
                }
                dp[prod] = 0;
            }
        }
    }


    return 0;
}
