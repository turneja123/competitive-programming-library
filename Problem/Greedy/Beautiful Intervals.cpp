//https://codeforces.com/contest/2162/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int b[N];
int ans[N];
pair<int, int> ival[N];

void add(vector<int> &d, int l, int r) {
    d[l]++;
    d[r + 1]--;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> diff(n + 1, 0);
        for (int i = 0; i < m; i++) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            ival[i] = {l, r};
            add(diff, l, r);
        }
        int s = 0, j = -1;
        for (int i = 0; i < n; i++) {
            s += diff[i];
            a[i] = s;
            if (a[i] == m) {
                j = i;
            }
        }
        if (j != -1) {
            ans[j] = 0;
            for (int i = 0, ct = 1; i < n; i++) {
                if (i == j) {
                    continue;
                }
                ans[i] = ct++;
            }
            for (int i = 0; i < n; i++) {
                cout << ans[i] << " ";
            }
            cout << endl;
            continue;
        }
        int p0 = -1, p1 = -1;
        for (int i = 0; i < n; i++) {
            int l = 0, r = n - 1;
            for (int j = 0; j < m; j++) {
                auto [lq, rq] = ival[j];
                if (i >= lq && i <= rq) {
                    l = max(lq, l);
                    r = min(rq, r);
                }
            }
            if (r - l > 0) {
                if (l == i) {
                    l++;
                }
                p0 = i, p1 = l;
                break;
            } else if (r == l && r != i) {
                p0 = i, p1 = l;
                break;
            }
        }
        if (p0 == -1) {
            p0 = 0, p1 = n - 1;
        }
        ans[p0] = 0, ans[p1] = 1;
        for (int i = 0, ct = 2; i < n; i++) {
            if (i == p0 || i == p1) {
                continue;
            }
            ans[i] = ct++;
        }
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }

  return 0;
}
