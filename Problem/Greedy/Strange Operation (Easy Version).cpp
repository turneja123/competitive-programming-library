//https://codeforces.com/contest/2156/problem/F1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int id[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
            id[a[i]] = i;
        }
        while (1) {
            int c = 0;
            for (int i = 2; i < n; i++) {
                if (id[i] < id[i - 1] && id[i] < id[i - 2]) {
                    int x = id[i], y = id[i - 1], z = id[i - 2];

                    a[x] -= 2;
                    a[y]++;
                    a[z]++;
                    id[a[x]] = x;
                    id[a[y]] = y;
                    id[a[z]] = z;
                    c = 1;

                }
            }
            if (!c) {
                break;
            }
        }
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            ans[id[i]] = i;
        }
        for (int i = 0; i < n; i++) {
            cout << ans[i] + 1 << " ";
        }
        cout << endl;
    }

    return 0;
}
