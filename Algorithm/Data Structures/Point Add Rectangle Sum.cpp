//https://judge.yosupo.jp/problem/point_add_rectangle_sum
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

    void upd(int x, int y, int wt) {
        x = id(x, compr_x);
        for (int i = x + 1; i <= n; i += i & (-i)) {
            int id_y = id(y, compr_y[i - 1]);
            for (int j = id_y + 1; j <= compr_y[i - 1].size(); j += j & (-j)) {
                t[i - 1][j - 1] += wt;
            }
        }
    }

    ll query_rect(int x, int y) {
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

    ll query(int x1, int y1, int x2, int y2) {
        return query_rect(x2, y2) - query_rect(x1 - 1, y2) - query_rect(x2, y1 - 1) + query_rect(x1 - 1, y1 - 1);
    }
};

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    BIT bit;
    vector<tuple<int, int, int, int, int>> queries;
    for (int i = 0; i < n; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        queries.push_back({0, x, y, w, -1});
        bit.add(x, y);
    }
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int x, y, w;
            cin >> x >> y >> w;
            queries.push_back({0, x, y, w, -1});
            bit.add(x, y);
        } else {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x2--, y2--;
            queries.push_back({1, x1, y1, x2, y2});
        }
    }
    bit.build();
    for (auto [t, x1, y1, x2, y2] : queries) {
        if (t == 0) {
            bit.upd(x1, y1, x2);
        } else {
            cout << bit.query(x1, y1, x2, y2) << endl;
        }
    }

    return 0;
}
