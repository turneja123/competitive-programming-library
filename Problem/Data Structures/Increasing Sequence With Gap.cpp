//https://dmoj.ca/problem/dcc1p4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    int z = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        z += a[i] == -1;
    }
    if (z + 1 >= k) {
        cout << "Infinity";
        return 0;
    }
    int l = 0, r = 1e9, ans = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        z = 0;
        map<long long, int> st;
        long long glob_k = 0; int glob_v = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] > 0) {
                int best = z + 1;
                if (st.empty()) {
                    st[a[i] - glob_k] = best - glob_v;
                    continue;
                }

                auto it = st.upper_bound(a[i] - mid - glob_k);
                if (it != st.begin()) {
                    it--;
                    best = max(best, it->second + glob_v + 1);
                }
                it = st.lower_bound(a[i] - glob_k);
                if (it == st.end() || it->first != a[i] - glob_k) {
                    it = st.insert(make_pair(a[i] - glob_k, best - glob_v)).first;
                } else {
                    it->second = max(it->second, best - glob_v);
                }
                best = it->second;
                it++;
                while (it != st.end() && it->second <= best) {
                    it = st.erase(it);
                }

            } else {
                z++;
                glob_k += mid;
                glob_v += 1;
            }
        }
        int lis = 0;
        for (auto [k, v] : st) {
            lis = max(lis, v + glob_v);
        }
        if (lis >= k) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans;
    return 0;
}
