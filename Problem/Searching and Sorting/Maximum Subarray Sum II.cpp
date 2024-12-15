//https://cses.fi/problemset/task/1644
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int x[N];
long long sum[N];

int main() {
    IOS;
    int n, a, b;
    cin >> n >> a >> b;
    multiset<long long> st;
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        sum[i] = (i == 0 ? x[i] : sum[i - 1] + x[i]);
    }
    long long ans = sum[a - 1];
    st.insert(0);
    for (int i = a, l = 0; i < b; i++, l++) {
        st.insert(sum[i - a]);
        ans = max(ans, sum[i] - *st.begin());
    }
    for (int i = b, r = b - a, l = -1; i < n; i++, l++, r++) {
        if (l == -1) {
            st.erase(st.find(0));
        } else {
            st.erase(st.find(sum[l]));
        }
        st.insert(sum[r]);
        ans = max(ans, sum[i] - *st.begin());
    }
    cout << ans;
    return 0;
}
