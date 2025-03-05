//https://codeforces.com/contest/2031/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int ans[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n % 2 == 1) {
            if (n < 27) {
                cout << -1 << endl;
                continue;
            }
            int j = 1;
            ans[1] = j;
            ans[10] = j;
            ans[26] = j;
            j++;
            int i = 2;
            for (i; i < 10; i += 2) {
                ans[i] = j;
                ans[i + 1] = j;
                j++;
            }
            i++;
            for (i; i < 23; i += 2) {
                ans[i] = j;
                ans[i + 1] = j;
                j++;
            }
            ans[23] = j, ans[27] = j;
            j++;
            ans[24] = j, ans[25] = j;
            j++;
            i = 28;
            for (i; i <= n; i += 2) {
                ans[i] = j;
                ans[i + 1] = j;
                j++;
            }
            for (int i = 1; i <= n; i++) {
                cout << ans[i] << " ";
            }
            cout << endl;
        } else {
            for (int i = 1; i <= n / 2; i++) {
                cout << i << " " << i << " ";
            }
            cout << endl;
        }
    }


    return 0;
}
