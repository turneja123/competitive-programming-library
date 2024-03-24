//https://dmoj.ca/problem/rte16s2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2505;

set<pair<int, int>> dp[N];
string s[4];
string a;

vector<pair<int, int>> d{make_pair(0, 1), make_pair(0, -1), make_pair(1, 0), make_pair(-1, 0)};

int main() {
    IOS;
    for (int i = 0; i < 4; i++) {
        cin >> s[i];
    }
    cin >> a;
    int n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            int l = i - s[j].size() + 1;
            if (l >= 0 && l + s[j].size() <= n) {
                string c = a.substr(l, s[j].size());
                if (c == s[j]) {
                    if (l == 0) {
                        dp[i].insert(d[j]);
                    } else {
                        for (auto it = dp[l - 1].begin(); it != dp[l - 1].end(); ++it) {
                            pair<int, int> ins = *it;
                            ins.first += d[j].first;
                            ins.second += d[j].second;
                            dp[i].insert(ins);
                        }
                    }
                }
            }
        }
    }
    cout << dp[n - 1].size();
    return 0;
}
