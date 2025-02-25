//https://atcoder.jp/contests/abc394/tasks/abc394_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 151;
const int INF = 1e9;

char a[N][N];
int dist[N][N];

vector<pair<int, char>> adj[N];
vector<pair<int, char>> rev[N];

int main() {
    IOS;
    int n;
    cin >> n;
    queue<pair<int, int>> q;
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        q.push(make_pair(i, i));
    }
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) {
            a[i][j] = s[j];
            if (a[i][j] != '-') {
                adj[i].push_back(make_pair(j, a[i][j]));
                rev[j].push_back(make_pair(i, a[i][j]));
                if (i != j) {
                    dist[i][j] = 1;
                    q.push(make_pair(i, j));
                }
            } else if (i != j) {
                dist[i][j] = INF;
            }
        }
    }
    while (q.size()) {
        auto [u, v] = q.front();
        q.pop();
        vector<int> a[26], b[26];
        for (auto [x, c] : rev[u]) {
            a[c - 'a'].push_back(x);
        }
        for (auto [x, c] : adj[v]) {
            b[c - 'a'].push_back(x);
        }
        for (int c = 0; c < 26; c++) {
            for (int x : a[c]) {
                for (int y : b[c]) {
                    if (dist[x][y] > dist[u][v] + 2) {
                        dist[x][y] = dist[u][v] + 2;
                        q.push(make_pair(x, y));
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF) {
                cout << -1 << " ";
            } else {
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
