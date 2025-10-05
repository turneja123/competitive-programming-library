//https://www.codechef.com/problems/PRODEQSUM?tab=statement
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll INF = 1e12;

int r[N];
int a[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int last = n;
        for (int i = n - 1; i >= 0; i--) {
            r[i] = last;
            if (a[i] != 1) {
                last = i;
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ll sum = a[i], prod = sum;
            ans++;
            int j = i;
            while (prod < INF) {
                int add = r[j] - j - 1;
                if (sum < prod && prod - sum <= add) {
                    ans++;
                }
                sum += add;
                j = r[j];
                if (j == n) {
                    break;
                }
                sum += a[j];
                prod *= a[j];
                if (sum == prod) {
                    ans++;
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
