//https://www.spoj.com/problems/BOXSCHOC/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 100005;
const int SQ = sqrt(N);

long long arr[N];

vector<int> v[N];
vector<long long> pref[N];

int main() {
    IOS;
    int t, ct = 1;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            for (int j = 1; j <= sqrt(arr[i]); j++) {
                if (j == sqrt(arr[i])) {
                    if (j * j == arr[i]) {
                        v[j].push_back(i);
                    }
                } else {
                    if (arr[i] % j == 0) {
                        v[j].push_back(i);
                        v[arr[i] / j].push_back(i);
                    }
                }
            }
        }
        for (int i = 1; i < N; i++) {
            long long sum = 0;
            for (int j = 0; j < v[i].size(); j++) {
                sum += 1;
                pref[i].push_back(sum);
            }
        }
        cin >> q;
        cout << "Case " << ct++ << ":" << endl;
        for (int i = 0; i < q; i++) {
            int l, r, k;
            cin >> l >> r >> k;
            l--, r--;
            if (v[k].size() == 0) {
                cout << 0 << endl;
            } else {
                long long ans = 0;
                int rq = upper_bound(v[k].begin(), v[k].end(), r) - v[k].begin() - 1;
                if (rq == -1) {
                    cout << 0 << endl;
                    continue;
                }
                ans += pref[k][rq];
                int lq = lower_bound(v[k].begin(), v[k].end(), l) - v[k].begin() - 1;
                if (lq >= 0) {
                    ans -= pref[k][lq];
                }
                cout << ans << endl;
            }
        }
        for (int i = 0; i < N; i++) {
            v[i].clear();
            pref[i].clear();
        }
    }
}
