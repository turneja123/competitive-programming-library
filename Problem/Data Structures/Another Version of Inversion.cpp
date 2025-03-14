//https://www.spoj.com/problems/DCEPC14A/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 305;

int a[N][N];
int bit[N][N];

void update(int x, int y, int n, int m, int val){
    for (int i = x; i <= n; i += -i & i) {
        for (int j = y; j <= m; j += -j & j) {
            bit[i][j] += val;
        }
    }
}

int query(int x, int y){
    int sum = 0;
    for (int i = x; i > 0; i -= -i & i) {
        for (int j = y; j > 0; j -= -j & j) {
            sum += bit[i][j];
        }
    }
    return sum;
}

int calc(int x1, int y1, int x2, int y2) {
    int sum = query(x2, y2) - query(x2, y1 - 1) - query(x1 - 1, y2) + query(x1 - 1, y1 - 1);
    return sum;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    map<int, vector<pair<int, int>>> pos;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            pos[a[i][j]].push_back(make_pair(i, j));
            update(i, j, n, m, 1);
        }
    }
    long long ans = 0;
    for (auto it = pos.begin(); it != pos.end(); it++) {
        vector<pair<int, int>> v = it->second;
        for (auto [i, j] : v) {
            update(i, j, n, m, -1);
        }
        for (auto [i, j] : v) {
            ans += calc(0, 0, i, j);
        }
    }
    cout << ans;
    return 0;
}
