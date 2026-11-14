//https://codeforces.com/contest/2271/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9;

int a[N];
int add[N];

bool chk(int n) {
    stack<int> st;
    for (int i = n - 1; i >= 0; i--) {
        while (st.size() && a[st.top()] < a[i]) {
            st.pop();
        }
        if (st.size() && a[st.top()] == a[i]) {
            add[i]++;
            add[st.top() + 1]--;
        }
        st.push(i);
    }
    int ok = 1, s = 0;
    for (int i = 0; i < n; i++) {
        s += add[i];
        if (s == 0) {
            ok = 0;
        }
    }
    for (int i = 0; i <= n; i++) {
        add[i] = 0;
    }
    return ok;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int mx = 0, pos = -1, ct = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] > mx) {
                mx = a[i];
                pos = i;
                ct = 1;
            } else if (a[i] == mx) {
                ct++;
            }
        }
        if (chk(n)) {
            cout << 0 << endl;
            continue;
        }
        vector<pair<int, int>> ops{{0, mx}, {n - 1, mx}};
        if (ct == 1) {
            ops.push_back({pos, 1});
        }
        int ans_ind = -1, ans_val;
        for (auto [i, x] : ops) {
            int old = a[i];
            a[i] = x;
            if (chk(n)) {
                ans_ind = i;
                ans_val = x;
                break;
            }
            a[i] = old;
        }
        if (ans_ind != -1) {
            cout << 1 << endl;
            cout << ans_ind + 1 << " " << ans_val << endl;
        } else {
            cout << 2 << endl;
            cout << 1 << " " << INF << endl;
            cout << n << " " << INF << endl;
        }
    }

    return 0;
}
