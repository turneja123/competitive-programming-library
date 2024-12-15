//https://atcoder.jp/contests/abc237/tasks/abc237_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

set<tuple<int, int, int>> st;

int main() {
    IOS;
    int n, q, x;
    cin >> n >> q >> x;
    int last = -1, l = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if (a < x) {
            a = 0;
        } else if (a == x) {
            a = 1;
        } else {
            a = 2;
        }
        if (i == 0) {
            last = a, l = i;
        } else if (last != a) {
            st.insert(make_tuple(l, i - 1, last));
            last = a, l = i;
        }
    }
    st.insert(make_tuple(l, n - 1, last));
    for (int i = 0; i < q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        l--, r--;
        vector<int> freq(3, 0);

        auto it = st.upper_bound(make_tuple(l, N, N));
        it--;
        auto [lq, rq, c] = *it;
        if (rq >= l) {
            freq[c] += rq - l + 1;
            rq = l - 1;
            st.erase(it);
            if (lq <= rq) {
                st.insert(make_tuple(lq, rq, c));
            }
        }
        it = st.lower_bound(make_tuple(l, 0, 0));
        while (it != st.end() && get<0>(*it) <= r) {
            auto [lq, rq, c] = *it;
            if (rq <= r) {
                freq[c] += rq - lq + 1;
                it = st.erase(it);
            } else {
                freq[c] += r - lq + 1;
                st.erase(it);
                st.insert(make_tuple(r + 1, rq, c));
                break;
            }
        }
        if (t == 1) {
            for (int j = 0, lf = l; j < 3; j++) {
                if (freq[j] != 0) {
                    st.insert(make_tuple(lf, lf + freq[j] - 1, j));
                    lf += freq[j];
                }
            }
        } else {
            for (int j = 2, lf = l; j >= 0; j--) {
                if (freq[j] != 0) {
                    st.insert(make_tuple(lf, lf + freq[j] - 1, j));
                    lf += freq[j];
                }
            }
        }
    }
    int ans = 0;
    for (auto it = st.begin(); it != st.end(); ++it) {
        if (get<2>(*it) == 1) {
            ans = get<1>(*it) + 1;
        }
    }
    cout << ans;
    return 0;
}

