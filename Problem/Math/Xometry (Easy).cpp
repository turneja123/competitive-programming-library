//https://www.codechef.com/problems/XSQR
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int MAX = 4e6 + 5;
const int N = 5005;

int ct[MAX];
int a[N];

int main(){
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (i == j) {
                    continue;
                }
                int sum = a[i] ^ a[j];
                ct[sum]++;
                ans -= 8;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (i == j) {
                    continue;
                }
                int sum = a[i] ^ a[j];
                ans += (2 * ct[sum] + 2) * 2;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    continue;
                }
                int sum = a[i] ^ a[j];
                ct[sum] = 0;
            }
        }
        cout << ans << endl;

    }

    return 0;
}
