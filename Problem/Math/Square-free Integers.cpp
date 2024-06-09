//https://www.spoj.com/problems/SQFREE/
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e7;

long long ans, n;
bool is_prime[N];
vector<long long> primes;

auto udiv = [](const uint64_t& a, const uint64_t& b) -> uint64_t {
    return (double)a / b + 1e-9;
};

void calc(long long prod, int i, int j) {
    if (j % 2 == 1) {
        ans -= udiv(n, prod);
    } else {
        ans += udiv(n, prod);
    }
    for (; i < primes.size(); i++) {
        __int128 cur = (__int128)prod * primes[i];
        if (cur > n) {
            return;
        }
        calc(cur, i + 1, j + 1);
    }
}

int main() {
	IOS;
	int t;
	cin >> t;
	primes.resize(664579);
	int j = 0;
	primes[j++] = 4;
	is_prime[2] = true;
	for (int i = 3; i < N; i += 2) {
        is_prime[i] = true;
	}
	for (int i = 3; i < N; i += 2) {
        if (is_prime[i]) {
            for (long long j = (long long)i * i; j < N; j += i) {
                is_prime[j] = false;
            }
            primes[j++] = (long long)i * i;
        }
	}
	while (t--) {
        cin >> n;
        ans = n;
        for (int i = 0; i < primes.size(); i++) {
            calc(primes[i], i + 1, 1);
        }
        cout << ans << endl;
	}

	return 0;
}
