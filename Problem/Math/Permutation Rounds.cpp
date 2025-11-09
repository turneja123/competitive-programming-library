//https://cses.fi/problemset/task/3398/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll M = 1e9 + 7;

int a[N];
int vis[N];
int spf[N];
int is_prime[N];
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

void sieve(int n){
    for (int i = 1; i < n; i++) {
        spf[i] = i;
        is_prime[i] = true;
    }
    is_prime[1] = false;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            for (int j = 2 * i; j < n; j += i) {
                is_prime[j] = false;
                spf[j] = min(spf[j], i);
            }
        }
    }
}

int main() {
    IOS;
    sieve(N);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            int u = i;
            int s = 0;
            while (!vis[u]) {
                vis[u] = true;
                u = a[u];
                s++;
            }
            while (s > 1) {
                int p = spf[s], e = 0;
                while (s % p == 0) {
                    s /= p;
                    e++;
                }
                freq[p] = max(freq[p], e);
            }
        }
    }
    ll ans = 1;
    for (int i = 1; i <= n; i++) {
        ans = ans * modPow(i, freq[i]) % M;
    }
    cout << ans;

    return 0;
}
