//https://qoj.ac/contest/2509/problem/14100
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

vector<tuple<int, int, char>> ops;

int solve(string s, int n) {
    vector<int> f(3, -n);
    for (int i = 0; i < 3 * n; i++) {
        f[s[i] - 'A']++;
    }
    int mn = -1;
    vector<int> id(3, 0);
    int ptr = 0;
    for (int i = 0; i < 3; i++) {
        if (f[i] < 0) {
            mn = i;
            break;
        }
    }
    if (mn == -1) {
        return 1;
    }
    vector<int> need, cur;
    map<vector<int>, int> mp;

    for (int i = 0; i < 3; i++) {
        if (f[i] >= 0) {
            id[i] = ptr++;
            cur.push_back(0);
            need.push_back(f[i]);
        }
    }
    if (cur.size() == 1) {
        return 0;
    }
    mp[cur] = -1;
    for (int i = 0; i < 3 * n; i++) {
        int c = s[i] - 'A';
        if (c != mn) {
            cur[id[c]]++;
        }
        vector<int> ask(cur.size());
        for (int j = 0; j < cur.size(); j++) {
            ask[j] = cur[j] - need[j];
        }
        auto it = mp.find(ask);
        if (it != mp.end()) {
            ops.push_back({it->second + 2, i + 1, 'A' + mn});
            return 1;
        }
        mp[cur] = i;
    }
    return 0;
}

int main() {
    IOS;
    int n;
    cin >> n;
    string s;
    cin >> s;
    if (solve(s, n)) {
        cout << ops.size() << endl;
        for (auto [l, r, c] : ops) {
            cout << l << " " << r << " " << c << endl;
        }
        return 0;
    }
    vector<pair<int, int>> f({make_pair(0, 0), make_pair(0, 1), make_pair(0, 2)});
    for (int i = 0; i < 3 * n; i++) {
        f[s[i] - 'A'].first++;
    }
    sort(f.begin(), f.end());

    int need = f.back().first - n;
    vector<int> pos;
    for (int i = 0; i < 3 * n; i++) {
        if (s[i] - 'A' == f.back().second) {
            pos.push_back(i);
        }
    }
    ops.push_back({pos[0] + 1, pos[need - 1] + 1, 'A'+ f[0].second});
    for (int i = pos[0]; i < pos[need - 1]; i++) {
        s[i] = 'A' + f[0].second;
    }
    solve(s, n);
    cout << ops.size() << endl;
    for (auto [l, r, c] : ops) {
        cout << l << " " << r << " " << c << endl;
    }





    return 0;
}
