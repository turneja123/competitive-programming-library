//https://www.spoj.com/problems/JPM/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e4 + 5;
const int INF = 1e9;

bool composite[N];
int dp[N];
vector<int> primes;


int main() {
    IOS;
    dp[0] = 0;
    dp[1] = INF;
    for (int i = 2; i < N; i++) {
        dp[i] = INF;
        if (!composite[i]) {
            primes.push_back(i);
            for (int j = i * 2; j < N; j += i) {
                composite[j] = true;
            }
        }
    }
    for (int i = 0; i < primes.size(); i++) {
        for (int j = N - 1; j >= primes[i]; j--) {
            if (dp[j - primes[i]] != INF) {
                dp[j] = min(dp[j], dp[j - primes[i]] + 1);
            }
        }
    }
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int n;
        cin >> n;
        cout << "Case " << i << ": " << ((dp[n] == INF) ? -1 : dp[n]) << endl;
    }

    return 0;
}
