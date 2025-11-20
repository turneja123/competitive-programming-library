//https://eolymp.com/en/problems/12273
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 32000;

bool is_prime[N];
vector<int> primes;

int main() {
    IOS;
    for (int i = 2; i < N; i++) {
        is_prime[i] = 1;
    }
    for (int i = 2; i < N; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = 2 * i; j < N; j += i) {
                is_prime[j] = 0;
            }
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        int ans = 1;
        for (int p : primes) {
            if (n % p == 0) {
                int prod_m = 1, prod_n = 1;
                while (n % p == 0) {
                    prod_n *= p;
                    n /= p;
                }
                while ((ll)prod_m * p <= min(prod_n, m)) {
                    prod_m *= p;
                }
                ans *= prod_n / prod_m;
            }
        }
        if (n > 1 && m < n) {
            ans *= n;
        }
        cout << ans << endl;

    }

    return 0;
}