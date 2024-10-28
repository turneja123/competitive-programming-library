//https://codeforces.com/contest/2033/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 505;

int a[N][N];
int ans[N][N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> a[i][j];
                if (a[i][j] < 0) {
                    int mn = min(i, j);
                    ans[i - mn][j - mn] = max(ans[i - mn][j - mn], abs(a[i][j]));
                }
            }
        }
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                sum += ans[i][j];
                ans[i][j] = 0;
            }
        }
        cout << sum << endl;
    }
    return 0;
}
