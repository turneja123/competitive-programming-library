//https://dmoj.ca/problem/othscc2p4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;
const int Q = 2e5 + 5;

int a[N][N];
int bit[N][N];
tuple<int, int, int, int, int, int> queries[Q];
int ans[Q];

int compr[N * N];
map<int, int> mp;
vector<pair<int, int>> pos[N * N];

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
    int sum = query(x2, y2) - query(x2 , y1 - 1) - query(x1 - 1, y2)+ query(x1 - 1,y1 - 1);
    return sum;
}

int main() {
    IOS;
    int n, m, q;
    cin >> n >> m >> q;
    int id = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            compr[id++] = a[i][j];
        }
    }
    sort(compr, compr + n * m);
    int ct = 0;
    for (int i = 0; i < n * m; i++) {
        if (i > 0 && compr[i] > compr[i - 1]) {
            ct++;
        }
        mp[compr[i]] = ct;
    }
    for (int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            pos[mp[a[i][j]]].push_back(make_pair(i, j));
        }
    }
    for (int i = 0; i < q; i++) {
        int k, r1, c1, r2, c2;
        cin >> k >> r1 >> c1 >> r2 >> c2;
        queries[i] = make_tuple(k, r1, c1, r2, c2, i);
    }
    sort(queries, queries + q);
    for (int i = 0; i < q; i++) {
        int k = get<0>(queries[i]), r1= get<1>(queries[i]), c1 = get<2>(queries[i]), r2 = get<3>(queries[i]), c2 = get<4>(queries[i]);
        if (i != 0 && k != get<0>(queries[i - 1])) {
            int prv = get<0>(queries[i - 1]);
            auto it = mp.find(prv);
            if (it != mp.end()) {
                for (int p = 0; p < pos[it->second].size(); p++) {
                    int x = pos[it->second][p].first, y = pos[it->second][p].second;
                    update(x, y, n, m, -1);
                }
            }
            auto itt = mp.find(k);
            if (itt != mp.end()) {
                for (int p = 0; p < pos[itt->second].size(); p++) {
                    int x = pos[itt->second][p].first, y = pos[itt->second][p].second;

                    update(x, y, n, m, 1);
                }
            }
        } else if (i == 0) {
            auto itt = mp.find(k);
            if (itt != mp.end()) {
                for (int p = 0; p < pos[itt->second].size(); p++) {
                    int x = pos[itt->second][p].first, y = pos[itt->second][p].second;
                    update(x, y, n, m, 1);
                }
            }
        }
        int sum = calc(r1, c1, r2, c2);
        ans[get<5>(queries[i])] = sum;
    }
    for (int i = 0; i < q; i++) {
        if (ans[i] > 0) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }

    return 0;
}
