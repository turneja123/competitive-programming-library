//https://atcoder.jp/contests/abc367/tasks/abc367_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;

int a[N];

long long suf[N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    map<long long, int> mpr, mpl;
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = suf[i + 1] + a[i];
        mpr[suf[i] % m]++;
    }
    long long sum = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        mpr[suf[i] % m]--;
        ans += mpr[(m - sum % m) % m];
        ans += mpl[sum % m];
        mpl[sum % m]++;
        sum += a[i];
    }
    cout << ans;

    return 0;
}
