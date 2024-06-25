//https://www.codechef.com/problems/COUNTN
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int spf[N];
long long prime_sum[N];
bool is_prime[N];

void sieve(int n){
    for (int i = 1; i < n; i++) {
        spf[i] = i;
        is_prime[i] = true;
    }
    is_prime[1] = false;
    for (int i = 2; i < n; i++) {
        prime_sum[i] = prime_sum[i - 1];
        if (is_prime[i]) {
            for (int j = 2 * i; j < n; j += i) {
                is_prime[j] = false;
                spf[j] = min(spf[j], i);
            }
            prime_sum[i] += i;
        }
    }
}

int main() {
    IOS;
    sieve(N);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        long long ans = prime_sum[spf[n]] * n;
        cout << ans << endl;
    }
    return 0;
}
