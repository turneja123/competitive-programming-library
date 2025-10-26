//https://codeforces.com/contest/2154/problem/C2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> divs[N];
int dp[N];
pair<int, int> p[N];


int main() {
    IOS;
    for (int i = 2; i < N; i++) {
        for (int j = i; j < N; j += i) {
            divs[j].push_back(i);
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            p[i].second = a;
            for (int d : divs[a]) {
                dp[d]++;
            }
        }
        for (int i = 0; i < n; i++) {
            cin >> p[i].first;
        }
        sort(p, p + n);
        ll ans = p[0].first + p[1].first;
        for (int i = 0; i < n; i++) {
            auto [_, a] = p[i];
            for (int d : divs[a]) {
                if (dp[d] > 1) {
                    ans = 0;
                }
            }
            for (int d : divs[a + 1]) {
                if (dp[d] >= 1) {
                    ans = min(ans, (ll)p[i].first);
                }
            }
        }
        auto [x, y] = p[0];
        for (int i = 1; i < n; i++) {
            auto [_, a] = p[i];
            for (int d : divs[a]) {
                int need = d - y % d;
                if (need == d) {
                    d = 0;
                }
                ans = min(ans, (ll)need * x);
            }
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            auto [_, a] = p[i];
            for (int d : divs[a]) {
                dp[d] = 0;
            }
        }
    }


    return 0;
}
