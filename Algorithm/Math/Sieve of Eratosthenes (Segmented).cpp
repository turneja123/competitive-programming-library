//https://www.spoj.com/problems/PRINT/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int P = sqrt(2147483647) + 2;
vector<char> is_prime(P, false);
vector<long long> primes{2};

void segmentedSieve(long long l, long long r) {
    if (l == 2) {
        cout << 2 << endl;
    }
    if (l % 2 == 0) {
        l++;
    }
    vector<char> is_prime_seg(r - l + 1, true);
    for (long long i : primes) {
        if (i == 2) {
            continue;
        }
        for (long long j = max(i * i, (l + i - 1) / i * i); j <= r; j += i) {
            is_prime_seg[j - l] = false;
        }
    }

    for (int i = 0; i < r - l + 1; i += 2) {
        if (is_prime_seg[i]) {
            cout << (long long)i + l << endl;
        }
    }
    return;
}

int main() {
    IOS;
    is_prime[2] = true;
    for (int i = 3; i < P; i += 2) {
        is_prime[i] = true;
    }
    for (int i = 3; i < P; i += 2){
        if (is_prime[i]) {
            primes.push_back(i);
        }
        for (int j = i * i; is_prime[i] && j < P; j += (i << 1)){
            is_prime[j] = false;
        }
    }
    int t;
    cin >> t;
    while (t--) {
        long long l, r;
        cin >> l >> r;
        segmentedSieve(l, r);
    }

    return 0;
}
