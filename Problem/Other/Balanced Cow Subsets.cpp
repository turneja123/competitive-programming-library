//https://www.spoj.com/problems/SUBSET/
#pragma GCC optimize("Ofast,fast-math")
#pragma GCC target("avx2,popcnt")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/random>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 20;

int a[K];
int pw[K];
int sum[1 << K];

gp_hash_table<int, vector<int>> mp;

using RNG = __gnu_cxx::sfmt19937;
decltype(RNG()()) x;

int main() {
    RNG rnd(time(NULL));
	IOS;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
        cin >> a[i];
        pw[i] = ((i == 0) ? 1 : pw[i - 1] * 2);
	}
	int bits = 1 << n;
	for (int j = 1; j < bits; j++) {
        for (int i = 0; i < n; i++) {
            int c = j & (1 << i);
            if (c) {
                sum[j] += a[i];
            }
        }
        mp[sum[j]].push_back(j);
	}
	int ans = 0;
	for (int j = 1; j < bits; j++) {
        if (sum[j] % 2 == 1) {
            continue;
        }
        int targ = sum[j] / 2;
        auto it = mp.find(targ);
        if (it == mp.end()) {
            continue;
        }
        int f = 0;
        for (int i = 0; i < K && !f; i++) {
            int k = rnd() % (it->second).size(), mask = (it->second)[k], c = j | mask;
            if (c == j) {
                f = 1;
            }
        }

        if (pw[__builtin_popcount(j)] < (it->second).size()) {
            for (int mask = j; mask > 0 && !f; mask = (mask - 1) & j) {
                if (sum[mask] == targ) {
                    f = 1;
                }
            }
        } else {
           for (int i = 0; i < (it->second).size() && !f; i++) {
                int mask = (it->second)[i], c = j | mask;
                if (c == j) {
                    f = 1;
                }
            }
        }
        ans += f;
	}
	cout << ans;

	return 0;
}
