//https://cses.fi/problemset/task/2214/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int main() {
    IOS;
    int n; ll k;
    cin >> n >> k;
    vector<int> ans(n, -1);
    int i = 0;
    while (i < n) {
        if (k - (n - (i + 1)) >= 0) {
            ans[n - (i + 1)] = i;
            k -= n - (i + 1);
            i++;
        } else {
            ans[k] = i;
            i++;
            break;
        }
    }
    for (int j = 0; j < n; j++) {
        if (ans[j] == -1) {
            ans[j] = i++;
        }
        cout << ans[j] + 1 << " ";
    }

    return 0;
}
