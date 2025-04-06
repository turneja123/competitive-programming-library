//https://www.spoj.com/problems/INS16H/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3000;
const long long M = 1e9 + 7;
const long long INF = 1e18;

int idx = 0;

vector<int> all_divs;
vector<int> divs[N];
long long val[N];

vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
long long ans = INF;
bool prime_pow[N];

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

gp_hash_table<long long, int, custom_hash> mp;

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

bool kth(long long n, int k) {
    long long l = 2, r = n;
    while (l <= r) {
        long long mid = (l + r) / 2;
        __int128 prod = 1;
        for (int i = 0; i < k; i++) {
            prod *= mid;
            if (prod > n) {
                break;
            }
        }
        if (prod == n) {
            return is_prime(mid);
        }
        if (prod < n) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }

    }
    return false;
}

void calc(long long prod, long long n) {
    if (prod >= ans) {
        return;
    }
    if (n == 1) {
        ans = min(ans, prod);
        return;
    }
    auto it = mp.find(n);
    int ind = it->second;
    if (ind == -1) {
        return;
    }
    it->second = -1;
    for (int j : divs[ind]) {
        long long x = val[j] - 1;
        if (__gcd(prod, x) == 1) {
            calc(prod * x, n / val[j]);
        }
    }
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        long long n;
        cin >> n;
        for (long long i = 1; i <= sqrtl(n); i++) {
            if (n % i == 0) {
                if (i != 1) {
                    val[idx] = i;
                    all_divs.push_back(i);
                    mp[i] = idx++;
                }
                if (i != n / i) {
                    val[idx] = n / i;
                    all_divs.push_back(n / i);
                    mp[n / i] = idx++;
                }
            }
        }
        for (int i = 0; i < all_divs.size(); i++) {
            long long x = val[i] - 1;
            prime_pow[i] = false;
            if (x == 1) {
                continue;
            }
            for (int j = 1; j < 50; j++) {
                if (kth(x, j)) {
                    prime_pow[i] = true;
                }
            }
        }
        for (int i = 0; i < all_divs.size(); i++) {
            for (int j = 0; j < all_divs.size(); j++) {
                if (prime_pow[j] && (val[i] % val[j] == 0)) {
                    divs[i].push_back(j);
                }
            }
        }

        calc(1, n);
        if (ans == INF) {
            ans = -1;
        }
        cout << ans << endl;
        ans = 1e18;
        for (int i = 0; i < all_divs.size(); i++) {
            divs[i].clear();
        }
        all_divs.clear();
        idx = 0;
    }

    return 0;
}
