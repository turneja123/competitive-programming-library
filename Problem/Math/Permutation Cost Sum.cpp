//https://www.codechef.com/START201A/problems/P_COST_SUM
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const ll M = 998244353;

int a[N];
int vis[N];
int ct[N];

ll S(ll n) {
    return (n * (n + 1) / 2) % M;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) {
                int u = i;
                int s = 0;
                while (!vis[u]) {
                    vis[u] = true;
                    u = a[u];
                    s++;
                }
                ct[s]++;

            }
        }
        vector<int> sizes;
        for (int i = 1; i <= n; i++) {
            if (ct[i]) {
                sizes.push_back(i);
            }
        }

        ll ans = 0;
        for (int A = 1; A <= n; A++) {
            for (int s : sizes) {
                if (s == 1) {
                    continue;
                }
                ll add = 0;
                ll spl = ((ll)A * s) / (s - 1);
                spl = min(spl, (ll)n);
                add = (add + S(spl) * (s - 1)) % M;

                if (spl < n) {
                    add = (add + (ll)(n - spl) * A % M * s % M) % M;
                }
                add = add * ct[s] % M;
                ans = (ans + add) % M;
            }
        }
        cout << ans << endl;
        for (int i = 1; i <= n; i++) {
            vis[i] = false;
            ct[i] = 0;
        }
    }

    return 0;
}
