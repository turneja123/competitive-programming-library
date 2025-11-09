//https://codeforces.com/contest/2164/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

vector<tuple<int, int, int>> func(string &a) {
    vector<tuple<int, int, int>> blk;
    char last = a[0]; int l = 0, ct = 1;
    for (int i = 1; i < a.size(); i++) {
        if (a[i] != last) {
            blk.push_back(make_tuple(last - 'a', l, l + ct - 1));
            l = i;
            ct = 1;
            last = a[i];
        } else {
            ct++;
        }
    }
    blk.push_back(make_tuple(last - 'a', l, l + ct - 1));
    return blk;
}

vector<int> pos[26];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        string a, b;
        cin >> a >> b;
        if (a[0] != b[0]) {
            cout << -1 << endl;
            continue;
        }
        if (a == b) {
            cout << 0 << endl;
            continue;
        }
        int found = 0;
        vector<tuple<int, int, int>> blk = func(b);
        vector<string> store;
        for (int it = 1; it <= k; it++) {
            string nw = a;
            for (int i = 0; i < 26; i++) {
                pos[i].clear();
            }
            for (int i = 0; i < n; i++) {
                pos[a[i] - 'a'].push_back(i);
            }
            int can = 1;
            int R = n;

            for (int i = blk.size() - 1; i >= 0; i--) {
                auto [c, l, r] = blk[i];
                if (pos[c].empty()) {
                    can = 0;
                    break;
                }
                int j = upper_bound(pos[c].begin(), pos[c].end(), min(l, R - 1)) - pos[c].begin() - 1;
                if (j == -1) {
                    can = 0;
                    break;
                }
                j = pos[c][j];
                for (int z = j + 1; z < R; z++) {
                    int cur = a[z - 1] - 'a';
                    if (cur == c) {
                        nw[z] = c + 'a';
                    }
                }
                R = min(j + 1, l);
            }
            if (!can) {
                break;
            }
            a = nw;
            store.push_back(a);
            if (a == b) {
                found = it;
                break;
            }

        }
        if (!found) {
            cout << -1 << endl;
        } else {
            cout << found << endl;
            for (string s : store) {
                cout << s << endl;
            }
        }

    }
    return 0;
}
