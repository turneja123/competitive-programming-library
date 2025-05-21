//https://codesprintla25.kattis.com/contests/codesprintla25open/problems/arcanesecret
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int a[N];

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    int sz = n / k;
    map<int, int> freq;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        freq[a[i]]++;
    }
    sort(a, a + n);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int big = n - (upper_bound(a, a + n, a[i]) - a);
        if (freq[a[i]] + big <= k / 2) {
            continue;
        }
        if (big > (k / 2) * sz) {
            continue;
        }
        ans++;
    }
    cout << ans;

    return 0;
}
