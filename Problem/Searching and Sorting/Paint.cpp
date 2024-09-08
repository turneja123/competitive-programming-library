//https://atcoder.jp/contests/abc346/tasks/abc346_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

long long ans[N];
bool r[N], c[N];

tuple<int, int, int> queries[N];

int main() {
    IOS;
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < q; i++) {
        int t, a, k;
        cin >> t >> a >> k;
        queries[i] = make_tuple(t, a, k);
    }
    int x = 0, y = 0;
    for (int i = q - 1; i >= 0; i--) {
        int t = get<0>(queries[i]), a = get<1>(queries[i]), k = get<2>(queries[i]);
        if (t == 1) {
            if (r[a]) {
                continue;
            }
            r[a] = true;
            ans[k] += m - x;
            y++;
        } else {
            if (c[a]) {
                continue;
            }
            c[a] = true;
            ans[k] += n - y;
            x++;
        }
    }
    long long tot = (long long)n * m - ans[0];
    int ct = 0;
    for (int i = 1; i < N; i++) {
        if (ans[i] > 0) {
            ct++;
            tot -= ans[i];
        }
    }
    ans[0] += tot;
    if (ans[0] > 0) {
        ct++;
    }
    cout << ct << endl;
    for (int i = 0; i < N; i++) {
        if (ans[i] > 0) {
            cout << i << " " << ans[i] << endl;
        }
    }
    return 0;
}
