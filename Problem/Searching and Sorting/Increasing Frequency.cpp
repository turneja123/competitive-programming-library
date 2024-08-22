//https://codeforces.com/contest/1082/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int pref[N];
vector<int> pos[N];

int max_subarray(vector<int> &a) {
    int best = 0, cur = 0;
    for (int i = 0; i < a.size(); i++) {
        cur = max({a[i], cur + a[i], 1});
        best = max(best, cur);
    }
    return best;
}

int main() {
    IOS;
    int n, c, ct = 0;
    cin >> n >> c;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if (a == c) {
            ct++;
        }
        pos[a].push_back(i);
        pref[i] = ct;
    }
    int ans = ct;
    for (int i = 0; i < N; i++) {
        if (i == c || pos[i].empty()) {
            continue;
        }
        vector<int> a{1};
        for (int j = 1; j < pos[i].size(); j++) {
            a.push_back(1 - (pref[pos[i][j]] - pref[pos[i][j - 1]]));
        }
        ans = max(ans, ct + max_subarray(a));
    }
    cout << ans;

    return 0;
}
