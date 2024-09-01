//https://atcoder.jp/contests/abc319/tasks/abc319_c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int a[3][3];
int t[9];

vector<vector<int>> line;

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(12);
    vector<int> pos;
    for (int i = 0; i < 9; i++) {
        pos.push_back(i);
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < 3; i++) {
        vector<int> v;
        for (int j = 0; j < 3; j++) {
            v.push_back(i * 3 + j);
        }
        line.push_back(v);
    }
    for (int j = 0; j < 3; j++) {
        vector<int> v;
        for (int i = 0; i < 3; i++) {
            v.push_back(i * 3 + j);
        }
        line.push_back(v);
    }
    line.push_back({0, 4, 8});
    line.push_back({2, 4, 6});
    int tot = 362880, good = tot;
    do {
        int bad = 0;
        for (int i = 0; i < 9; i++) {
            t[pos[i]] = i;
        }
        for (int j = 0; j < line.size(); j++) {
            vector<pair<int, int>> v;
            for (int i = 0; i < 3; i++) {
                v.push_back(make_pair(t[line[j][i]], line[j][i]));
            }
            sort(v.begin(), v.end());
            if (a[v[0].second / 3][v[0].second % 3] == a[v[1].second / 3][v[1].second % 3] && a[v[1].second / 3][v[1].second % 3] != a[v[2].second / 3][v[2].second % 3]) {
                bad = 1;
            }
        }

        good -= bad;
    } while (next_permutation(pos.begin(), pos.end()));
    double ans = (double)good / (double)tot;
    cout << ans;



    return 0;
}
