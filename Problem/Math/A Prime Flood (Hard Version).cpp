//https://codeforces.com/contest/2264/problem/E2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const ll M = 998244353;

int mask[N];
int is_prime[N];
int spf[N];

vector<int> divs[N];
vector<int> v_mask[N];
ll pw[N];

vector<pair<int, int>> dp[N];

int main() {
    IOS;
    pw[0] = 1;
    for (int i = 1; i < N; i++) {
        pw[i] = pw[i - 1] * 2 % M;
        is_prime[i] = (i != 1);
        mask[i] = 1;
        spf[i] = i;
    }
    for (int i = 2; i < N; i++) {
        if (is_prime[i]) {
            divs[i].push_back(i);
            mask[i] = i;
            for (int j = 2 * i; j < N; j += i) {
                divs[j].push_back(i);
                is_prime[j] = 0;
                mask[j] *= i;
                spf[j] = min(spf[j], i);
            }
        }
    }
    for (int i = 2; i < N; i++) {
        v_mask[mask[i]].push_back(i);
    }

    dp[1].push_back({1, 1});
    int ct = 0, mx = 0;
    for (int i = 2; i < N; i++) {
        vector<int> p;
        int n = mask[i];
        while (n > 1) {
            p.push_back(spf[n]);
            n /= spf[n];
        }
        n = p.size();
        vector<int> cand;
        for (int j = 0; j < 1 << n; j++) {
            int prod = 1;
            for (int k = 0; k < n; k++) {
                int c = j & (1 << k);
                if (c) {
                    prod *= p[k];
                }
            }
            auto it = upper_bound(v_mask[prod].begin(), v_mask[prod].end(), i);
            while (it != v_mask[prod].end()) {
                cand.push_back(*it);
                it++;
            }
        }
        ct += cand.size();
        sort(cand.begin(), cand.end());
        dp[i].push_back({i, i});
        for (int j : cand) {
            auto it = upper_bound(dp[i - 1].begin(), dp[i - 1].end(), make_pair(j, N));
            it--;
            if (it->second != dp[i].back().second) {
                dp[i].push_back({j, it->second});
            }
        }
        mx = max(mx, (int)dp[i].size());
    }

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            ans = (ans + a[i]) % M;
            int mid = i + 1;
            for (int j = 0; j < dp[a[i]].size(); j++) {
                int r = (j == dp[a[i]].size() - 1 ? n - 1 : lower_bound(a.begin(), a.end(), dp[a[i]][j + 1].first) - a.begin() - 1);
                if (mid > r) {
                    continue;
                }
                ll ways = pw[mid - 1 - i] * (pw[r - mid + 1] - 1) % M;
                ans = (ans + ways * dp[a[i]][j].second) % M;
                mid = r + 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
