//https://codeforces.com/contest/2150/problem/A
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        string s;
        cin >> s;
        set<int> st;
        for (int i = 0; i < m; i++) {
            int p;
            cin >> p;
            st.insert(p);
        }
        int last = 1; char last_jump = 'A';
        for (int i = 0; i < n; i++) {
            if (last_jump == 'B') {
                auto it = st.upper_bound(last);
                if (it == st.end() || *it > last + 1) {
                    last++;
                } else {
                    while (it != st.end() && *it == last + 1) {
                        last++;
                        it++;
                    }
                    last++;
                }
            }
            if (s[i] == 'A') {
                last++;
                st.insert(last);
            } else {
                auto it = st.upper_bound(last);
                if (it == st.end() || *it > last + 1) {
                    last++;
                    st.insert(last);
                } else {
                    while (it != st.end() && *it == last + 1) {
                        last++;
                        it++;
                    }
                    last++;
                    st.insert(last);
                }
            }
            last_jump = s[i];
        }
        cout << st.size() << endl;
        for (int x : st) {
            cout << x << " ";
        }
        cout << endl;
    }

    return 0;
}
