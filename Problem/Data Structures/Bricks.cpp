//https://ocpc2025s.eolymp.space/en/compete/ejd99p3q1p1tnem8befqm7318o/problem/4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int SQ = 450;

vector<int> his_last[N];
vector<int> colors[N];
vector<int> g[N];

set<int> st[N];
string out[N];

int main() {
    IOS;
    int n, m, q;
    cin >> n >> m;
    vector<pair<int, int>> all;
    for (int i = 0; i < n; i++) {
        int s, c;
        cin >> s >> c;
        c--;
        colors[c].push_back(s);
        all.push_back({s, c});
    }
    sort(all.begin(), all.end());
    for (int i = 0; i < m; i++) {
        sort(colors[i].begin(), colors[i].end());
    }
    priority_queue<tuple<int, int, int, int>> pq;
    for (int i = 0; i < m; i++) {
        his_last[i].resize(colors[i].size(), 0);
        his_last[i][0] = -1;
        for (int j = 1; j < colors[i].size(); j++) {
            his_last[i][j] = colors[i][j - 1];
            g[i].push_back(colors[i][j] - colors[i][j - 1]);
            pq.push({colors[i][j] - colors[i][j - 1], j, j - 1, i});
        }
        st[i].insert(0);
        st[i].insert(colors[i].size() - 1);
        if (g[i].size()) {
            sort(g[i].begin(), g[i].end());
        }
    }
    map<pair<int, int>, int> mp;
    cin >> q;
    vector<tuple<int, int, int, int>> queries;
    for (int i = 0; i < q; i++) {
        int u, v, k;
        cin >> k >> u >> v;
        u--, v--;
        queries.push_back({k, u, v, i});
    }
    sort(queries.begin(), queries.end());
    reverse(queries.begin(), queries.end());
    for (int i = 0; i < q; i++) {
        auto [k, u, v, ind] = queries[i];
        while (pq.size() && get<0>(pq.top()) > k) {
            auto [_, j1, j2, c] = pq.top();
            st[c].insert(j1);
            st[c].insert(j2);
            pq.pop();

        }
        if (colors[u].size() > colors[v].size()) {
            swap(u, v);
        }
        auto it = mp.find({u, v});
        if (it != mp.end()) {
            if (it->second <= k) {
                out[ind] = "YES";
            } else {
                out[ind] = "NO";
            }
            continue;
        }
        if (colors[u].size() < SQ && colors[v].size() >= SQ) {
            int p = (int)g[v].size() - (upper_bound(g[v].begin(), g[v].end(), k) - g[v].begin());
            if (p > colors[u].size() + 5) {
                out[ind] = "NO";
                continue;
            }
            int i = 0; auto j = st[v].begin();
            int ans = 0;
            int last = -1;
            while (i < colors[u].size() || j != st[v].end()) {
                if (j == st[v].end()) {
                    int r = upper_bound(colors[v].begin(), colors[v].end(), colors[u][i]) - colors[v].begin() - 1;
                    if (r != -1) {
                        r = colors[v][r];
                    }
                    if (max(last, r) != -1) {
                        ans = max(ans, colors[u][i] - max(last, r));
                    }
                    last = colors[u][i];
                    i++;
                } else if (i == colors[u].size()) {
                    if (max(last, his_last[v][*j]) != -1) {
                        ans = max(ans, colors[v][*j] - max(last, his_last[v][*j]));
                    }
                    last = colors[v][*j];
                    j++;
                } else if (colors[u][i] < colors[v][*j]) {
                    int r = upper_bound(colors[v].begin(), colors[v].end(), colors[u][i]) - colors[v].begin() - 1;
                    if (r != -1) {
                        r = colors[v][r];
                    }
                    if (max(last, r) != -1) {
                        ans = max(ans, colors[u][i] - max(last, r));
                    }
                    last = colors[u][i];
                    i++;
                } else {
                    if (max(last, his_last[v][*j]) != -1) {
                        ans = max(ans, colors[v][*j] - max(last, his_last[v][*j]));
                    }
                    last = colors[v][*j];
                    j++;
                }
                if (ans > k) {
                    break;
                }
            }
            //cout << ans << " " << k << endl;
            if (ans <= k) {
                out[ind] = "YES";
            } else {
                out[ind] = "NO";
            }
            continue;
        } else {
            int i = 0, j = 0;
            int ans = 0;
            int last = -1;
            while (i < colors[u].size() || j < colors[v].size()) {
                if (j == colors[v].size()) {
                    if (last != -1) {
                        ans = max(ans, colors[u][i] - last);
                    }
                    last = colors[u][i];
                    i++;
                } else if (i == colors[u].size()) {
                    if (last != -1) {
                        ans = max(ans, colors[v][j] - last);
                    }
                    last = colors[v][j];
                    j++;
                } else if (colors[u][i] < colors[v][j]) {
                    if (last != -1) {
                        ans = max(ans, colors[u][i] - last);
                    }
                    last = colors[u][i];
                    i++;
                } else {
                    if (last != -1) {
                        ans = max(ans, colors[v][j] - last);
                    }
                    last = colors[v][j];
                    j++;
                }
            }
            mp[{u, v}] = ans;
        }


        if (mp[{u, v}] <= k) {
            out[ind] = "YES";
        } else {
            out[ind] = "NO";
        }

    }
    for (int i = 0; i < q; i++) {
        cout << out[i] << endl;
    }

    return 0;
}
