//https://cses.fi/problemset/task/1163/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int INF = 2e9;

int main() {
    IOS;
    int n, x;
    cin >> x >> n;
    set<pair<int, int>> st;
    multiset<int> sizes;
    st.insert(make_pair(0, x));
    sizes.insert(x);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        auto it = st.upper_bound(make_pair(a, INF));
        it--;
        if (it->second == a) {
            continue;
        }
        auto [l, r] = *it;
        sizes.erase(sizes.find(r - l));
        st.erase(it);
        st.insert(make_pair(l, a));
        sizes.insert(a - l);
        st.insert(make_pair(a, r));
        sizes.insert(r - a);
        cout << *sizes.rbegin() << " ";
    }

    return 0;
}
