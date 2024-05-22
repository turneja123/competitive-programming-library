//https://www.spoj.com/problems/PRMFN/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

long long pw[19];

__int128 read() {
    __int128 x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
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

const long long R = 3814697265625;

long long dig[] = {0, 2, 3, 5, 7};

long long get(long long x) {
    if (x == 0) {
        return 2;
    }
    long long n = 0;
    vector<int> digits;
    while (x > 0) {
        digits.push_back(max(2ll, dig[x % 5]));
        x /= 5;
    }
    for (int i = digits.size() - 1; i >= 0; i--) {
        n *= 10;
        n += digits[i];
    }
    return n;
}

int main() {
    IOS;
    pw[0] = 1;
    for (int i = 1; i < 19; i++) {
        pw[i] = pw[i - 1] * 5;
    }
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        long long n;
        cin >> n;
        long long l = 0, r = R - 1, j = 0;
        while (l <= r) {
            long long mid = (l + r) / 2;
            if (get(mid) <= n) {
                j = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        long long ans = 0;
        for (; j >= 0 && ans == 0;) {
            long long x = get(j);
            if (x > n) {
                long long t = j;
                vector<int> digits;
                while (t > 0) {
                    digits.push_back(t % 5);
                    t /= 5;
                }
                for (int i = 0; i < digits.size(); i++) {
                    if (digits[i] == 0) {
                        j -= pw[i];
                        break;
                    }
                }
                continue;
            }
            if (is_prime(x)) {
                ans = x;
            }
            j--;
        }
        cout << "Case " << tt << ": " << ans << endl;
    }

    return 0;
}
