//https://codeforces.com/contest/2170/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int ans[N];
int a[N];
int quest[N];
int diff[N];

int get_value(int i, int n) {
    int ans = 0;
    if (!quest[i] || a[i] != 1) {
        return -1000;
    }
    if (i != 0 && a[i - 1] == 1) {
        ans++;
    }
    if (i != n - 1 && a[i + 1] == 0) {
        ans--;
    }
    return ans;

}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        string s;
        cin >> s;
        int m = 0;
        int ans = 0;

        for (int i = 0; i < n; i++) {
            if (s[i] == 'I') {
                ans++;
            } else if (s[i] == 'V') {
                ans += 5;
            } else if (s[i] == 'X') {
                ans += 10;
            }
            if (s[i] == '?') {
                m++;
                quest[i] = 1;
            } else {
                quest[i] = 0;
            }

            if (s[i] == 'I' || s[i] == '?') {
                a[i] = 1;
            } else {
                a[i] = 0;
            }
        }
        set<pair<int, int>> st;
        diff[0] = 0;
        for (int i = 0; i < n; i++) {

            if (i != n - 1 && a[i] == 1 && a[i + 1] == 0) {
                diff[0]++;
            }
            int x = get_value(i, n);
            if (x != -1000) {
                st.insert({x, i});
            }
        }
        for (int j = 1; j <= m; j++) {
            auto [d, i] = *st.rbegin();
            st.erase({d, i});
            diff[j] = diff[j - 1] + d;

            if (i != 0) {
                int x = get_value(i - 1,n);
                if (x != -1000) {
                    st.erase(st.find({x, i - 1}));
                }
            }
            if (i != n - 1) {
                int x = get_value(i + 1,n);
                if (x != -1000) {
                    st.erase(st.find({x, i + 1}));
                }

            }
            a[i] = 0;

            if (i != 0) {
                int x = get_value(i - 1,n);
                if (x != -1000) {
                    st.insert({x, i - 1});
                }
            }
            if (i != n - 1) {
                int x = get_value(i + 1,n);
                if (x != -1000) {
                    st.insert({x, i + 1});
                }
            }
        }
        for (int j = 0; j < q; j++) {
            int need = m;
            int x,v,i;
            cin >> x >> v >> i;
            if (i >= need) {
                x = 0, v = 0, i = need;
            } else {
                need -= i;
                if (v >= need) {
                    x = 0, v = need;
                } else {
                    need -= v;
                    x = need;
                }
            }
            int cur = ans + i + 5 * v + 10 * x - 2 * diff[v + x];
            cout << cur << endl;

        }

    }


    return 0;
}
