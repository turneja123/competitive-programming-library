//https://ocpc2025s.eolymp.space/en/compete/1kvhss06dl7d13loo53cn0nk1k/problem/13
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;

char ans[N][N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    if (n != m) {
        cout << "No";
        return 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans[i][j] = '.';
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = n - 1 - i; j < n; j++) {
            ans[i][j] = '#';
        }
    }
    cout << "Yes" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << ans[i][j];
        }
        cout << endl;
    }
    return 0;
}
