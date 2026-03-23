//https://www.spoj.com/problems/BLSUMSEQ/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e4 + 5;

int a[N];
unsigned int ans[N];
vector<tuple<int, int, int, int>> queries[N];

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < q; i++) {
        int t, l, r, x;
        cin >> t >> l >> r >> x;
        l--, r--;
        queries[l].push_back({r, t, x, i});
    }
    for (int i = 0; i < n; i++) {
        vector<unsigned int> dp(N, 0);
        bitset<N> b;
        dp[0] = 1;
        b[0] = 1;
        sort(queries[i].begin(), queries[i].end());
        for (int j = i, ptr = 0; j < n; j++) {
            b |= b << a[j];
            for (int k = N - 1; k >= a[j]; k--) {
                dp[k] += dp[k - a[j]];
            }
            while (ptr < queries[i].size() && get<0>(queries[i][ptr]) == j) {
                auto [_, t, x, ind] = queries[i][ptr];
                if (t == 1) {
                    if (x >= N) {
                        ans[ind] = 0;
                    } else {
                        ans[ind] = dp[x] - (x == 0);
                    }
                } else {
                    for (int z = 1; z < N; z++) {
                        if (!b[z]) {
                            x--;
                        }
                        if (x == 0) {
                            ans[ind] = z;
                            break;
                        }
                    }
                    if (x != 0) {
                        ans[ind] = N + x - 1;
                    }
                }
                ptr++;
            }
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }


    return 0;
}
