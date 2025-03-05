//https://codeforces.com/contest/2070/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e6 + 5;
const int B = 20;

long long ans[N];
long long a[B];
long long mask_sum[N];

int n;

int odd_mask = 0;

void subset_sum_convolution(vector<int> F, vector<int> G) {
    vector<vector<int>> f(n + 1, vector<int> (1 << n, 0));
    vector<vector<int>> g(n + 1, vector<int> (1 << n, 0));
    for (int mask = 0; mask < (1 << n); mask++) {
        int ct = __builtin_popcount(mask & odd_mask);
        f[ct][mask] = F[mask];
        g[ct][mask] = G[mask];
    }

    for (int k = 0; k <= n; k++) {
        for (int i = 0; i <= n; i++) {
            for (int mask = 0; mask < (1 << n); mask++) {
                if (mask >> i & 1) {
                    f[k][mask] += f[k][mask ^ (1 << i)];
                    g[k][mask] += g[k][mask ^ (1 << i)];
                }
            }
        }
    }
    vector<vector<long long>> h(n + 1, vector<long long> (1 << n, 0));
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int k = 0; k <= n; k++) {
            for (int i = 0; i <= k; i++) {
                h[k][mask] += (long long)f[i][mask] * g[k - i][mask];
            }
        }
    }
    for (int k = 0; k <= n; k++) {
        for (int i = 0; i <= n; i++) {
            for (int mask = 0; mask < (1 << n); mask++) {
                if (mask >> i & 1) {
                    h[k][mask] -= h[k][mask ^ (1 << i)];
                }
            }
        }
    }
    for (int mask = 0; mask < (1 << n); mask++)  {
        int ct = __builtin_popcount(mask & odd_mask);
        long long cur = h[ct][mask];
        if (ct == 0) {
            cur -= F[mask];
        }
        long long sum = mask_sum[(1 << n) - 1] - mask_sum[mask];
        ans[sum] += cur;
    }
    return;
}

int main() {
    IOS;
    int m;
    cin >> n >> m;
    vector<int> freq(1 << n, 0);
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        int mask = 0;
        for (int j = 0; j < s.size(); j++) {
            int c = s[j] - 'A';
            mask += 1 << c;
        }
        freq[mask]++;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] % 2 == 1) {
            odd_mask += 1 << i;
        }
    }
    for (int i = 0; i < 1 << n; i++) {
        for (int j = 0; j < n; j++) {
            int c = i & (1 << j);
            if (c) {
                mask_sum[i] += a[j];
            }
        }
    }
    subset_sum_convolution(freq, freq);
    for (int i = 0; i <= mask_sum[(1 << n) - 1]; i++) {
        cout << ans[i] / 2 << " ";
    }
    return 0;
}
