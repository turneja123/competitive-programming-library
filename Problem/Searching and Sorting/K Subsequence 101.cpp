//https://www.codechef.com/problems/REMK
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int MAX = 55;

int a[N];
int pref[MAX][N];
vector<int> pos[N];

int get(int l, int r, int j) {
    int sum = pref[j][r];
    if (l != 0) {
        sum -= pref[j][l - 1];
    }
    return sum;
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
            pos[a[i]].push_back(i);
            pref[a[i]][i]++;
            if (i != 0) {
                for (int j = 0; j < MAX; j++) {
                    pref[j][i] += pref[j][i - 1];
                }
            }
        }
        int ans = 0;
        for (int l = 1; l < MAX; l++) {
            for (int r = 1; r < MAX; r++) {
                if (pos[l].empty() || pos[r].empty()) {
                    continue;
                }
                if (pos[l][0] == pos[r][pos[r].size() - 1]) {
                    continue;
                }
                int cur = l + r, m = k - 2;
                for (int j = MAX - 1; j > 0 && m > 0; j--) {
                    int ct = get(pos[l][0] + 1, pos[r][pos[r].size() - 1] - 1, j);
                    cur += min(ct, m) * j * 2;
                    m -= min(ct, m);
                }
                if (m == 0) {
                    ans = max(ans, cur);
                }
            }
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < MAX; j++) {
                pref[j][i] = 0;
            }
        }
        for (int j = 0; j < MAX; j++) {
            pos[j].clear();
        }

    }

    return 0;
}
