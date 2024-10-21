//https://www.codechef.com/problems/COUNTTRIP
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

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
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < min(n, i + 102); j++) {
                int diff = abs(a[i] - a[j]);
                if (diff == j - i) {
                    ans += j - i + 1;
                } else if (diff >= j - i && diff % 2 == (j - i) % 2) {
                    int l = i - (diff - (j - i)) / 2;
                    if (l >= 0) {
                        ans++;
                    }
                    int r = j + (diff - (j - i)) / 2;
                    if (r < n) {
                        ans++;
                    }
                }
            }
        }
        cout << ans * 2 + n << endl;

    }
    return 0;
}
