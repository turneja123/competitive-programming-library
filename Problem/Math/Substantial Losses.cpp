//https://www.facebook.com/codingcompetitions/hacker-cup/2024/round-1/problems/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 998244353;

int main() {
    IOS;
    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        long long w, g, l;
        cin >> w >> g >> l;
        l %= M, w %= M, g %= M;
        long long ans = (2 * l + 1) % M * (w - g + M) % M;
        cout << "Case #" << tt << ": " << ans << endl;
    }
    return 0;

}
