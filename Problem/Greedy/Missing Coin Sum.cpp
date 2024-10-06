//https://cses.fi/problemset/task/2183/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);
    if (a[0] != 1) {
        cout << 1;
        return 0;
    }
    long long r = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > r + 1) {
            break;
        }
        r += a[i];
    }
    cout << r + 1;
    return 0;
}
