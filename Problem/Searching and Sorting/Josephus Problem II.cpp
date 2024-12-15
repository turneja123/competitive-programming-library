//https://cses.fi/problemset/task/2163
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> st;

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    if (n == 1) {
        cout << 1;
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        st.insert(i);
    }
    auto it = st.find_by_order(k % n);
    while (st.size() > 1) {
        cout << *it << " ";
        int x = st.order_of_key(*it);
        st.erase(it);
        int y = (x + k) % (st.size());
        it = st.find_by_order(y);
    }
    cout << *st.begin();

    return 0;
}
