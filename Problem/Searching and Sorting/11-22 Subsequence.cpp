//https://atcoder.jp/contests/abc381/tasks/abc381_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int pref[2][N];

vector<int> pos;

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    for (int i = 0; i < n; i++) {
        if (i != 0) {
            pref[0][i] += pref[0][i - 1];
            pref[1][i] += pref[1][i - 1];
        }
        pref[0][i] += s[i] == '1';
        pref[1][i] += s[i] == '2';
        if (s[i] == '/') {
            pos.push_back(i);
        }
    }
    for (int i = 0; i < q; i++) {
        int lq, rq;
        cin >> lq >> rq;
        lq--, rq--;
        int l = lower_bound(pos.begin(), pos.end(), lq) - pos.begin();
        int r = upper_bound(pos.begin(), pos.end(), rq) - pos.begin() - 1;
        int s = r - l + 1, lbin = 0, rbin = s - 1, ans = 0;
        while (lbin <= rbin) {
            int mid = (lbin + rbin) / 2, ind = pos[l + mid];
            int ctl = pref[0][ind] - (lq == 0 ? 0 : pref[0][lq - 1]);
            int ctr = pref[1][rq] - pref[1][ind];
            ans = max(ans, 2 * min(ctl, ctr) + 1);
            if (ctl < ctr) {
                lbin = mid + 1;
            } else {
                rbin = mid - 1;
            }
        }
        cout << ans << endl;
    }


    return 0;
}
