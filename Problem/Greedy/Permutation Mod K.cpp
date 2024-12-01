//https://www.codechef.com/problems/PERMMODK
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
        int n, k;
        cin >> n >> k;
        vector<int> ans;

        if (n == 1 || k == 1 || (k == 2 && n % 2 == 1)) {
            cout << -1 << endl;
            continue;
        }
        for (int j = 1; j <= n / k; j++) {
            for (int i = 1; i < k; i++) {
                ans.push_back(k * (j - 1) + i + 1);
            }
            ans.push_back(k * (j - 1) + 1);
        }
        for (int i = 2; i <= n % k; i++) {
            ans.push_back((n / k) * k + i);
        }
        if (n % k != 0) {
            ans.push_back((n / k) * k + 1);
        }
        if (n % k == 1) {
            swap(ans[n - 1], ans[n - 3]);
        }
        for (int x : ans) {
            cout << x << " ";
        }
        cout << endl;
    }

    return 0;
}
