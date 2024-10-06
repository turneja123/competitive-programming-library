//https://codeforces.com/contest/1991/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int ans[N];

int main() {
    IOS;
    int t;
    cin >> t;
    ans[1] = 1, ans[2] = 4, ans[3] = 2;
    for (int i = 4; i < N; i += 4) {
        ans[i] = 3;
        ans[i + 2] = 4;
    }
    for (int i = 5; i < N; i += 4) {
        ans[i] = 1;
        ans[i + 2] = 2;
    }
    while (t--) {
        int n;
        cin >> n;
        if (n == 1) {
            cout << 1 << endl;
        } else if (n < 4) {
            ans[2] = 2;
            cout << 2 << endl;
        } else if (n < 6) {
            ans[2] = 2;
            cout << 3 << endl;
        } else {
            ans[2] = 4;
            cout << 4 << endl;
        }
        for (int i = 1; i <= n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
