//https://atcoder.jp/contests/abc393/tasks/abc393_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

int main() {
    IOS;
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> pos;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            pos.push_back(i);
        }
    }
    int m = pos.size();
    int mid = pos[(m - 1) / 2];
    int j = mid - ((m - 1) / 2);
    for (int i = 0; i < m; i++, j++) {
        ans += abs(pos[i] - j);
    }
    cout << ans;
    return 0;
}
