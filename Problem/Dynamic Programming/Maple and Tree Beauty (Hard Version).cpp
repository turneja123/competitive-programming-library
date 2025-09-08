//https://codeforces.com/contest/2138/problem/C2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;


int pref[N];
int level[N];
int depth[N];
vector<int> adj[N];
int m;

bitset<N> ans;

void dfs(int u) {
    level[depth[u]]++;
    if (adj[u].empty()) {
        m = min(m, depth[u]);
    }
    for (int v : adj[u]) {
        depth[v] = depth[u] + 1;
        dfs(v);
    }
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 1; i < n; i++) {
            int p;
            cin >> p;
            p--;
            adj[p].push_back(i);
        }
        m = n;
        dfs(0);
        ans[0] = 1;
        ans[1] = 1;
        int best = 1, sum = 1;
        vector<pair<int, bitset<N>>> buffer;
        for (int i = 1; i <= m; i++) {
            sum += level[i];
            ans |= (ans << level[i]);
            pref[i] = sum;

            if (i % 64 == 0) {
                for (int j = max(0, sum - n + k); j <= min(k, sum); j++) {
                    if (ans[j]) {
                        best = i + 1;
                        break;
                    }
                }
                if (best != i + 1) {
                    for (int p = 0; p < buffer.size(); p++) {
                        int sum = pref[buffer[p].first];
                        bitset<N> b = buffer[p].second;
                        for (int j = max(0, sum - n + k); j <= min(k, sum); j++) {
                            if (b[j]) {
                                best = max(best, buffer[p].first + 1);
                                break;
                            }
                        }
                    }
                    break;
                }
                buffer.clear();
            } else {
                buffer.push_back({i, ans});
            }
        }
        for (int p = 0; p < buffer.size(); p++) {
            int sum = pref[buffer[p].first];
            bitset<N> b = buffer[p].second;
            for (int j = max(0, sum - n + k); j <= min(k, sum); j++) {
                if (b[j]) {
                    best = max(best, buffer[p].first + 1);
                    break;
                }
            }
        }
        cout << best << endl;
        for (int i = 0; i <= n; i++) {
            adj[i].clear();
            ans[i] = 0;
            level[i] = 0;
        }
    }

    return 0;
}
