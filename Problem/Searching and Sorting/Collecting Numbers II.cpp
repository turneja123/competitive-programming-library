//https://cses.fi/problemset/task/2217/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int pos[N];

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
        if (pos[a[i] - 1] == 0) {
            ans++;
        }
    }
    for (int k = 0; k < q; k++) {
        int l, r;
        cin >> l >> r;
        if (l > r) {
            swap(l, r);
        }
        int x = a[l], y = a[r];
        if (abs(x - y) == 1) {
            if (x > y) {
                if (pos[x + 1] > l && pos[x + 1] < r) {
                    ans++;
                }
                if (pos[y - 1] > l && pos[y - 1] < r) {
                    ans++;
                }
                ans--;
            } else {
                if (pos[x - 1] > l && pos[x - 1] < r) {
                    ans--;
                }
                if (pos[y + 1] > l && pos[y + 1] < r) {
                    ans--;
                }
                ans++;
            }
        } else {
            if (pos[x - 1] > l && pos[x - 1] < r) {
                ans--;
            }
            if (pos[x + 1] > l && pos[x + 1] < r) {
                ans++;
            }

            if (pos[y - 1] > l && pos[y - 1] < r) {
                ans++;
            }
            if (pos[y + 1] > l && pos[y + 1] < r) {
                ans--;
            }
        }
        pos[x] = r, pos[y] = l;
        swap(a[l], a[r]);
        cout << ans << endl;
    }

    return 0;
}
