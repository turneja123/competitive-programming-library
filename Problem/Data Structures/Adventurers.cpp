//https://codeforces.com/contest/2047/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

struct Data {
    int x, y, wt;
    Data(int x, int y, int wt) : x(x), y(y), wt(wt) {}
};

struct BIT {
    int n;
    vector<int> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void upd(int i, int val) {
        i++;
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    int query(int i) {
        int ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    int query(int l, int r) {
        l++, r++;
        return query(r) - query(l - 1);
    }
};

int yval[N];

bool comp(Data a, Data b) {
    return a.x < b.x;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        map<pair<int, int>, int> mp;
        set<int> st;
        map<int, int> mpy;
        int m = 0;
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            mp[{x, y}]++;
            st.insert(y);
        }
        for (int y : st) {
            yval[m] = y;
            mpy[y] = m++;
        }
        vector<Data> points;
        for (auto it : mp) {
            points.push_back(Data(it.first.first, mpy[it.first.second], it.second));
        }
        sort(points.begin(), points.end(), comp);
        BIT bl(m), br(m);
        for (Data point : points) {
            br.upd(point.y, point.wt);
        }
        n = points.size();
        int best = 0; pair<int, int> ans = {0, 0};
        for (int i = 0; i < n;) {
            int cur = points[i].x;
            while (i < n && points[i].x == cur) {
                br.upd(points[i].y, -points[i].wt);
                bl.upd(points[i].y, points[i].wt);
                i++;
            }
            int l = 0, r = m - 1;
            while (l <= r) {
                int mid = (l + r) / 2;
                int lf = min(bl.query(0, mid), br.query(0, mid));
                int rt = min(bl.query(mid + 1, m - 1), br.query(mid + 1, m - 1));
                int tot = min(lf, rt);
                if (tot > best) {
                    best = tot;
                    ans = make_pair(cur + 1, yval[mid] + 1);
                }
                if (lf < rt) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
        }
        cout << best << endl;
        cout << ans.first << " " << ans.second << endl;
    }
    return 0;
}
