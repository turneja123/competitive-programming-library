//https://atcoder.jp/contests/abc380/tasks/abc380_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

map<pair<vector<int>, vector<int>>, int> mp[2];

int calc(vector<int> &a, vector<int> &b, vector<int> &c, bool flag) {
    auto it = mp[flag].find(make_pair(a, b));
    if (it != mp[flag].end()) {
        return it->second;
    }
    if (!c.size()) {
        return !flag;
    }
    if (flag) {
        int ans = 0;
        for (int i = 0; i < a.size(); i++) {
            int x = lower_bound(c.begin(), c.end(), a[i]) - c.begin() - 1;
            if (x >= 0) {
                vector<int> ta = a, tc = c;
                int y = c[x], z = a[i];
                a.erase(a.begin() + i);
                a.push_back(y);
                sort(a.begin(), a.end());
                c.erase(c.begin() + x);
                c.push_back(z);
                sort(c.begin(), c.end());
                ans = max(ans, calc(a, b, c, 0));
                a = ta, c = tc;
            } else {
                vector<int> ta = a, tc = c;
                int z = a[i];
                a.erase(a.begin() + i);
                sort(a.begin(), a.end());
                c.push_back(z);
                sort(c.begin(), c.end());
                ans = max(ans, calc(a, b, c, 0));
                a = ta, c = tc;
            }
        }
        return mp[flag][make_pair(a, b)] = ans;
    } else {
        int ans = 1;
        for (int i = 0; i < b.size(); i++) {
            int x = lower_bound(c.begin(), c.end(), b[i]) - c.begin() - 1;
            if (x >= 0) {
                vector<int> tb = b, tc = c;
                int y = c[x], z = b[i];
                b.erase(b.begin() + i);
                b.push_back(y);
                sort(b.begin(), b.end());
                c.erase(c.begin() + x);
                c.push_back(z);
                sort(c.begin(), c.end());
                ans = min(ans, calc(a, b, c, 1));
                b = tb, c = tc;
            } else {
                vector<int> tb = b, tc = c;
                int z = b[i];
                b.erase(b.begin() + i);
                sort(b.begin(), b.end());
                c.push_back(z);
                sort(c.begin(), c.end());
                ans = min(ans, calc(a, b, c, 1));
                b = tb, c = tc;
            }
        }
        return mp[flag][make_pair(a, b)] = ans;
    }
}

int main() {
	IOS;
	int n, m, l;
	cin >> n >> m >> l;
	vector<int> a(n), b(m), c(l);
	for (int i = 0; i < n; i++) {
        cin >> a[i];
	}
    for (int i = 0; i < m; i++) {
        cin >> b[i];
	}
	for (int i = 0; i < l; i++) {
        cin >> c[i];
	}
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());
    int ans = calc(a, b, c, 1);
    if (ans) {
        cout << "Takahashi";
    } else {
        cout << "Aoki";
    }
	return 0;
}
