//https://cses.fi/problemset/task/1632/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

pair<int, int> a[N];

bool comp(pair<int, int> a, pair<int, int> b) {
    return a.second < b.second;
}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    multiset<int> st;
    for (int i = 0; i < k; i++) {
        st.insert(0);
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    sort(a, a + n, comp);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        auto it = st.upper_bound(a[i].first);
        if (it != st.begin()) {
            it--;
            ans++;
            st.erase(it);
            st.insert(a[i].second);
        }
    }
    cout << ans;
    return 0;
}
