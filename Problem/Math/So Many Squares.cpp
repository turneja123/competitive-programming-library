//https://www.spoj.com/problems/SQRPERF/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const long long K = 51;
const long long M = 1e9 + 7;

long long basis[K];
bool is_prime[N];
int spf[N];

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

void insert_vector(long long a) {
    for (int i = K - 1; i >= 0; i--) {
        long long c = a & (1ll << i);
        if (!c) {
            continue;
        }
        if (!basis[i]) {
            basis[i] = a;
            return;
        }
        a ^= basis[i];
    }
}

int main() {
    IOS;
    sieve(N);
    int n;
    cin >> n;
    while (n != 0) {
        map<int, int> mp;
        for (int i = 0; i < n; i++) {
            int a; long long mask = 0;
            cin >> a;
            while (a > 1) {
                int p = spf[a], j = -1;
                auto it = mp.find(p);
                if (it == mp.end()) {
                    j = mp.size();
                    mp[p] = j;
                } else {
                    j = it->second;
                }
                int e = 0;
                while (a % p == 0) {
                    a /= p;
                    e++;
                }
                if (e % 2 == 1) {
                    mask += 1ll << j;
                }
            }
            insert_vector(mask);
        }
        int sz = 0;
        for (int i = K - 1; i >= 0; i--) {
            if (basis[i]) {
                sz++;
            }
            basis[i] = 0;
        }
        cout << modPow(2, n - sz) - 1 << endl;
        cin >> n;
    }
    return 0;
}
