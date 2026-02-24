//https://codeforces.com/contest/2201/problem/A2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int a[N];
int r[N];
ll ans[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        stack<int> st;
        int R = n; ll s = 0;
        for (int i = n - 1; i >= 0; i--) {
            while (st.size() && a[st.top()] > a[i]) {
                st.pop();
            }
            if (st.size()) {
                r[i] = st.top();
            } else {
                r[i] = n;
            }
            st.push(i);
            if (i + 1 != n && a[i + 1] - 1 > a[i]) {
                R = i + 1;
            }
            r[i] = min(r[i], R);
            ans[i] = (r[i] == n ? 0 : ans[r[i]]) + n - i;
            s += ans[i];
        }
        cout << s << endl;
    }

    return 0;
}
