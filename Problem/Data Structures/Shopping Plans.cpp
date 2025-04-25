//https://dmoj.ca/problem/cco20p6
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;
const long long INF = 1e18;

struct Group {
    vector<int> a;
    int l;
    int r;
    int diff;
};

vector<Group> ta;
vector<Group> a;
vector<int> diff_arr[N];
vector<long long> pref[N];

bool comp(Group &a, Group &b) {
    return a.diff < b.diff;
}

vector<long long> solve(long long mx, long long s, int k) {
    int ct = 1;
    vector<long long> sorted{s};
    priority_queue<tuple<long long, int, int, int, int>> pq;
    if (a[0].l == 0) {
        long long val = s + a[0].a[0];
        if (val <= mx && ct + pq.size() < k) {
            pq.push(make_tuple(-val, 0, 0, 1, 1));
        }
    } else {
        long long val = s + a[0].diff;
        if (val <= mx && ct + pq.size() < k) {
            pq.push(make_tuple(-val, 0, a[0].l, 1, 1));
        }
        for (int i = 2; i <= a[0].l && ct + pq.size() < k; i++) {
            long long val = s + pref[0][a[0].l - 1] - ((a[0].l - 1 - i == -1) ? 0 : pref[0][a[0].l - 1 - i]);
            if (val <= mx) {
                pq.push(make_tuple(-val, 0, a[0].l, i, 0));
            } else {
                break;
            }
        }
        val = s + a[0].a[a[0].l];
        if (val <= mx && ct + pq.size() < k && a[0].l + 1 <= a[0].r) {
            pq.push(make_tuple(-val, 0, a[0].l, a[0].l + 1, 0));
        }
    }
    while (pq.size() && ct < k) {
        auto [s, g, j, sz, first] = pq.top();
        s = -s;
        pq.pop();
        ct++;
        sorted.push_back(s);
        if (j != a[g].a.size() - 1) {
            for (int i = 1; i <= sz && ct + pq.size() < k; i++) {
                long long val = s + pref[g][j] - ((j - i == -1) ? 0 : pref[g][j - i]);
                if (val <= mx) {
                    pq.push(make_tuple(-val, g, j + 1, i, 0));
                } else {
                    break;
                }
            }
            if (j + 1 == sz) {
                long long val = s + a[g].a[j + 1];
                if (val <= mx && ct + pq.size() < k && sz + 1 <= a[g].r) {
                    pq.push(make_tuple(-val, g, j + 1, sz + 1, 0));
                }
            }
        }

        if (g != a.size() - 1) {
            if (a[g + 1].l == 0) {
                long long val = s + a[g + 1].a[0];
                if (val <= mx && ct + pq.size() < k) {
                    pq.push(make_tuple(-val, g + 1, 0, 1, 1));
                }
            } else {
                long long val = s + a[g + 1].diff;
                if (val <= mx && ct + pq.size() < k) {
                    pq.push(make_tuple(-val, g + 1, a[g + 1].l, 1, 1));
                }
                for (int i = 2; i <= a[g + 1].l && ct + pq.size() < k; i++) {
                    long long val = s + pref[g + 1][a[g + 1].l - 1] - ((a[g + 1].l - 1 - i == -1) ? 0 : pref[g + 1][a[g + 1].l - 1 - i]);
                    if (val <= mx) {
                        pq.push(make_tuple(-val, g + 1, a[g + 1].l, i, 0));
                    } else {
                        break;
                    }
                }
                val = s + a[g + 1].a[a[g + 1].l];
                if (val <= mx && ct + pq.size() < k && a[g + 1].l + 1 <= a[g + 1].r) {
                    pq.push(make_tuple(-val, g + 1, a[g + 1].l, a[g + 1].l + 1, 0));
                }
            }

        }

        if (g != a.size() - 1 && first) {
            if (a[g + 1].l == 0) {
                long long val = s + a[g + 1].a[0] - a[g].diff;
                if (val <= mx && ct + pq.size() < k) {
                    pq.push(make_tuple(-val, g + 1, 0, 1, 1));
                }
            } else {
                long long val = s + a[g + 1].diff - a[g].diff;
                if (val <= mx && ct + pq.size() < k) {
                    pq.push(make_tuple(-val, g + 1, a[g + 1].l, 1, 1));
                }
                for (int i = 2; i <= a[g + 1].l && ct + pq.size() < k; i++) {
                    long long val = s + pref[g + 1][a[g + 1].l - 1] - ((a[g + 1].l - 1 - i == -1) ? 0 : pref[g + 1][a[g + 1].l - 1 - i]) - a[g].diff;
                    if (val <= mx) {
                        pq.push(make_tuple(-val, g + 1, a[g + 1].l, i, 0));
                    } else {
                        break;
                    }
                }
                val = s + a[g + 1].a[a[g + 1].l] - a[g].diff;
                if (val <= mx && ct + pq.size() < k && a[g + 1].l + 1 <= a[g + 1].r) {
                    pq.push(make_tuple(-val, g + 1, a[g + 1].l, a[g + 1].l + 1, 0));
                }
            }
        }
    }
    return sorted;
}

int main() {
    IOS;
    int n, m, k;
    cin >> n >> m >> k;
    ta.resize(m);
    for (int i = 0; i < n; i++) {
        int x, c;
        cin >> x >> c;
        x--;
        ta[x].a.push_back(c);
    }
    long long s = 0;
    for (int i = 0; i < m; i++) {
        cin >> ta[i].l >> ta[i].r;
        if (ta[i].r == 0) {
            continue;
        }
        ta[i].r = min(ta[i].r, (int)ta[i].a.size());
        if (ta[i].r < ta[i].l) {
            for (int j = 0; j < k; j++) {
                cout << -1 << endl;
            }
            return 0;
        }
        sort(ta[i].a.begin(), ta[i].a.end());
        for (int j = 0; j < ta[i].l; j++) {
            s += ta[i].a[j];
        }
        if (ta[i].l == ta[i].a.size()) {
            continue;
        }
        if (ta[i].l == 0) {
            ta[i].diff = ta[i].a[0];
        } else {
            ta[i].diff = ta[i].a[ta[i].l] - ta[i].a[ta[i].l - 1];
        }
        a.push_back(ta[i]);
    }
    sort(a.begin(), a.end(), comp);
    m = a.size();
    for (int i = 0; i < m; i++) {
        diff_arr[i].resize(a[i].a.size());
        pref[i].resize(a[i].a.size());
        for (int j = 0; j < a[i].a.size() - 1; j++) {
            diff_arr[i][j] = a[i].a[j + 1] - a[i].a[j];
            pref[i][j] = (j == 0 ? diff_arr[i][j] : pref[i][j - 1] + diff_arr[i][j]);
        }
    }

    long long mid = INF;
    vector<long long> ans = solve(mid, s, k);
    if (ans.size() < k) {
        sort(ans.begin(), ans.end());
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i] << endl;
        }
        for (int i = ans.size(); i < k; i++) {
            cout << -1 << endl;
        }
        return 0;
    }
    long long l = 1, r = 1e18, spl;
    ans = {};
    while (l <= r) {
        long long mid = (l + r) / 2;
        vector<long long> cur = solve(mid, s, k);
        if (cur.size() < k) {
            ans = cur;
            l = mid + 1;
        } else {
            r = mid - 1;
            spl = mid;
        }
    }
    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << endl;
    }
    for (int i = ans.size(); i < k; i++) {
        cout << spl << endl;
    }
    return 0;
}
