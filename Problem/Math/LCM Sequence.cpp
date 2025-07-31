//https://atcoder.jp/contests/abc412/tasks/abc412_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int P = 1e7 + 5;
vector<char> is_prime(P, false);
vector<long long> primes{2};

bool is_prime_seg[P];

void segmentedSieve(long long l, long long r) {
    for (int i = 0; i < r - l + 1; i++) {
        is_prime_seg[i] = true;
    }
    for (long long i : primes) {
        for (long long j = max(i * i, (l + i - 1) / i * i); j <= r; j += i) {
            is_prime_seg[j - l] = false;
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
    for (ll i = 3; i < P; i += 2){
        if (is_prime[i]) {
            primes.push_back(i);
        }
        for (ll j = i * i; is_prime[i] && j < P; j += (i << 1)){
            is_prime[j] = false;
        }
    }
    long long l, r;
    cin >> l >> r;
    segmentedSieve(l, r);
    for (ll i = 2; i < P; i++) {
        if (!is_prime[i]) {
            continue;
        }
        __int128 j = i;
        while (j <= r) {
            if (j >= l && j <= r) {
                is_prime_seg[j - l] = true;
            }
            j *= i;
        }
    }
    is_prime_seg[0] = 1;
    int ans = 0;
    for (int i = 0; i < r - l + 1; i++) {
        ans += is_prime_seg[i];
    }
    cout << ans;

    return 0;
}
