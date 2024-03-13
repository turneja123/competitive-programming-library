//https://atcoder.jp/contests/abc344/tasks/abc344_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
unordered_map<int, int> nxt;
unordered_map<int, int> prv;

int main() {
    IOS;
    int n;
    cin >> n;
    int k = n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        nxt[a[i]] = a[i + 1];
    }
    for (int i = 1; i < n; i++) {
        prv[a[i]] = a[i - 1];
    }
    int start = a[0];
    nxt[a[n - 1]] = -1;
    prv[a[0]] = -1;
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t, x, y;
        cin >> t;
        if (t == 2) {
            k--;
            cin >> x;
            int pr = prv[x], nx = nxt[x];
            if (pr != -1) {
                if (nx != -1) {
                    nxt[pr] = nx;
                } else {
                    nxt[pr] = -1;
                }
            }
            if (nx != -1) {
                if (pr != -1) {
                    prv[nx] = pr;
                } else {
                    prv[nx] = -1;
                    start = nx;
                }
            }
            prv[x] = -2;
            nxt[x] = -2;
        } else {
            k++;
            cin >> x >> y;
            int nx = nxt[x];
            if (nx != -1) {
                nxt[y] = nx;
                prv[nx] = y;
            } else {
                nxt[y] = -1;
            }
            nxt[x] = y;
            prv[y] = x;
        }
    }
    for (int i = 0; i < k; i++) {
        cout << start << " ";
        start = nxt[start];
    }

    return 0;
}
