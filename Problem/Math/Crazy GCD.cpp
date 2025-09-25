//https://basecamp.eolymp.com/en/problems/12230
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;
const int INF = 2e9;

vector<pair<int, int>> v[N];
int val[N * N];
int seen[N * N];
int e[N * N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        map<int, int> mp;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            v[i].clear();
            int s = sqrt(a);
            for (int j = 2; j <= s; j++) {
                if (a % j != 0) {
                    continue;
                }
                int e = 0;
                while (a % j == 0) {
                    e++;
                    a /= j;
                }
                auto it = mp.find(j);
                if (it == mp.end()) {
                    val[mp.size()] = j;
                    mp[j] = mp.size();
                }
                v[i].push_back({mp[j], e});
            }
            if (a > 1) {
                auto it = mp.find(a);
                if (it == mp.end()) {
                    val[mp.size()] = a;
                    mp[a] = mp.size();
                }
                v[i].push_back({mp[a], 1});
            }
        }

        int ans = 1;
        for (int k = 1; k <= n; k++) {
            int mn = INF;
            for (int i = 0; i < k; i++) {
                vector<int> restore;
                int m = 0;
                for (int j = i; j < n; j += k) {
                    m++;
                    for (int z = 0; z < v[j].size(); z++) {
                        if (!seen[v[j][z].first]) {
                            seen[v[j][z].first] = true;
                            restore.push_back(v[j][z].first);
                        }
                        e[v[j][z].first] += v[j][z].second;
                    }
                }
                int cur = 1;
                for (int j : restore) {
                    int p = 1, ct = e[j] / m;
                    for (int z = 0; z < ct; z++) {
                        p *= val[j];
                    }
                    cur *= p;
                    seen[j] = false;
                    e[j] = 0;
                }
                mn = min(mn, cur);
            }
            ans = max(ans, mn);
        }
        cout << ans << endl;
    }
    return 0;
}
