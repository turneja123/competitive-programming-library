//https://codeforces.com/contest/2211/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

//#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;


vector<ll> g[N];
int ans[N];


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = n - 1; i >= 0; i--) {
            g[i].clear();
            ans[i] = 0;
            ll a; int k;
            cin >> a >> k;
            if (k == 0) {
                ans[i] = 1;
                g[i].push_back(a);
            } else {
                for (int j = 0; j < k; j++) {
                    int v;
                    cin >> v;
                    v--;
                    for (ll x : g[v]) {
                        x = __gcd(x, a);
                        for (ll y : g[i]) {
                            x /= __gcd(x, y);
                        }
                        if (x != 1) {
                            g[i].push_back(x);
                        }
                    }
                    ans[i] += ans[v];
                    g[v].clear();
                }
                if (g[i].empty()) {
                    ans[i]++;
                    g[i].push_back(a);
                }
            }
            cout << ans[i] << endl;
        }
    }

    return 0;
}
