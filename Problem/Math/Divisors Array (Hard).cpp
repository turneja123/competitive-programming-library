//https://www.codechef.com/START166A/problems/LOLBSGNJ6PK8
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e7 + 5;
const long long M = 1e9 + 7;

bool is_prime[N];
int spf[N];
long long inv[N];

long long ct[N];
long long ans[N];

void sieve(int n){
    inv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
    }

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
    int n, m;
    cin >> n >> m;
    ans[1] = 1;
    for (int i = 2; i <= m; i++) {
        int j = i;
        ans[i] = ans[i - 1];
        while (j > 1) {
            int p = spf[j], e = 0;
            while (j % p == 0) {
                j /= p;
                e++;
            }
            ans[i] = ans[i] * inv[ct[p] + 1] % M * (ct[p] + e + 1) % M;
            ct[p] += e;
        }
    }

    for (int i = 0; i < n; i++) {
        int j;
        cin >> j;
        long long cur = ans[m];
        while (j > 1) {
            int p = spf[j], e = 0;
            while (j % p == 0) {
                j /= p;
                e++;
            }
            cur = cur * inv[ct[p] + 1] % M * (ct[p] + e + 1) % M;
        }
        cout << cur << " ";
    }
    return 0;
}
