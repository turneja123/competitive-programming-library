//https://www.spoj.com/problems/LNTILING/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 105;
const int K = 50005;

vector<char> a;
vector<vector<char>> x;

map<char, char> mp;

int dp[N][K];

vector<int> masks[N];

bool test(vector<char> v, int j) {
    int x = 0, y = 0;
    vector<pair<int, int>> coord;
    coord.push_back(make_pair(x, y));
    for (int i = 1; i < v.size(); i++) {
        if (a[i + j] == 'R') {
            x++;
        } else if (a[i + j] == 'L') {
            x--;
        } else if (a[i + j] == 'U') {
            y++;
        } else {
            y--;
        }
        coord.push_back(make_pair(x, y));
    }
    x = 0, y = 0;
    int k = 0;
    for (int i = 1; i < v.size(); i++) {
        if (v[i] == 'R') {
            x++;
        } else if (v[i] == 'L') {
            x--;
        } else if (v[i] == 'U') {
            y++;
        } else {
            y--;
        }
        if (x != coord[i].first || y != coord[i].second) {
            break;
        }
        k++;
    }
    if (k == v.size() - 1) {
        return true;
    }
    x = coord[v.size() - 1].first, y = coord[v.size() - 1].second;

    for (int i = 1; i < v.size(); i++) {
        if (v[i] == 'R') {
            x++;
        } else if (v[i] == 'L') {
            x--;
        } else if (v[i] == 'U') {
            y++;
        } else {
            y--;
        }
        if (x != coord[v.size() - 1 - i].first || y != coord[v.size() - 1 - i].second) {
            return false;
        }
    }
    return true;
}

int main() {
    IOS;
    mp['R'] = 'D';
    mp['D'] = 'L';
    mp['L'] = 'U';
    mp['U'] = 'R';
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n;
        for (int i = 0; i < n; i++) {
            char c; int k;
            cin >> c >> k;
            for (int j = 0; j < k; j++) {
                a.push_back(c);
            }
        }
        cin >> m;
        for (int p = 0; p < m; p++) {
            int ct, n;
            cin >> ct >> n;
            vector<char> v;
            for (int i = 0; i < n; i++) {
                char c; int k;
                cin >> c >> k;
                for (int j = 0; j < k; j++) {
                    v.push_back(c);
                }
            }
            for (int i = 0; i < ct; i++) {
                x.push_back(v);
            }
        }
        n = a.size(), m = x.size();
        for (int mask = 1; mask < 1 << m; mask++) {
            int bits = 0;
            for (int j = 0; j < m; j++) {
                int c = mask & (1 << j);
                if (c) {
                    bits += x[j].size();
                }
            }
            masks[bits - 1].push_back(mask);
        }
        for (int i = 0; i < n; i++) {
            for (int mask : masks[i]) {
                for (int j = 0; j < m; j++) {
                    int c = mask & (1 << j);
                    if (!c || x[j].size() > i + 1) {
                        continue;
                    }
                    int prev, s = i - x[j].size();
                    if (s < 0) {
                        if (__builtin_popcount(mask) == 1) {
                            prev = 1;
                        } else {
                            prev = 0;
                        }
                    } else {
                        int sub = mask ^ (1 << j);
                        prev = dp[s][mask ^ (1 << j)];
                    }
                    if (!prev) {
                        continue;
                    }

                    vector<char> v = x[j];
                    bool can = false;
                    for (int k = 0; k < 4 && !can; k++) {
                        can |= test(v, i - v.size() + 1);
                        for (int y = 0; y < v.size(); y++) {
                            v[y] = mp[v[y]];
                        }
                    }
                    if (can) {
                        dp[i][mask] = 1;
                        //cout << i << " " << mask << endl;
                    }

                }
            }
        }
        string ans = "NO";
        for (int mask = 0; mask < 1 << m; mask++) {
            if (dp[n - 1][mask]) {
                ans = "YES";
            }
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            for (int mask = 0; mask < 1 << m; mask++) {
                dp[i][mask] = 0;
            }
            masks[i].clear();
        }
        x.clear();
        a.clear();

    }

    return 0;
}
