//https://codeforces.com/contest/2101/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
vector<int> pos[N];

long long calc(int k, int n) {
    long long ans = 0;
    multiset<int> st;
    for (int i = 0; i < n; i++) {
        if (a[i] >= k) {
            st.insert(i);
        }
    }
    for (int i = k; i >= 1; i--) {
        if (st.size() > 1) {
            ans += *st.rbegin() - *st.begin();
            st.erase(st.begin());
            st.erase(prev(st.end()));
        }
        for (int j : pos[i - 1]) {
            st.insert(j);
        }
    }
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            pos[a[i]].push_back(i);
        }
        int l = 1, r = n;
        while (r - l >= 3) {
            int m1 = l + (r - l) / 3;
            int m2 = r - (r - l) / 3;

            long long f1 = calc(m1, n);
            long long f2 = calc(m2, n);

            if (f1 < f2) {
                l = m1 + 1;
            } else {
                r = m2 - 1;
            }
        }
        long long ans = 0;
        for (; l <= r; l++) {
            ans = max(ans, calc(l, n));
        }
        cout << ans << endl;
        for (int i = 1; i <= n; i++) {
            pos[i].clear();
        }
    }


    return 0;
}
