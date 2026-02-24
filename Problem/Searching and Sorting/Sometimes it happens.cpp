//https://eolymp.com/en/compete/qn51qrti910ch6lpn4ju3memsk/problem/5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

vector<int> bad[N];
vector<int> ok[N];
int a[N];

int main() {
    IOS;
    int n, k, q;
    cin >> n >> k >> q;
    vector<int> pos;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] == 0) {
            pos.push_back(i);
        }
    }
    for (int i = 0; i + k - 1 < pos.size(); i++) {

        int l = pos[i], r = pos[i + k - 1];
        if (r - l + 1 > 2 * k) {
            bad[i % k].push_back(i);
        }
        int far_l = (i == 0 ? -1 : pos[i - 1]);
        int far_r = (i + k - 1 == pos.size() - 1 ? n : pos[i + k]);
        if (far_r - far_l - 1 >= 2 * k) {
            ok[i % k].push_back(i);
        }

    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        int L = lower_bound(pos.begin(), pos.end(), l) - pos.begin();
        int R = upper_bound(pos.begin(), pos.end(), r) - pos.begin() - 1;
        int m = R - L + 1;
        if (m % k != 0) {
            cout << "NO" << endl;
            continue;
        }
        if (m == 0) {
            cout << "YES" << endl;
            continue;
        }
        auto j = lower_bound(bad[L % k].begin(), bad[L % k].end(), L);
        if (j != bad[L % k].end() && *j <= R) {
            cout << "NO" << endl;
            continue;
        }
        string ans = "NO";

        if (m >= 3 * k) {
            auto it = lower_bound(ok[L % k].begin(), ok[L % k].end(), L + k);
            if (it != ok[L % k].end() && *it <= R - 2 * k + 1) {
                ans = "YES";
            }
        }

        int far_l = l - 1;
        int far_r = min(r + 1, (L + k == pos.size() ? n : pos[L + k]));
        if (far_r - far_l - 1 >= 2 * k) {
            ans = "YES";
        }
        far_l = max(l - 1, (R - k == -1 ? -1 : pos[R - k]));
        far_r = r + 1;
        if (far_r - far_l - 1 >= 2 * k) {
            ans = "YES";
        }
        cout << ans << endl;
    }


    return 0;
}
