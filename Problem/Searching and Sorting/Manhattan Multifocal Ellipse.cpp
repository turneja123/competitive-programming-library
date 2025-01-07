//https://atcoder.jp/contests/abc366/tasks/abc366_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int M = 4e6 + 5;

int x[N], y[N];
long long prefx[N], prefy[N];

int main() {
    IOS;
    int n, d;
    cin >> n >> d;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        x[i] += 2e6, y[i] += 2e6;
    }
    sort(x, x + n);
    sort(y, y + n);
    for (int i = 0; i < n; i++) {
        prefx[i] = (i == 0 ? x[i] : prefx[i - 1] + x[i]);
        prefy[i] = (i == 0 ? y[i] : prefy[i - 1] + y[i]);
    }
    vector<int> v;
    for (int i = 0; i < M; i++) {
        int j = upper_bound(y, y + n, i) - y - 1;
        long long cost = (j == -1 ? 0 : (long long)i * (j + 1) - prefy[j]) + (prefy[n - 1] - (j == -1 ? 0 : prefy[j]) - (long long)i * (n - j - 1));
        if (cost <= d) {
            v.push_back(cost);

        }
    }
    sort(v.begin(), v.end());
    long long ans = 0;
    for (int i = 0; i < M; i++) {
        int j = upper_bound(x, x + n, i) - x - 1;
        long long cost = (j == -1 ? 0 : (long long)i * (j + 1) - prefx[j]) + (prefx[n - 1] - (j == -1 ? 0 : prefx[j]) - (long long)i * (n - j - 1));
        if (cost <= d) {
            int need = d - cost;
            int k = upper_bound(v.begin(), v.end(), need) - v.begin() - 1;
            ans += k + 1;
        }
    }
    cout << ans;
    return 0;

}
