//https://atcoder.jp/contests/abc391/tasks/abc391_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;
const long long M = 998244353;

int ans[N];

map<vector<int>, long long> mp[N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    vector<int> v(n, 0);

    mp[0][v] = 1;


    for (int i = 0; i < m; i++) {
        for (auto it : mp[i]) {
            vector<int> v = it.first;
            for (int c = 0; c < 26; c++) {
                char cc = 'a' + c;
                vector<int> nw = v;
                for (int j = 0; j < n; j++) {
                    if (s[j] == cc) {
                        if (j == 0) {
                            nw[j] = 1;
                        } else {
                            nw[j] = v[j - 1] + 1;
                        }
                    }
                }
                int mx = 0;
                for (int j = 0; j < n; j++) {
                    nw[j] = max(nw[j], mx);
                    mx = max(mx, nw[j]);
                }
                mp[i + 1][nw] = (mp[i + 1][nw] + it.second) % M;
            }
        }
    }
    for (auto it : mp[m]) {
        int mx = 0;
        for (int j = 0; j < n; j++) {
            mx = max(mx, it.first[j]);
        }
        ans[mx] = (ans[mx] + it.second) % M;
    }
    for (int i = 0; i <= n; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
