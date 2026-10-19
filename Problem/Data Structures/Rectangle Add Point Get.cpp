//https://judge.yosupo.jp/problem/rectangle_add_point_get
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

struct BIT {
    vector<int> compr_x;
    vector<vector<int>> compr_y;
    vector<vector<ll>> t;
    map<int, vector<int>> mp;
    int n;

    int id(int x, vector<int> &v) {
        return lower_bound(v.begin(), v.end(), x) - v.begin();
    }

    int id_q(int x, vector<int> &v) {
        return upper_bound(v.begin(), v.end(), x) - v.begin() - 1;
    }

    void add(int x, int y) {
        mp[x].push_back(y);
    }

    void build() {
        for (auto [x, v] : mp) {
            compr_x.push_back(x);
            compr_y.push_back(v);
        }
        mp.clear();
        n = compr_x.size();
        for (int i = n - 1; i >= 0; i--) {
            for (int y : compr_y[i]) {
                int pos = i + 1;
                pos += pos & (-pos);
                for (int i = pos; i <= n; i += i & (-i)) {
                    compr_y[i - 1].push_back(y);
                }
            }
        }

        t.resize(n);
        for (int i = 0; i < n; i++) {
            sort(compr_y[i].begin(), compr_y[i].end());
            compr_y[i].erase(unique(compr_y[i].begin(), compr_y[i].end()), compr_y[i].end());
            t[i] = vector<ll>(compr_y[i].size(), 0);
        }
    }

    void upd_rect(int x, int y, int wt) {
        x = id(x, compr_x);
        for (int i = x + 1; i <= n; i += i & (-i)) {
            int id_y = id(y, compr_y[i - 1]);
            for (int j = id_y + 1; j <= compr_y[i - 1].size(); j += j & (-j)) {
                t[i - 1][j - 1] += wt;
            }
        }
    }

    ll query(int x, int y) {
        x = id_q(x, compr_x);
        ll ans = 0;
        for (int i = x + 1; i >= 1; i -= i & (-i)) {
            int id_y = id_q(y, compr_y[i - 1]);
            for (int j = id_y + 1; j >= 1; j -= j & (-j)) {
                ans += t[i - 1][j - 1];
            }
        }
        return ans;
    }

    void upd(int x1, int y1, int x2, int y2, int wt) {
        upd_rect(x1, y1, wt);
        upd_rect(x2 + 1, y1, -wt);
        upd_rect(x1, y2 + 1, -wt);
        upd_rect(x2 + 1, y2 + 1, wt);
    }
};

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    BIT bit;
    vector<tuple<int, int, int, int, int>> queries;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2, w;
        cin >> x1 >> y1 >> x2 >> y2 >> w;
        x2--, y2--;
        queries.push_back({x1, y1, x2, y2, w});
        bit.add(x1, y1);
        bit.add(x2 + 1, y1);
        bit.add(x1, y2 + 1);
        bit.add(x2 + 1, y2 + 1);
    }
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int x1, y1, x2, y2, w;
            cin >> x1 >> y1 >> x2 >> y2 >> w;
            x2--, y2--;
            queries.push_back({x1, y1, x2, y2, w});
            bit.add(x1, y1);
            bit.add(x2 + 1, y1);
            bit.add(x1, y2 + 1);
            bit.add(x2 + 1, y2 + 1);
        } else {
            int x, y;
            cin >> x >> y;
            queries.push_back({-1, x, y, -1, -1});
        }
    }
    bit.build();
    for (auto [x1, y1, x2, y2, wt] : queries) {
        if (x1 != -1) {
            bit.upd(x1, y1, x2, y2, wt);
        } else {
            cout << bit.query(y1, x2) << endl;
        }
    }

    return 0;
}
