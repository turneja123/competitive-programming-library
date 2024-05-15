//https://www.spoj.com/problems/FACTDIV/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const long long M = 1e9 + 7;

int prime_cnt[N];
bool is_prime[N];
vector<int> primes;
long long ans[N];
long long ct[N];
long long pref[N];

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
    is_prime[2] = true;
    for (int i = 3; i < n; i += 2) {
        is_prime[i] = true;
    }
    for (int i = 3; i * i < n; i += 2){
        for (int j = i * i; is_prime[i] && j < n; j += (i << 1)){
            is_prime[j] = false;
        }
    }
    for (int i = 1; i < n; i++){
        prime_cnt[i] = prime_cnt[i - 1] + is_prime[i];
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
}

int main() {
    IOS;
    sieve(N);
    ct[2] = 1;
    ans[1] = 1, ans[2] = 2;
    pref[1] = ans[1], pref[2] = pref[1] + ans[2];
    for (int i = 3; i < N; i++) {
        if (is_prime[i]) {
            ans[i] = ans[i - 1] * 2 % M;
            ct[i]++;
        } else {
            int n = i;
            ans[i] = ans[i - 1];
            for (int j = 0; primes[j] * primes[j] <= i; j++) {
                int e = 0;
                while (n % primes[j] == 0) {
                    e++;
                    n /= primes[j];
                }
                if (e > 0) {
                    ans[i] = ans[i] * modPow(ct[primes[j]] + 1, M - 2) % M;
                    ct[primes[j]] += e;
                    ans[i] = ans[i] * (ct[primes[j]] + 1) % M;
                }
            }
            if (n > 1) {
                ans[i] = ans[i] * modPow(ct[n] + 1, M - 2) % M;
                ct[n]++;
                ans[i] = ans[i] * (ct[n] + 1) % M;
            }
        }
        pref[i] = (pref[i - 1] + ans[i]) % M;
    }
    int t;
    cin >> t;
    while (t--) {
        int l, r;
        cin >> l >> r;
        cout << (pref[r] - pref[l - 1] + M) % M << endl;
    }
    return 0;
}
