//https://codeforces.com/contest/1651/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;

pair<int, int> a[N];
map<pair<int, int>, int> mp;
int dist[N];
pair<int, int> ans[N];
vector<int> adj[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        mp[a[i]] = i;
        dist[i] = N;
    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (abs(dx) + abs(dy) != 1) {
                    continue;
                }
                auto it = mp.find(make_pair(a[i].first + dx, a[i].second + dy));
                if (dist[i] > 1 && it == mp.end()) {
                    dist[i] = 1;
                    q.push(i);
                    ans[i] = make_pair(a[i].first + dx, a[i].second + dy);
                } else {
                    adj[i].push_back(it->second);
                    adj[it->second].push_back(i);
                }
            }
        }
    }
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (abs(dx) + abs(dy) != 1) {
                    continue;
                }
                auto it = mp.find(make_pair(a[u].first + dx, a[u].second + dy));
                if (it != mp.end() && dist[it->second] > dist[u] + 1) {
                    dist[it->second] = dist[u] + 1;
                    ans[it->second] = ans[u];
                    q.push(it->second);
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i].first << " " << ans[i].second << endl;
    }


    return 0;
}
