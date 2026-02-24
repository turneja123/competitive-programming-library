//https://qoj.ac/contest/3347/problem/17159
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1 << 20;

ll dp[N];
ll dp_sos[N];
ll dp_one[N];
ll dp_fin[N];

vector<pair<int, int>> v[N];
vector<int> add[2 * N], rem[2 * N];

int main() {
    IOS;
    int k, n, m;
    cin >> k >> n >> m;
    vector<int> compr{1, k + 1};
    for (int i = 0; i < n; i++) {
        int s;
        cin >> s;
        v[i].resize(s);
        for (int j = 0; j < s; j++) {
            int l, r;
            cin >> l >> r;
            r++;
            compr.push_back(l);
            compr.push_back(r);
            v[i][j] = {l, r};
        }
    }
    sort(compr.begin(), compr.end());
    compr.erase(unique(compr.begin(), compr.end()), compr.end());


    for (int i = 0; i < n; i++) {
        for (auto [l, r] : v[i]) {
            int L = lower_bound(compr.begin(), compr.end(), l) - compr.begin();
            int R = lower_bound(compr.begin(), compr.end(), r) - compr.begin();
            add[L].push_back(i);
            rem[R].push_back(i);
        }
    }
    for (int i = 0, j = 0; i < compr.size(); i++) {
        dp[j] += (i == 0 ? 0 : compr[i] - compr[i - 1]);
        for (int k : rem[i]) {
            j ^= 1 << k;
        }
        for (int k : add[i]) {
            j ^= 1 << k;
        }
    }
    for (int j = 0; j < 1 << n; j++) {
        dp_sos[j] = dp[j];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 1 << n; j++) {
            int c = (1 << i) & j;
            if (c) {
                dp_sos[j] += dp_sos[j ^ (1 << i)];
            }
        }
    }
    for (int j = 0; j < 1 << n; j++) {
        dp_fin[j] = k - dp_sos[((1 << n) - 1) ^ j];
    }
    for (int b = 0; b < n; b++) {
        for (int j = 0; j < 1 << n; j++) {
            int c = (1 << b) & j;
            if (!c) {
                continue;
            }
            dp_one[j ^ (1 << b)] = dp[j];
        }
        for (int i = 0; i < n; i++) {
            if (i == b) {
                continue;
            }
            for (int j = 0; j < 1 << n; j++) {
                int c = (1 << b) & j;
                if (c) {
                    continue;
                }
                c = (1 << i) & j;
                if (c) {
                    dp_one[j] += dp_one[j ^ (1 << i)];
                }
            }
        }
        for (int j = 0; j < 1 << n; j++) {
            int c = (1 << b) & j;
            if (c) {
                continue;
            }
            int comple = ((1 << n) - 1) ^ (1 << b) ^ j;
            dp_fin[j ^ (1 << b)] -= dp_one[comple];

        }
    }
    int ans = 0;
    for (int i = 0; i < 1 << n; i++) {
        ans += dp_fin[i] >= m;
    }
    cout << ans;

    return 0;
}
