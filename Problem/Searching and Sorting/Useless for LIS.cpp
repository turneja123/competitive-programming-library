//https://atcoder.jp/contests/abc354/tasks/abc354_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9 + 2;

int a[N];
int dp[N];
vector<int> pos[N];
vector<int> suf[N];
vector<int> mark;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            dp[i + 1] = INF;
        }
        int ans = 1;
        dp[1] = a[0];
        pos[1].push_back(0);
        for (int i = 1; i < n; i++) {
            int l = 1, r = n, mx = 0;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (dp[mid] < a[i]) {
                    l = mid + 1;
                    mx = mid;
                } else {
                    r = mid - 1;
                }
            }
            dp[mx + 1] = min(dp[mx + 1], a[i]);
            ans = max(ans, mx + 1);
            pos[mx + 1].push_back(i);
        }
        suf[ans].resize(pos[ans].size());

        for (int j = pos[ans].size() - 1; j >= 0; j--) {
            int ind = pos[ans][j];
            mark.push_back(ind);
            if (j == pos[ans].size() - 1) {
                suf[ans][j] = a[ind];
            } else {
                suf[ans][j] = max(suf[ans][j + 1], a[ind]);
            }
        }
        for (int i = ans - 1; i > 0; i--) {
            assert(pos[i + 1].size() > 0);
            vector<int> next_pos;
            for (int j = pos[i].size() - 1; j >= 0; j--) {
                int ind = pos[i][j];
                int r = upper_bound(pos[i + 1].begin(), pos[i + 1].end(), ind) - pos[i + 1].begin();
                if (r == suf[i + 1].size() || suf[i + 1][r] <= a[ind]) {
                    continue;
                } else {
                    next_pos.push_back(ind);
                    mark.push_back(ind);
                }
            }
            pos[i] = next_pos;
            suf[i].resize(pos[i].size());
            reverse(pos[i].begin(), pos[i].end());
            for (int j = pos[i].size() - 1; j >= 0; j--) {
                int ind = pos[i][j];
                if (j == pos[i].size() - 1) {
                    suf[i][j] = a[ind];
                } else {
                    suf[i][j] = max(suf[i][j + 1], a[ind]);
                }
            }
        }
        sort(mark.begin(), mark.end());
        cout << mark.size() << endl;
        for (int i : mark) {
            cout << i + 1 << " ";
        }
        cout << endl;
        mark.clear();
        for (int i = 0; i <= n; i++) {
            pos[i].clear();
            suf[i].clear();

        }
    }
    return 0;
}
