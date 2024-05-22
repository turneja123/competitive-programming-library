//https://judge.yosupo.jp/problem/static_range_frequency
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

long long a[N];

vector<int> pos[N];
gp_hash_table<int, int> mp;

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    set<int> st;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        st.insert(a[i]);
    }
    int m = st.size(); int j = 0;
    for (auto it = st.begin(); it != st.end(); ++it) {
        mp[*it] = j++;
    }
    for (int i = 0; i < n; i++) {
        pos[mp[a[i]]].push_back(i);
    }
    for (int i = 0; i < q; i++) {
        int l, r, k, ans = 0;
        cin >> l >> r >> k;
        r--;
        auto it = mp.find(k);
        if (it == mp.end()) {
            cout << 0 << endl;
            continue;
        }
        k = it->second; int m = pos[k].size();
        int lq = lower_bound(pos[k].begin(), pos[k].end(), l) - pos[k].begin();
        int rq = upper_bound(pos[k].begin(), pos[k].end(), r) - pos[k].begin();
        rq--;
        if (lq == m || lq > rq) {
            ans = 0;
        } else {
            ans = rq - lq + 1;
        }
        cout << ans << endl;
    }

    return 0;
}
