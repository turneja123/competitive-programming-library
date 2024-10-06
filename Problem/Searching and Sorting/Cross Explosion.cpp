//https://atcoder.jp/contests/abc370/tasks/abc370_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;

set<int> row[N];
set<int> col[N];

int main() {
    IOS;
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            row[i].insert(j);
            col[j].insert(i);
        }
    }
    for (int i = 0; i < q; i++) {
        int r, c;
        cin >> r >> c;
        r--, c--;
        if (row[r].size()) {
            auto it = row[r].lower_bound(c);
            if (it != row[r].end() && *it == c) {
                row[r].erase(it);
            } else {
                if (it != row[r].end()) {
                    col[*it].erase(r);
                    row[r].erase(it);

                }
                if (row[r].size()) {
                    it = row[r].lower_bound(c);
                    if (it != row[r].begin()) {
                        it--;
                        col[*it].erase(r);
                        row[r].erase(it);
                    }
                }
            }
        }
        if (col[c].size()) {
            auto it = col[c].lower_bound(r);
            if (it != col[c].end() && *it == r) {
                col[c].erase(it);
            } else {
                if (it != col[c].end()) {
                    row[*it].erase(c);
                    col[c].erase(it);

                }
                if (col[c].size()) {
                    it = col[c].lower_bound(r);
                    if (it != col[c].begin()) {
                        it--;
                        row[*it].erase(c);
                        col[c].erase(it);
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += row[i].size();
    }
    cout << ans;
    return 0;
}
