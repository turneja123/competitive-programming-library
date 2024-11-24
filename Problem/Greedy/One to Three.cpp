//https://www.codechef.com/problems/ONETOTHREE
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int a[N];
bool can[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            can[i] = false;
        }
        queue<int> q;
        for (int i = 1; i < n - 1; i++) {
            if (a[i - 1] + a[i + 1] == 4 && a[i] == 3) {
                can[i] = true;
                q.push(i);
            }
        }
        while (q.size()) {
            int i = q.front();
            q.pop();
            if (a[i - 1] + a[i + 1] == 4) {
                a[i] = 1;
            }
            if (i > 1) {
                if (!can[i - 1] && a[i - 1] != 2 && a[i - 2] + a[i] == 4) {
                    can[i - 1] = true;
                    q.push(i - 1);
                }
            }
            if (i < n - 2) {
                if (!can[i + 1] && a[i + 1] != 2 && a[i + 2] + a[i] == 4) {
                    can[i + 1] = true;
                    q.push(i + 1);
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += a[i];
        }
        cout << ans << endl;

    }
    return 0;
}

