//https://codeforces.com/contest/1175/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

long long a[N];
long long pref[N];

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        sum += x;
        a[i] = sum;
    }
    sort(a, a + n - 1);
    for (int i = 0; i < n - 1; i++) {
        pref[i] = (i == 0 ? a[i] : pref[i - 1] + a[i]);
    }
    long long ans = sum * k - (k == 1 ? 0 : pref[k - 2]);
    cout << ans << endl;

    return 0;
}
