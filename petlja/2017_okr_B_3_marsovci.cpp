#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int a[N];

int main() {
    IOS;
    int n;
    cin >> n;
    int mn = 1e9, mx = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mn = min(mn, a[i]);
        mx = max(mx, a[i]);
    }
    vector<int> vmn, vmx;
    for (int i = 0; i < n; i++) {
        if (a[i] == mn) {
            vmn.push_back(i);
        }
        if (a[i] == mx) {
            vmx.push_back(i);
        }
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int posmn = upper_bound(vmn.begin(), vmn.end(), i) - vmn.begin() - 1;
        int posmx = upper_bound(vmx.begin(), vmx.end(), i) - vmx.begin() - 1;
        if (posmn == -1 || posmx == -1) {
            continue;
        }
        int dist = min(vmn[posmn], vmx[posmx]);
        ans += dist + 1;
    }
    cout << ans;
    return 0;
}
