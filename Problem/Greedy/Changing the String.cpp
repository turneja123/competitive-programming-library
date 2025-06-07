//https://codeforces.com/contest/2111/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


set<int> st[4];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        string s;
        cin >> s;
        for (int i = 0; i < m; i++) {
            char x, y;
            cin >> x >> y;
            if (x == 'c' && y == 'a') {
                st[0].insert(i);
            } else if (x == 'b' && y == 'a') {
                st[1].insert(i);
            } else if (x == 'c' && y == 'b') {
                st[2].insert(i);
            } else if (x == 'b' && y == 'c') {
                st[3].insert(i);
            }
        }
        for (int i = 0; i < n; i++) {
            if (s[i] == 'c') {
                if (st[0].size()) {
                    s[i] = 'a';
                    st[0].erase(st[0].begin());
                    continue;
                }
                if (st[2].size()) {
                    if (st[1].size()) {
                        int x = *st[2].begin();
                        auto it = st[1].lower_bound(x);
                        if (it != st[1].end()) {
                            st[2].erase(st[2].begin());
                            st[1].erase(it);
                            s[i] = 'a';
                        } else {
                            st[2].erase(st[2].begin());
                            s[i] = 'b';
                        }
                    } else {
                        st[2].erase(st[2].begin());
                        s[i] = 'b';
                    }
                }
            } else if (s[i] == 'b') {
                if (st[1].size()) {
                    st[1].erase(st[1].begin());
                    s[i] = 'a';
                } else if (st[3].size() && st[0].size()) {
                    int x = *st[3].begin();
                    auto it = st[0].lower_bound(x);
                    if (it != st[0].end()) {
                        st[3].erase(st[3].begin());
                        st[0].erase(it);
                        s[i] = 'a';
                    }
                }
            }
        }
        for (int i = 0; i < 4; i++) {
            st[i].clear();
        }
        cout << s << endl;
    }
    return 0;
}
