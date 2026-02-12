//https://www.codechef.com/problems/MAXMINMEX
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll M = 998244353;

ll fact[N];
ll pw[N];

int main() {
    IOS;
    fact[0] = 1, pw[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = fact[i - 1] * i % M;
        pw[i] = pw[i - 1] * 2 % M;
    }

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        int last = a[0], cur = 1, best = 1, ct = 1;
        for (int i = 1; i < n; i++) {
            if (a[i] > last + 1) {
                cur = 1;
            } else {
                cur++;
            }
            last = a[i];
            if (cur > best) {
                best = cur;
                ct = 1;
            } else if (cur == best) {
                ct++;
            }
        }
        ll ans = fact[n - best] * pw[best - 1] % M * ct % M;
        cout << ans << endl;

    }

    return 0;
}
