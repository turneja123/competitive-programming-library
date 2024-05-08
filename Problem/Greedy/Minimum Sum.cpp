//https://www.spoj.com/problems/SQRMINSUM/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e4 + 5;

int sq[N];

int main() {
    IOS;
    for (int i = 1; i < N; i++) {
        sq[i] = sqrt(i);
    }
    int t;
    cin >> t;
    while (t--) {
        int l, k;
        cin >> l >> k;
        vector<int> freq(l + 1, 1);
        int ans = l * (l + 1) / 2, r = l;
        for (int i = 1; i <= k; i++) {
            while (freq[r] == 0) {
                r--;
            }
            ans += sq[r] - r;
            freq[sq[r]]++, freq[r]--;
        }
        cout << ans << endl;
    }
    return 0;
}
