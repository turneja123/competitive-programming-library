//https://atcoder.jp/contests/abc377/tasks/abc377_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

pair<int, int> a[N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    multiset<int> st;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        st.insert(a[i].second);
    }
    sort(a, a + n);
    long long ans = 0;
    for (int i = 1, l = 0; i <= m; i++) {
        int r = m + 1;
        if (st.size()) {
            r = min(r, *st.begin());
        }
        ans += r - i;
        while (l < n && a[l].first <= i) {
            st.erase(st.find(a[l].second));
            l++;
        }
    }
    cout << ans;

    return 0;
}
