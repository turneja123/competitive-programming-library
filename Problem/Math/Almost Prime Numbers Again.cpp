//https://www.spoj.com/problems/KPRIMESB/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e6 + 5;

int prime_cnt[N];
bool is_prime[N];

int main() {
	IOS;
	is_prime[2] = true;
	prime_cnt[2] = 1;
	for (int i = 3; i < N; i += 2) {
        is_prime[i] = true;
	}
	for (int i = 3; i < N; i++) {
        if (is_prime[i]) {
            for (int j = 2 * i; j < N; j += i) {
                is_prime[j] = false;
            }
        }
        prime_cnt[i] = prime_cnt[i - 1] + is_prime[i];
	}
	int t;
	cin >> t;
	for (int tt = 1; tt <= t; tt++) {
        int n, k;
        cin >> n >> k;
        vector<int> p(k);
        int ans = n - 1;
        for (int i = 0; i < k; i ++) {
            cin >> p[i];
            if (p[i] <= n) {
                ans++;
            }
        }
        int bits = 1 << k, ct = 0;
        for (int j = 1; j < bits; j++) {
            long long prod = 1;
            for (int i = 0; i < k; i++) {
                int c = j & (1 << i);
                if (c != 0) {
                    prod *= p[i];
                }
            }
            if (__builtin_popcount(j) % 2 == 1) {
                ct += (long long)n / prod;
            } else {
                ct -= (long long)n / prod;
            }
        }
        if (n == 0) {
            ans = 0;
        }
        cout << "Case " << tt << ": " << ans - ct - prime_cnt[n] << endl;

	}
	return 0;
}
