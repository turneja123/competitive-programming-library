#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

vector <int> primes;
const int N = 1e8 + 4;

void atkin(int limit) {
    if (limit > 2) {
        primes.push_back(2);
    }
    if (limit > 3) {
        primes.push_back(3);
    }
    bool *sieve = (bool *)malloc(sizeof(bool) * limit);
    for (int i = 0; i < limit; i++) {
        sieve[i] = false;
    }
    for (int x = 1; x * x < limit; x++) {
        for (int y = 1; y * y < limit; y++) {
            int n = (4 * x * x) + (y * y);

            if (n <= limit && (n % 12 == 1 || n % 12 == 5)) {
                sieve[n] ^= true;
            }

            n = (3 * x * x) + (y * y);
            if (n <= limit && n % 12 == 7) {
                sieve[n] ^= true;
            }

            n = (3 * x * x) - (y * y);
            if (x > y && n <= limit && n % 12 == 11) {
                sieve[n] ^= true;
            }
        }
    }
    for (int r = 5; r * r < limit; r++) {
        if (sieve[r]) {
            for (int i = r * r; i < limit; i += r * r) {
                sieve[i] = false;
            }
        }
    }
    for (int a = 5; a < limit; a++) {
        if (sieve[a]) {
            primes.push_back(a);
        }
    }
}

int main() {
    IOS;
    atkin(N);
    return 0;

}
