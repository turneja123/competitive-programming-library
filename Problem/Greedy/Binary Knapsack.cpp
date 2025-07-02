//https://atcoder.jp/contests/arc201/tasks/arc201_b
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 60;

vector<long long> c[K];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n; long long w;
        cin >> n >> w;
        for (int i = 0; i < n; i++) {
            int k, y;
            cin >> k >> y;
            c[k].push_back(y);
        }
        long long ans = 0;
        for (int i = 0; i < K; i++) {
            if (c[i].empty()) {
                continue;
            }
            sort(c[i].begin(), c[i].end(), greater<long long>());
            long long b = (1ll << i) & w;
            int j = 0;
            if (b) {
                ans += c[i][0];
                j = 1;
            }
            while (i < K - 1 && j < c[i].size()) {
                c[i + 1].push_back(c[i][j] + (j == c[i].size() - 1 ? 0 : c[i][j + 1]));
                j += 2;
            }
            c[i].clear();
        }
        cout << ans << endl;
    }
    return 0;
}

