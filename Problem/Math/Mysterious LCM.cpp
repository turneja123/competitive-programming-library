//https://codeforces.com/gym/102141/attachments
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
vector<long long> factors;
vector<long long> prime_power;

__int128 mult(__int128 a, __int128 b, __int128 mod) {
    return (__int128)a * b % mod;
}

__int128 f(__int128 x, __int128 c, __int128 mod) {
    return (mult(x, x, mod) + c) % mod;
}

__int128 binpower(__int128 base, __int128 e, __int128 mod) {
    __int128 result = 1;
    base %= mod;
    while (e) {
        if (e & 1) {
            result = (__int128)result * base % mod;
        }
        base = (__int128)base * base % mod;
        e >>= 1;
    }
    return result;
}

long long rho(long long n) {
    long long c = rand() % (n + 1);
    long long x = rand() % (n + 1);
    long long xx = x;
    long long g = 1;
    if (n % 2 == 0) {
        return 2;
    }

    while (g == 1) {
        x = f(x, c, n);
        xx = f(xx, c, n);
        xx = f(xx, c, n);
        g = __gcd(abs(x - xx), n);
    }
    return g;
}

bool check_composite(__int128 n, __int128 a, __int128 d, int s) {
    __int128 x = binpower(a, d, n);
    if (x == 1 || x == n - 1) {
        return false;
    }
    for (int r = 1; r < s; r++) {
        x = (__int128)x * x % n;
        if (x == n - 1) {
            return false;
        }
    }
    return true;
};


bool is_prime(__int128 n) {
    if (n < 2) {
        return false;
    }
    int r = 0;
    __int128 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }
    for (int a : primes) {
        if (n == a) {
            return true;
        }
        if (check_composite(n, a, d, r)) {
            return false;
        }
    }
    return true;
}

void factor(__int128 n) {
    if (n == 1) {
        return;
    }
    if (is_prime(n)) {
        factors.push_back(n);
        return;
    }

    __int128 divisor = rho(n);
    factor(divisor);
    factor(n / divisor);
    return;
}


const int K = 15;
const int N = 1 << K;

int a[N];
int b[N];
int ans[N];
int freq[N];
int temp[N];


int main() {
    IOS;

    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n; long long m;
        cin >> n >> m;
        factor(m);
        sort(factors.begin(), factors.end());
        int i = 0, j = 0;
        while (i < factors.size()) {
            long long cur = factors[i], prod = 1;
            while (i < m && factors[i] == cur) {
                prod *= factors[i];
                i++;
            }
            prime_power.push_back(prod);
            j = i;
        }
        factors.clear();


        int k = prime_power.size(), bits = 1 << k;
        for (int i = 0; i < n; i++) {
            long long a;
            cin >> a;
            if (m % a != 0) {
                continue;
            }
            int mask = 0;
            for (int j = 0; j < k; j++) {
                if (a % prime_power[j] == 0) {
                    mask += 1 << j;
                }
            }
            ans[mask] = 1;
            freq[mask]++;
        }
        int ct = -1;
        for (int t = 0; t < k + 1; t++) {
            if (ans[bits - 1] > 0) {
                ct = t + 1;
                break;
            }

            for (int j = 0; j < bits; j++) {
                temp[j] = ans[j];
                if (freq[j] > 0) {
                    a[j] = 1;
                } else {
                    a[j] = 0;
                }
            }
            for (int i = 0; i < k; i++) {
                for (int j = 0; j < bits; j++) {
                    int c = j & (1 << i);
                    if (c) {
                        ans[j] += ans[j ^ (1 << i)];
                        a[j] += a[j ^ (1 << i)];
                    }
                }
            }
            for (int j = 0; j < bits; j++) {
                b[j] = ans[j] * a[j];
            }
            for (int i = 0; i < k; i++) {
                for (int j = 0; j < bits; j++) {
                    int c = j & (1 << i);
                    if (c) {
                        b[j] -= b[j ^ (1 << i)];
                    }
                }
            }
            for (int j = 0; j < bits; j++) {
                ans[j] = max(temp[j], b[j]);
                ans[j] = min(ans[j], 1);
            }
        }
        cout << "Case " << tt << ": " << ct << endl;
        prime_power.clear();
        for (int i = 0; i < bits; i++) {
            ans[i] = 0;
            freq[i] = 0;
        }


    }


    return 0;
}
