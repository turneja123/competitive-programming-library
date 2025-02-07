//https://codeforces.com/contest/2049/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int ans[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, x, y;
        cin >> n >> x >> y;
        x--, y--;
        if (x > y) {
            swap(x, y);
        }
        for (int i = 0; i < n; i++) {
            ans[i] = -1;
        }
        int i;
        if (y - x == 1 || (x == 0 && y == n - 1)) {
            ans[0] = 0;
            i = 1;
            x = 0;
        } else {
            ans[x] = 0;
            ans[y] = 1;
            int xa = (x + 1) % n, xb = (x - 1 + n) % n;
            int ya = (y + 1) % n, yb = (y - 1 + n) % n;
            ans[xa] = 1;
            ans[xb] = 1;
            ans[ya] = 0;
            ans[yb] = 0;
            if (xa == ya || xa == yb) {
                ans[xa] = 2;
            }
            if (xb == ya || xb == yb) {
                ans[xb] = 2;
            }
            i = y;
        }
        while (i != x) {
            if (ans[i] == -1) {
                set<int> st;
                if (ans[(i - 1 + n) % n] != -1) {
                    st.insert(ans[(i - 1 + n) % n]);
                }
                if (ans[(i + 1) % n] != -1) {
                    st.insert(ans[(i + 1) % n]);
                }
                if (*st.begin() == 1) {
                    ans[i] = 0;
                } else if (*st.rbegin() == 0 || st.size() == 1) {
                    ans[i] = 1;
                } else {
                    ans[i] = 2;
                }
            }
            i = (i + 1) % n;
        }
        i = x;
        while (i != y) {
            if (ans[i] == -1) {
                set<int> st;
                if (ans[(i - 1 + n) % n] != -1) {
                    st.insert(ans[(i - 1 + n) % n]);
                }
                if (ans[(i + 1) % n] != -1) {
                    st.insert(ans[(i + 1) % n]);
                }
                if (*st.begin() == 1) {
                    ans[i] = 0;
                } else if (*st.rbegin() == 0 || st.size() == 1) {
                    ans[i] = 1;
                } else {
                    ans[i] = 2;
                }
            }
            i++;
        }
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
