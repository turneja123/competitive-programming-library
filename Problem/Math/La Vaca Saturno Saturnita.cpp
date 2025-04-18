//https://codeforces.com/contest/2094/problem/H
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int a[N];
vector<int> divs[N];
vector<int> pos[N];

int main() {
    IOS;
    for (int i = 2; i < N; i++) {
        for (int j = i; j < N; j += i) {
            divs[j].push_back(i);
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            pos[a[i]].push_back(i);
        }
        for (int i = 0; i < q; i++) {
            int k, l, r;
            cin >> k >> l >> r;
            l--, r--;
            long long ans = 0;
            while (k % a[l] == 0) {
                k /= a[l];
            }
            while (1) {
                int nx = n;
                for (int d : divs[k]) {
                    if (pos[d].size()) {
                        int p = upper_bound(pos[d].begin(), pos[d].end(), l) - pos[d].begin();
                        if (p == pos[d].size() || pos[d][p] > r) {
                            continue;
                        }
                        nx = min(nx, pos[d][p]);
                    }
                }
                if (nx == n) {
                    break;
                }
                ans += (long long)k * (nx - l);
                l = nx;
                while (k % a[nx] == 0) {
                    k /= a[nx];
                }
            }
            ans += (long long)k * (r - l + 1);
            cout << ans << endl;
        }
        for (int i = 0; i < n; i++) {
            pos[a[i]].clear();
        }
    }
    return 0;
}
