//https://www.spoj.com/problems/ANDQQ/
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const long long M = 2117566807;

const int K = 19;
const int N = 1 << K;

vector<int> queries[K];

long long a[N];
long long b[N];
long long ans[N];

long long seed, sum = 0;

long long gen() {
    seed = (seed * 997 + 29) % M;
    return seed;
}

void conv(int k) {
    for (int j = 0; j < N; j++) {
        b[j] = 0;
    }
    for (int i = 0; i < queries[k].size(); i++) {
        b[queries[k][i]]++;
    }

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            int c = j & (1 << i);
            if (c) {
                b[j ^ (1 << i)] += b[j];
            }
        }
    }
    for (int j = 0; j < N; j++) {
        ans[j] = a[j] * b[j];
    }
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            int c = j & (1 << i);
            if (c) {
                ans[j ^ (1 << i)] -= ans[j];
            }
        }
    }
    for (int j = 0; j < N; j++) {
        if (__builtin_popcount(j) == k) {
            sum += ans[j];
        }
    }
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n, q, mod_A, mod_V, mod_K;
        cin >> seed >> n >> q >> mod_A >> mod_V >> mod_K;
        for (int i = 0; i < n; i++) {
            int x = gen() % mod_A;
            a[x]++;
        }
        for (int i = 0; i < q; i++) {
            int v = gen() % mod_V, k = gen() % mod_K;
            queries[k].push_back(v);
        }
        for (int i = 0; i < K; i++) {
            for (int j = 0; j < N; j++) {
                int c = j & (1 << i);
                if (c) {
                    a[j ^ (1 << i)] += a[j];
                }
            }
        }

        for (int k = 0; k < mod_K; k++) {
            conv(k);
            queries[k].clear();
        }
        cout << "Case " << tt << ": " << sum << endl;
        sum = 0;
        for (int j = 0; j < N; j++) {
            a[j] = 0;
        }
    }

    return 0;
}
