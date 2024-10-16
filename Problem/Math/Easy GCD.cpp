//https://www.spoj.com/problems/GCDEASY/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int a[N];

void get_divs(int i, int cur, vector<pair<int, int>> &f, vector<int> &divs) {
    if (i == f.size()) {
        divs.push_back(cur);
        return;
    }
    for (int j = 0; j <= f[i].second; j++) {
        get_divs(i + 1, cur, f, divs);
        cur *= f[i].first;
    }
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int g = a[0];
        for (int i = 1; i < n; i++) {
            g = __gcd(g, a[i]);
        }
        int ans = (k / g) * g;
        vector<pair<int, int>> f;
        int sq = sqrt(g);
        for (int i = 2; i <= sq; i++) {
            if (g % i == 0) {
                int e = 0;
                while (g % i == 0) {
                    e++;
                    g /= i;
                }
                f.push_back(make_pair(i, e));
            }
        }
        if (g > 1) {
            f.push_back(make_pair(g, 1));
        }
        vector<int> divs;
        get_divs(0, 1, f, divs);
        for (int d : divs) {
            if (d == 1) {
                continue;
            }
            ans = max(ans, (k / d) * d);
        }
        cout << ans << endl;
    }

    return 0;
}
