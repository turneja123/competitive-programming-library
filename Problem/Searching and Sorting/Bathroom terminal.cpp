//https://codeforces.com/contest/852/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    vector<string> v;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        v.push_back(s);
    }
    sort(v.begin(), v.end());

    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        int j[3];
        j[0] = -1, j[1] = -1, j[2] = -1;
        for (int k = 0; k < s.size(); k++) {
            if (s[k] == '?') {
                if (j[0] == -1) {
                    j[0] = k;
                } else if (j[1] == -1) {
                    j[1] = k;
                } else {
                    j[2] = k;
                }
            }
        }
        int ans = 0;
        vector<string> st;
        for (int x1 = 0; x1 < 6; x1++) {
            for (int x2 = 0; x2 < 6; x2++) {
                for (int x3 = 0; x3 < 6; x3++) {
                    string t = s;
                    if (j[2] != -1) {
                        if (x3 == 0) {
                            t.erase(t.begin() + j[2]);
                        } else {
                            t[j[2]] = 'a' + x3 - 1;
                        }
                    }

                    if (j[1] != -1) {
                        if (x2 == 0) {
                            t.erase(t.begin() + j[1]);
                        } else {
                            t[j[1]] = 'a' + x2 - 1;
                        }
                    }

                    if (j[0] != -1) {
                        if (x1 == 0) {
                            t.erase(t.begin() + j[0]);
                        } else {
                            t[j[0]] = 'a' + x1 - 1;
                        }
                    }
                    st.push_back(t);
                }
            }
        }
        sort(st.begin(), st.end());
        st.erase(unique(st.begin(), st.end()), st.end());
        for (string t : st) {
            ans += upper_bound(v.begin(), v.end(), t) - lower_bound(v.begin(), v.end(), t);
        }
        cout << ans << endl;
    }
    return 0;
}
