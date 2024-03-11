//solution for https://cses.fi/problemset/task/1713/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        gp_hash_table<int, int> fact;
        int n, ans = 1;
        cin >> n;
        for (int i = 2; i <= sqrt(n); i++) {
            while (n % i == 0) {
                n /= i;
                fact[i]++;
            }
        }
        if (n > 1) {
            fact[n]++;
        }
        for (auto it = fact.begin(); it != fact.end(); ++it) {
            ans *= it->second + 1;
        }
        cout << ans << endl;

    }


    return 0;
}
