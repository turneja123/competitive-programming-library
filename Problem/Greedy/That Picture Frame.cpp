//https://ocpc2026w.eolymp.space/en/compete/7ds15ifh194hve0pf1tgf05pqs/problem/1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> widths[N];

int main() {
    IOS;
    int n, h, w;
    cin >> n >> h >> w;
    vector<int> compr;
    vector<pair<int, int>> items;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        compr.push_back(x);
        items.push_back({x, y});
    }
    sort(compr.begin(), compr.end());
    compr.erase(unique(compr.begin(), compr.end()), compr.end());
    for (auto [x, y] : items) {
        int x_c = lower_bound(compr.begin(), compr.end(), x) - compr.begin();
        widths[x_c].push_back(y);
    }
    string ans = "SAGET";
    for (int i = n - 1; i >= 0; i--) {
        if (widths[i].empty()) {
            continue;
        }
        sort(widths[i].begin(), widths[i].end(), greater<int>());
        for (int j = 0; j < widths[i].size(); j++) {
            if (j + widths[i][j] > w) {
                ans = "MBOTEN";
            }
        }
    }
    cout << ans;

    return 0;
}
