//https://arena.petlja.org/sr-Latn-RS/competition/bubblecup17finals#tab_136727
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;
int x[N];

int main() {
    IOS;
    int n, a, b;
    cin >> n >> a >> b;
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    int l = 1, r = 1e9, ans = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        vector<long long> cur(x, x + n);
        for (int i = 0; i < n; i++) {
            cur[i] -= (long long)b * mid;
        }
        long long cost = 0;
        if (a == b) {
            for (int i = 0; i < n; i++) {
                if (cur[i] > 0) {
                    cost = mid + 1;
                }
            }
        } else {
            for (int i = 0; i < n; i++) {
                if (cur[i] > 0) {
                    cost += cur[i] / (a - b);
                    if (cur[i] % (a - b)) {
                        cost++;
                    }
                }
            }
        }
        if (cost <= mid) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans;
    return 0;
}
