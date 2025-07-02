//https://arena.petlja.org/sr-Latn-RS/competition/20202021drzavno-vezba#tab_133823
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const long long M = 1e9 + 7;

int freq[N];
long long dp[N];
long long fact[N];

int main() {
    IOS;
    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = fact[i - 1] * i % M;
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        freq[a]++;
    }
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            dp[i] += freq[j];
        }
        dp[i] = dp[i] * (dp[i] - 1);
    }
    long long ans = 0;
    for (int i = N - 1; i > 0; i--) {
        for (int j = 2 * i; j < N; j += i) {
            dp[i] -= dp[j];
        }
        ans = (ans + dp[i] % M * (n - 1) % M * fact[n - 2] % M * i % M) % M;
    }
    cout << ans;

    return 0;
}

