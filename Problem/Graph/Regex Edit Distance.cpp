//https://www.spoj.com/problems/AMR10B/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 505;
const int INF = 1e9;

vector<pair<int, char>> graph[2][N];
int ans[N][N];
int timer;
char trans[2][N];
string s[2];

void build(int l, int r, int u, int v, int n) {
    if (l == r) {
        trans[n][u] = s[n][l];
        graph[n][u].emplace_back(v, trans[n][u]);
        return;
    }
    int mid = l + 1, ct = 0;
    do {
        if (s[n][mid] == '(') {
            ct++;
        } else if (s[n][mid] == ')') {
            ct--;
        }
        mid++;
    } while (ct != 0 && mid <= r);

    int xl = timer++, yl = timer++, xr, yr;
    build(l + 1, mid - 1, xl, yl, n);
    if (s[n][mid] == '*') {
        graph[n][u].emplace_back(xl, 'e');
        graph[n][u].emplace_back(v, 'e');
        graph[n][v].emplace_back(u, 'e');
        graph[n][yl].emplace_back(v, 'e');
    } else if (s[n][mid] == '|') {
        xr = timer++, yr = timer++;
        build(mid + 1, r - 1, xr, yr, n);
        graph[n][u].emplace_back(xl, 'e');
        graph[n][u].emplace_back(xr, 'e');
        graph[n][yl].emplace_back(v, 'e');
        graph[n][yr].emplace_back(v, 'e');
    } else {
        xr = timer++, yr = timer++;
        build(mid, r - 1, xr, yr, n);
        graph[n][u].emplace_back(xl, 'e');
        graph[n][yl].emplace_back(xr, 'e');
        graph[n][yr].emplace_back(v, 'e');
    }
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        for (int i = 0; i < N; i++) {
            trans[0][i] = 'e';
            trans[1][i] = 'e';
            graph[0][i].clear();
            graph[1][i].clear();
            for (int j = 0; j < N; j++) {
                ans[i][j] = INF;
            }
        }
        ans[1][1] = 0;
        int n, m;
        cin >> s[0] >> s[1];
        timer = 2;
        build(0, s[0].size() - 1, 0, 1, 0);
        n = timer;
        timer = 2;
        build(0, s[1].size() - 1, 0, 1, 1);
        m = timer;
        for (int k = 0; k < 1250; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    for (const auto &t1 : graph[0][i]) {
                        int next1 = t1.first;
                        char ch1 = t1.second;
                        if (ch1 == 'e') {
                            ans[i][j] = min(ans[i][j], ans[next1][j]);
                        }
                    }
                    for (const auto &t2 : graph[1][j]) {
                        int next2 = t2.first;
                        char ch2 = t2.second;
                        if (ch2 == 'e') {
                            ans[i][j] = min(ans[i][j], ans[i][next2]);
                        }
                    }
                    if (trans[0][i] != 'e') {
                        ans[i][j] = min(ans[i][j], ans[i + 1][j] + 1);
                        if (trans[0][i] == trans[1][j]) {
                            ans[i][j] = min(ans[i][j], ans[i + 1][j + 1]);
                        } else if (trans[1][j] != 'e') {
                            ans[i][j] = min(ans[i][j], ans[i + 1][j + 1] + 1);
                        }
                    }
                    if (trans[1][j] != 'e') {
                        ans[i][j] = min(ans[i][j], ans[i][j + 1] + 1);
                    }
                }
            }
        }

       cout << ans[0][0] << endl;
    }
    return 0;
}
