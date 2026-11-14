//https://qoj.ac/contest/636/problem/1646
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;

vector<int> a[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < n; i++) {
            int c;
            cin >> c;
            c--;
            a[i].push_back(c);
        }
    }
    for (int i = 0; i < n; i++) {
        reverse(a[i].begin(), a[i].end());
    }

    map<vector<vector<int>>, vector<pair<int, int>>> ans;
    vector<pair<int, int>> all_ops;

    while (1) {
        vector<int> seen(n, 0);
        vector<int> ct(n, 0), good(n, 0);
        int pivot = -1;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < a[i].size(); j++) {
                if (!seen[a[i][j]]) {
                    ct[a[i][j]]++;
                }
                seen[a[i][j]] = 1;
            }
            for (int j = 0; j < a[i].size(); j++) {
                seen[a[i][j]] = 0;
            }
            if (a[i].size()) {
                good[a[i].back()] = 1;
            } else {
                pivot = i;
            }
        }
        int c = -1;
        for (int i = 0; i < n; i++) {
            if (good[i] && ct[i] > 1) {
                c = i;
                break;
            }
        }
        if (c == -1) {
            break;
        }
        vector<vector<int>> hsh;
        vector<pair<vector<int>, int>> v;

        for (int i = 0; i <= n; i++) {
            int has = 0;
            for (int j = 0; j < a[i].size(); j++) {
                if (a[i][j] == c) {
                    has = 1;
                }
            }
            if (has) {
                vector<int> t;
                for (int j = 0; j < a[i].size(); j++) {
                    if (a[i][j] == c) {
                        t.push_back(1);
                    } else {
                        t.push_back(0);
                    }
                }
                hsh.push_back(t);
                v.push_back({t, i});
            }

        }
        hsh.push_back({});
        v.push_back({{}, pivot});

        sort(hsh.begin(), hsh.end());
        sort(v.begin(), v.end());
        auto it = ans.find(hsh);
        if (it == ans.end()) {
            map<vector<vector<int>>, pair<int, int>> mp;
            mp[hsh] = {-1, -1};
            vector<vector<int>> our;
            queue<vector<vector<int>>> q;
            q.push(hsh);

            auto ok = [&](vector<vector<int>> &a) -> int {
                int has_one = 0, has_pivot = 0;
                for (int i = 0; i < a.size(); i++) {
                    if (a[i].empty()) {
                        has_pivot = 1;
                    } else {
                        int ok = 1;
                        for (int j = 0; j < a[i].size(); j++) {
                            if (a[i][j] == 0) {
                                ok = 0;
                            }
                        }
                        has_one |= ok;
                    }
                }
                return has_one && has_pivot;
            };

            int found = 0;
            while (q.size() && !found) {
                auto cur = q.front();
                q.pop();

                for (int i = 0; i < cur.size(); i++) {
                    for (int j = 0; j < cur.size(); j++) {
                        if (i == j) {
                            continue;
                        }
                        if (cur[i].size() >= 1 && cur[j].size() <= 2) {
                            cur[j].push_back(cur[i].back());
                            cur[i].pop_back();
                            if (mp.find(cur) == mp.end()) {
                                if (ok(cur) && !found) {
                                    found = 1;
                                    our = cur;
                                }
                                mp[cur] = {i, j};
                                q.push(cur);
                            }
                            cur[i].push_back(cur[j].back());
                            cur[j].pop_back();
                        }

                    }
                }
            }
            vector<pair<int, int>> ops;
            while (our != hsh) {
                auto [i, j] = mp[our];
                ops.push_back({i, j});
                our[i].push_back(our[j].back());
                our[j].pop_back();
            }

            reverse(ops.begin(), ops.end());
            ans[hsh] = ops;
        }
        auto ops = ans[hsh];
        for (int k = 0; k < ops.size(); k++) {
            int i = v[ops[k].first].second, j = v[ops[k].second].second;
            a[j].push_back(a[i].back());
            a[i].pop_back();
            all_ops.push_back({i, j});
        }
    }
    int pivot = -1;
    for (int i = 0; i <= n; i++) {
        if (a[i].empty()) {
            pivot = i;
        }
    }
    if (pivot != n) {
        all_ops.push_back({n, pivot});
        all_ops.push_back({n, pivot});
        all_ops.push_back({n, pivot});
    }

    cout << all_ops.size() << endl;
    for (auto [i, j] : all_ops) {
        cout << i + 1 << " " << j + 1 << endl;
    }

    return 0;
}
