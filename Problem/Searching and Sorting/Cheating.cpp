//https://dmoj.ca/problem/bts24p2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e6 + 5;

int a[N], b[N];
long long diff[N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    for (int i = 0, j = 0; i < n; i++) {
        diff[j] += a[i];
        j += b[i];
        if (j >= m) {
            j -= m;
            diff[0] += a[i], diff[j] -= a[i];
        } else {
            diff[j] -= a[i];
        }
    }
    long long sum = 0;
    for (int i = 0; i < m; i++) {
        sum += diff[i];
        cout << sum << " ";
    }

    return 0;
}
