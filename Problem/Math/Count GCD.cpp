//https://codeforces.com/contest/1750/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 998244353;

int a[N];

long long calc(int g, int m, vector<int> &x) {
    vector<int> primes;
    for (int p : x) {
        if (g % p == 0) {
            primes.push_back(p);
        }
    }
    long long ans = 0;
    int n = primes.size();
    for (int i = 0; i < 1 << n; i++) {
        int prod = 1;
        for (int j = 0; j < n; j++) {
            int c = i & (1 << j);
            if (c) {
                prod *= primes[j];
            }
        }
        if (__builtin_popcount(i) % 2 == 0) {
            ans += m / prod;
        } else {
            ans -= m / prod;
        }
    }
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int g = a[0], tmp = g;
        vector<int> primes;
        for (int i = 2; i <= sqrt(g); i++) {
            if (tmp % i == 0) {
                primes.push_back(i);
                while (tmp % i == 0) {
                    tmp /= i;
                }
            }
        }
        if (tmp > 1) {
            primes.push_back(tmp);
        }
        long long ans = 1;
        for (int i = 1; i < n; i++) {
            if (a[i] == a[i - 1]) {
                ans = ans * (m / a[i]) % M;
            } else {
                if (a[i - 1] % a[i] != 0) {
                    ans = 0;
                    break;
                }
                ans = ans * calc(a[i - 1] / a[i], m / a[i], primes) % M;
            }
        }
        cout << ans << endl;
    }

    return 0;
}
