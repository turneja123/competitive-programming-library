//https://www.hackerrank.com/contests/projecteuler/challenges/euler249/problem
#pragma GCC optimize("Ofast,fast-math")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 7001;
const int S = 2935500;

const long long M = 1e16;

bool is_prime[S];
vector<int> primes;

long long dp[S];
long long dp_next[S];
long long pref[N];

int queries[N];

int main() {
    IOS;
    int t, n = 0;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> queries[i];
        n = max(n, queries[i]);
    }
    is_prime[2] = true;
    for (int i = 3; i < S; i += 2) {
        is_prime[i] = true;
    }
    for (int i = 3; i * i < S; i += 2){
        for (int j = i * i; is_prime[i] && j < S; j += (i << 1)){
            is_prime[j] = false;
        }
    }
    int sum = 0;
    for (int i = 1; i < n; i++){
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    dp[0] = 1;
    __int128 c = 0;
    for (int i = 0; i < primes.size(); i++) {
        sum += primes[i];
        for (int j = sum; j >= primes[i]; j--) {
            dp[j] = (dp[j] + dp[j - primes[i]]) % M;
            if (is_prime[j]) {
                c += dp[j - primes[i]];
            }
        }
        int r = (i == primes.size() - 1) ? n : primes[i + 1];
        c %= M;
        for (int j = primes[i]; j < r; j++) {
            pref[j] = c;
        }
    }
    for (int i = 0; i < t; i++) {
        cout << pref[queries[i] - 1] << " ";
    }

    return 0;
}
