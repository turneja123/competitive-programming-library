//https://codeforces.com/contest/2030/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 998244353;

long long inv[N];
long long fact[N];
long long factinv[N];
int freq[N];

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

long long binomial(long long n, long long k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            freq[a]++;
        }
        if (freq[0] == 0) {
            cout << 0 << endl;
            for (int i = 0; i < n; i++) {
                freq[i] = 0;
            }
            continue;
        }
        vector<pair<long long, long long>> dp(freq[0] + 1);
        vector<pair<long long, long long>> dp_sum(freq[0] + 1);
        dp_sum[0] = make_pair(0, 0);
        long long ans = 0;
        int m = n;
        m -= freq[0];
        for (int j = 1; j <= freq[0]; j++) {
            dp[j] = make_pair(binomial(freq[0], j), binomial(freq[0], j) * j % M);
            dp_sum[j] = make_pair((dp[j].first + dp_sum[j - 1].first) % M, (dp[j].second + dp_sum[j - 1].second) % M);
            ans = (ans + dp[j].second * modPow(2, m - freq[1])) % M;
        }
        int f = freq[0];
        for (int i = 1; i < n; i++) {
            f = min(f, freq[i]);
            m -= freq[i];
            if (f == 0) {
                break;
            }
            vector<pair<long long, long long>> dp_nx(f + 1);
            vector<long long> suf(freq[i] + 1);
            suf[freq[i]] = 1;
            for (int j = freq[i] - 1; j > 0; j--) {
                suf[j] = (suf[j + 1] + binomial(freq[i], j)) % M;
            }

            for (int j = 1; j <= f; j++) {
                pair<long long, long long> ways = make_pair((dp_sum.back().first - dp_sum[j - 1].first + M) % M, (dp_sum.back().second - dp_sum[j - 1].second + M) % M);
                dp_nx[j] = make_pair(ways.first * binomial(freq[i], j) % M, (ways.second * binomial(freq[i], j) + ways.first * binomial(freq[i], j) % M * j) % M);
                if (j != freq[i]) {
                    ways = make_pair(dp[j].first * suf[j + 1] % M, dp[j].second * suf[j + 1] % M);
                    dp_nx[j].first = (dp_nx[j].first + ways.first) % M;
                    dp_nx[j].second = (dp_nx[j].second + ways.second + ways.first * j) % M;
                }
            }
            for (int j = 1; j <= f; j++) {
                dp[j] = dp_nx[j];
                dp_sum[j] = make_pair((dp[j].first + dp_sum[j - 1].first) % M, (dp[j].second + dp_sum[j - 1].second) % M);
                ans = (ans + dp[j].second * modPow(2, m - freq[i + 1])) % M;
            }
            dp_sum.resize(f + 1);
            dp.resize(f + 1);
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            freq[i] = 0;
        }
    }

    return 0;
}
