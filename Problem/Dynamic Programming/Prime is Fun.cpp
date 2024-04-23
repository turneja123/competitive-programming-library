//https://www.spoj.com/problems/ARRPRM/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int P = 2005;
vector<int> primes;
bitset<P> is_prime;
int dp[P][2];
int a[P];
int pref[P];


int main() {
    IOS;
    is_prime[2] = true;
    for (int i = 3; i < P; i += 2) {
        is_prime[i] = true;
    }
    for (int i = 3; i * i < P; i += 2){
        for (int j = i * i; is_prime[i] && j < P; j += (i << 1)){
            is_prime[j] = false;
        }
    }
    for (int i = 1; i < P; i++){
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            dp[i][0] = 0, dp[i][1] = 0;
            pref[i] = pref[i - 1] + a[i];
        }
        for (int i = 2; i <= n; i++) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
            dp[i][1] = dp[i - 1][0];
            for (int j = 0; j < primes.size() && i >= primes[j]; j++) {
                dp[i][1] = max(dp[i][1], dp[i - primes[j]][0] + pref[i] - pref[i - primes[j]]);
            }
        }
        cout << max(dp[n][0], dp[n][1]) << endl;

    }
    return 0;
}
