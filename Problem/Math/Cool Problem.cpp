//https://codeforces.com/contest/2187/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll M = 998244353;

bitset<N> a, b;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, x, y;
        cin >> n >> x >> y;
        string s;
        cin >> s;
        a[N / 2] = 1;
        for (int i = n - 1; i >= 0; i--) {
            bitset<N> nx_a, nx_b;
            if (s[i] == '0' || s[i] == '?') {
                nx_a |= a << 1;
                nx_b |= b >> 1;
            }
            if (s[i] == '1' || s[i] == '?') {
                nx_a |= b;
                nx_b |= a;
            }
            a = nx_a, b = nx_b;
        }
        set<ll> st;
        ll ans = 0;
        for (int i = N / 2 - n; i <= N / 2 + n; i++) {
            if (a[i] || b[i]) {
                int z = (i < N / 2 ? N / 2 - i - 1 : i - N / 2);
                ll cur = (ll)z * (z + 1) / 2 * x + (ll)(z % 2 == n % 2 ? n / 2 - z / 2 : n / 2 + 1 + z / 2) * y;
                if (st.find(cur) == st.end()) {
                    ans = (ans + cur) % M;
                    st.insert(cur);
                }
            }
            a[i] = 0, b[i] = 0;
        }
        cout << ans << endl;
    }


    return 0;
}
