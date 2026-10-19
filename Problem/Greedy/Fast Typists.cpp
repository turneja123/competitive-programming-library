//bbc15
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a[i] ^= x;
    }
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a[i] ^= x;
    }
    int ans = 0, l = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] != a[i - 1]) {
            if (a[i - 1] == 1) {
                int s = i - l;
                ans += (s + k - 1) / k;
            }
            l = i;
        }
    }
    if (a[l] == 1) {
        int s = n - l;
        ans += (s + k - 1) / k;
    }
    cout << ans;

    return 0;
}
