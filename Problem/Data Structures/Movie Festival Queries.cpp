//https://cses.fi/problemset/task/1664/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int K = 20;

pair<int, int> ivals[N];

int up[K][N];

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    multiset<int> st;
    for (int i = 0; i < n; i++) {
        cin >> ivals[i].first >> ivals[i].second;
        st.insert(ivals[i].second);
    }
    sort(ivals, ivals + n);
    for (int i = 1, l = 0; i < N; i++) {
        while (l < n && ivals[l].first < i) {
            st.erase(st.find(ivals[l].second));
            l++;
        }
        if (st.size()) {
            up[0][i] = *st.begin();
        } else {
            up[0][i] = N - 1;
        }
    }
    for (int i = N - 1; i > 0; i--) {
        for (int k = 1; k < K; k++) {
            up[k][i] = up[k - 1][up[k - 1][i]];
        }
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        int ans = 0;
        for (int k = K - 1; k >= 0; k--) {
            if (up[k][l] <= r) {
                l = up[k][l];
                ans += 1 << k;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
