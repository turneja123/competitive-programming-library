//https://codeforces.com/contest/2147/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int b[N];
int cost[N];
int notset[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            sum |= a[i];
        }
        int ans = __builtin_popcount(sum);

        for (int z = 0; z < 31; z++) {
            cost[z] = 0; notset[z] = 0;
            for (int i = 0; i < n; i++) {
                b[i] = a[i];
            }
            for (int k = z; k >= 0; k--) {
                int ct = 0;
                for (int i = 0; i < n; i++) {
                    int c = b[i] & (1 << k);
                    if (c) {
                        ct++;
                    }
                }
                int c = sum & (1 << k);
                if (!c) {
                    notset[z]++;
                }
                if (ct == 0) {
                    int best = 0, ind = 0;
                    int full = (1 << k) - 1;
                    for (int i = 0; i < n; i++) {
                        int diff = full & b[i];
                        if (diff > best) {
                            best = diff;
                            ind = i;
                        }
                    }
                    cost[z] += (1 << k) - best;
                    b[ind] -= best;
                }
            }
        }
        for (int i = 0; i < q; i++) {
            int s;
            cin >> s;
            int cur = ans;
            for (int z = 0; z < 31; z++) {
                if (cost[z] <= s) {
                    cur = ans + notset[z];
                }
            }
            cout << cur << endl;
        }

    }
    return 0;
}
