//https://atcoder.jp/contests/arc164/tasks/arc164_c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int main() {
    IOS;
    int n;
    cin >> n;
    ll ans = 0;
    multiset<int> st;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        ans += a;
        st.insert(a - b);
    }
    for (int i = 0; i < n; i++) {
        auto it = st.end();
        it--;
        int x = *it;
        ans -= x;
        st.erase(st.find(x));
        st.insert(-x);
        it = st.end();
        it--;
        st.erase(it);
    }
    cout << ans;



    return 0;
}
