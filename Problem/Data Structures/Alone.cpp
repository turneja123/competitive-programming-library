//https://atcoder.jp/contests/abc346/tasks/abc346_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
vector<int> pos[N];
vector<pair<int, int>> segtree[4 * N];
set<pair<int, int>> ivals;
vector<tuple<int, int, int, int>> restore;

long long sum = 0; int ans = 0;

void upd(int l, int r, int lq, int rq, pair<int, int> edge, int node) {
    if (r < lq || l > rq) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].push_back(edge);
        return;
    }
    int mid = (l + r) / 2;
    upd(l, mid, lq, rq, edge, 2 * node + 1);
    upd(mid + 1, r, lq, rq, edge, 2 * node + 2);
    return;
}

void dfs(int l, int r, int node) {
    int ct = 0;
    for (auto [l, r] : segtree[node]) {
        if (ivals.empty()) {
            ivals.insert(make_pair(l, r));
            restore.push_back(make_tuple(-1, l, r, ans));
            ans += r - l + 1;
            ct++;
            continue;
        }
        auto it = ivals.lower_bound({l, r});
        if (it != ivals.begin()) {
            --it;
            if (it->second < l - 1) {
                ++it;
            }
        }
        int new_l = l;
        int new_r = r;
        while (it != ivals.end() && it->first <= r + 1) {
            new_l = min(new_l, it->first);
            new_r = max(new_r, it->second);
            restore.push_back(make_tuple(1, it->first, it->second, ans));
            ans -= it->second - it->first + 1;
            it = ivals.erase(it);
            ct++;
        }
        ivals.insert(make_pair(new_l, new_r));
        restore.push_back(make_tuple(-1, new_l, new_r, ans));
        ans += new_r - new_l + 1;
        ct++;
    }
    if (l == r) {
        sum += ans;
    } else {
        int mid = (l + r) / 2;
        dfs(l, mid, 2 * node + 1);
        dfs(mid + 1, r, 2 * node + 2);
    }
    for (int i = 0; i < ct; i++) {
        auto [f, l, r, a] = restore.back();
        ans = a;
        if (f == -1) {
            ivals.erase(ivals.find(make_pair(l, r)));
        } else {
            ivals.insert(make_pair(l, r));
        }
        restore.pop_back();
    }
    return;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < pos[i].size(); j++) {
            int l = (j == 0 ? 0 : pos[i][j - 1] + 1);
            int r = (j == pos[i].size() - 1 ? n - 1 : pos[i][j + 1] - 1);
            upd(0, n - 1, l, pos[i][j], make_pair(pos[i][j], r), 0);
        }
    }
    dfs(0, n - 1, 0);
    cout << sum;
    return 0;
}
