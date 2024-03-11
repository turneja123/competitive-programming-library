//solution for https://cses.fi/problemset/task/2428/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
map<int, int> freq;

int main() {
    IOS;
    int n, k, d = 0, l = 0;
    ll ans = 0;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (freq[a[i]] == 0) {
            d++;
        }
        freq[a[i]]++;
        while (d > k) {
            freq[a[l]]--;
            if (freq[a[l]] == 0) {
                d--;
            }
            l++;
        }
        ans += i - l + 1;
    }
    cout << ans;
    return 0;
}
