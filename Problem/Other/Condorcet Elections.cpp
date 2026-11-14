//https://qoj.ac/contest/1964/problem/10310
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 51;

int need[N][N];
int ct[N][N];

mt19937 gene(3);

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        need[u][v] = 1;
    }
    vector<vector<int>> p;
    for (int i = 0; i < 500; i++) {
        vector<int> v(n);
        iota(v.begin(), v.end(), 0);
        shuffle(v.begin(), v.end(), gene);
        for (int j = 0; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                ct[v[j]][v[k]]++;
            }
        }
        p.push_back(v);
    }
    int cost = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (need[i][j] && ct[i][j] <= ct[j][i]) {
                cost += ct[j][i] - ct[i][j] + 1;
            }
        }
    }
    while (cost) {
        int i = gene() % 500, j = gene() % (n - 1);
        int u = p[i][j], v = p[i][j + 1];
        if (need[v][u] && ct[u][v] >= ct[v][u]) {
            swap(p[i][j], p[i][j + 1]);
            cost -= ct[u][v] - ct[v][u] + 1;
            ct[u][v]--;
            ct[v][u]++;
            cost += max(0, ct[u][v] - ct[v][u] + 1);

            continue;
        }

        if (!need[u][v] || (need[u][v] && ct[u][v] - 1 > ct[v][u] + 1)) {
            swap(p[i][j], p[i][j + 1]);
            ct[u][v]--;
            ct[v][u]++;
        }
    }
    cout << "YES" << endl;
    cout << 500 << endl;
    for (int i = 0; i < 500; i++) {
        for (int j = 0; j < n; j++) {
            cout << p[i][j] + 1 << " ";
        }
        cout << endl;
    }


    return 0;
}
