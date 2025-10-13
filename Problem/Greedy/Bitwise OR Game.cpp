//https://atcoder.jp/contests/arc208/tasks/arc208_a
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int ct[30];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            for (int j = 0; j < 30; j++) {
                int c = a[i] & (1 << j);
                if (c) {
                    ct[j]++;
                }
            }
        }
        string ans = "Bob";
        for (int j = 0; j < 30; j++) {
            if (ct[j] > 0 && ct[j] % 2 == 0) {
                ans = "Alice";
            }
            ct[j] = 0;
        }
        cout << ans << endl;
    }

    return 0;
}
