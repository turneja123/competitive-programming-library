//https://codeforces.com/contest/2089/problem/B2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N], a_tmp[N];
int b[N], b_tmp[N];

int r[N];
ll pref[N];

bool chk(int n, int m, ll k) {
    deque<int> st;
    for (int i = n; i >= 0; i--) {
        if (i == n) {
            st.push_front(i);
            continue;
        }
        while (st.size() && st.back() - i > m) {
            st.pop_back();
        }
        if (pref[st.back()] < pref[i]) {
            k -= pref[i] - pref[st.back()];
        }
        while (st.size() && pref[st.front()] < pref[i]) {
            st.pop_front();
        }
        st.push_front(i);
    }
    return k >= 0;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n; ll k, s = 0;
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> a_tmp[i];
            s += a_tmp[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b_tmp[i];
        }
        ll mx = -1; int j = -1;
        for (int i = 0; i < n; i++) {
            pref[i] = b_tmp[i] - a_tmp[i] + ((i == 0) ? 0 : pref[i - 1]);
            if (pref[i] >= mx) {
                mx = pref[i];
                j = i;
            }
        }
        pref[0] = 0;
        for (int i = 0; i < n; i++) {
            a[i] = a_tmp[(j + 1 + i) % n];
            b[i] = b_tmp[(j + 1 + i) % n];
            pref[i + 1] = b[i] - a[i] + pref[i];
        }
        int l = 1, r = n, ans = n;
        while (l <= r) {
            int mid = (l + r) / 2;
            bool can = chk(n, mid, k);
            if (can) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        if (k >= s) {
            ans = 0;
        }
        cout << ans << endl;
    }
    return 0;
}
