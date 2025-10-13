//https://codeforces.com/contest/2153/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e7 + 5;

bool is_prime[N];
bool seen[N];
vector<int> primes;

int legendre(int n, int k) {
    long long fact_pow = 0;
    while (n) {
        n /= k;
        fact_pow += n;
    }
    return fact_pow;
}

vector<int> divs[1000];

int main() {
    IOS;
    for (int i = 2; i < N; i++) {
        is_prime[i] = true;
    }
    for (int i = 2; i < N; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = (ll)i * i; j < N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        int j = lower_bound(primes.begin(), primes.end(), n) - primes.begin();
        if (primes[j] == n) {
            cout << 0 << endl;
            continue;
        }
        j--;
        int p = primes[j];
        for (int i = p; i <= n; i++) {
            int a = i;
            for (int j : primes) {
                if (j * j > a) {
                    break;
                }
                if (a % j == 0) {
                    divs[i - p].push_back(j);
                    while (a % j == 0) {
                        a /= j;
                    }
                }
            }
            if (a > 1) {
                divs[i - p].push_back(a);
            }
        }
        ll ans = 0;
        for (int i = p; i < n; i++) {
            vector<int> restore;
            int mn = 1e9;
            for (int j = i; j <= n; j++) {
                int ind = j - p;
                for (int p : divs[ind]) {
                    if (!seen[p]) {
                        seen[p] = true;
                        restore.push_back(p);
                        int x = legendre(i, p), y = legendre(n, p);
                        if (x != y) {
                            ll P = p; int e = 1;
                            while (1) {
                                if (y / e != x / e) {
                                    mn = min(mn, x / e);
                                }
                                e++;
                                P = P * p;
                                if (P > m) {
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            ans += mn;
            for (int p : restore) {
                seen[p] = false;
            }
        }
        cout << ans << endl;
        for (int i = p; i < n; i++) {
            divs[i - p].clear();
        }
    }
    return 0;
}
