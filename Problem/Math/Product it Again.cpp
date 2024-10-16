//https://www.spoj.com/problems/PROD1GCD/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e7 + 5;
const long long M = 1e9 + 7;

bool is_prime[N];
vector<int> primes;

void sieve(int n){
    for (int i = 1; i < n; i++) {
        is_prime[i] = true;
    }
    is_prime[1] = false;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = 2 * i; j < n; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

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

long long a[32][N / 10];
long long pw[32][N / 10];
int mx[N / 10];

int main() {
    IOS;
    sieve(N);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        if (n > m) {
            swap(n, m);
        }
        for (int j = 0; j < primes.size() && primes[j] <= n; j++) {
            long long prod = primes[j]; int i = 0;
            while (prod <= n) {
                a[i][j] = (long long)(n / prod) * (m / prod);
                pw[i][j] = prod;
                mx[j] = i;
                i++;
                prod *= primes[j];
            }
        }
        long long ans = 1;
        for (int j = 0; j < primes.size() && primes[j] <= n; j++) {
            for (int i = mx[j]; i >= 0; i--) {
                for (int p = i + 1; p <= mx[j]; p++) {
                    a[i][j] -= a[p][j];
                }
                ans = ans * modPow(pw[i][j], a[i][j] % (M - 1)) % M;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
