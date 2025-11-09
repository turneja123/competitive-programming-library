//https://cses.fi/problemset/task/3397
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 21;

ll fact[N];


int main() {
    IOS;
    fact[0] = 1;
    for (int i = 1; i < 21; i++) {
        fact[i] = fact[i - 1] * i;
    }
    int t;
    cin >> t;
    while (t--) {
        int c;
        cin >> c;
        if (c == 1) {
            int n; ll k;
            cin >> n >> k;
            vector<int> seen(n + 1, 0);
            vector<int> ans;
            for (int i = 1; i <= n; i++) {
                int ct = 0;
                int last = -1; ll rem = 0;
                for (int j = 1; j <= n; j++) {
                    if (k - fact[n - i] * ct > 0) {
                        last = j;
                        rem = fact[n - i] * ct;
                    }
                    if (!seen[j]) {
                        ct++;
                    }
                }
                ans.push_back(last);
                k -= rem;
                seen[last] = 1;
            }
            for (int j : ans) {
                cout << j << " ";
            }
            cout << endl;

        } else {
            int n;
            cin >> n;
            vector<int> seen(n + 1, 0);
            ll ans = 0;
            for (int i = 1; i <= n; i++) {
                int a;
                cin >> a;
                int ct = 0;
                for (int j = 1; j < a; j++) {
                    if (!seen[j]) {
                        ct++;
                    }
                }
                ans += fact[n - i] * ct;
                seen[a] = 1;
            }
            cout << ans + 1 << endl;
        }
    }
    return 0;
}
