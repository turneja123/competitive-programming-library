//https://atcoder.jp/contests/arc212/tasks/arc212_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 55;

int a[N][N];
int ans[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    while (1) {
        int f = 0;
        for (int i = 0; i < n; i++) {
            int s = 0;
            for (int j = 0; j < n; j++) {
                s += (ans[i] == ans[j] ? 1 : -1) * a[i][j];
            }
            if (s < 0) {
                ans[i] ^= 1;
                f = 1;
            }
        }
        if (!f) {
            break;
        }
    }
    for (int i = 0; i < n; i++) {
        if (ans[i]) {
            cout << 'X';
        } else {
            cout << 'Y';
        }
    }


    return 0;
}
