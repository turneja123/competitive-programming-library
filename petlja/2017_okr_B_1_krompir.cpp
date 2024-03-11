#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

bool hor[N];
bool ver[N];


int main() {
    IOS;
    ll n, m;
    cin >> n >> m;
    ll ctx = 0, cty = 0;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        if (!hor[x]) {
            hor[x] = true;
            ctx++;
        }
        if (!ver[y]) {
            ver[y] = true;
            cty++;
        }
    }
    ll ans = n * ctx + (n - ctx) * cty;
    cout << ans;
    return 0;
}
