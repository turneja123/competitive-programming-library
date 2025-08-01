//https://www.spoj.com/problems/SPIRALGR/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;

vector<pair<int, int>> mov{{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

int a[N][N];
int dist[N][N];
pair<int, int> pos[N * N];

bool is_prime[N * N];

int main() {
    //IOS;
    for (int i = 2; i < N * N; i++) {
        is_prime[i] = true;
    }
    for (int i = 2; i < N * N; i++) {
        if (is_prime[i]) {
            for (int j = 2 * i; j < N * N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    int x = N / 2, y = N / 2;
    int i = 1, j = 1, z = 0, p = 0;
    a[x][y] = i;
    pos[i] = {x, y};
    while (x < N && y < N && x >= 0 && y >= 0) {
        for (int k = 0; k < j; k++) {
            x += mov[p].first;
            y += mov[p].second;
            a[x][y] = ++i;
            pos[i] = {x, y};
        }
        z++;
        if (z % 2 == 0) {
            j++;
            z = 0;
        }
        p = (p + 1) % 4;
    }
    int st, en;
    int t = 1;
    while (cin >> st >> en) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                dist[i][j] = N * N;
            }
        }
        auto [x, y] = pos[st];
        dist[x][y] = 0;
        queue<pair<int, int>> q;
        q.push({x, y});
        int ans = -1;
        while (q.size()) {
            auto [x, y] = q.front();
            q.pop();
            if (a[x][y] == en) {
                ans = dist[x][y];
                break;
            }
            for (auto [dx, dy] : mov) {
                if (x + dx >= 0 && x + dx < N && y + dy >= 0 && y + dy <= N && dist[x + dx][y + dy] == N * N && !is_prime[a[x + dx][y + dy]]) {
                    dist[x + dx][y + dy] = dist[x][y] + 1;
                    q.push({x + dx, y+ dy});
                }
            }
        }
        cout << "Case " << t++ << ": ";
        if (ans == -1) {
            cout << "impossible" << endl;
        } else {
            cout << ans << endl;

        }
    }
    return 0;
}
