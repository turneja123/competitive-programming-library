//https://qoj.ac/contest/2694/problem/15638
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int diff[N];
int ct[N];
int ans[N];

int main() {
    IOS;
    int n, k, q;
    cin >> n >> k >> q;
    vector<tuple<int, int, int, int>> a;
    set<int> st;
    for (int i = 0; i < q; i++) {
        int j, l, r;
        cin >> j >> l >> r;
        j--;
        st.insert(l);
        st.insert(r);
        a.push_back({l, r, j, i});
    }
    map<int, int> mp;
    for (int x : st) {
        mp[x] = mp.size();
    }
    for (int i = 0; i < q; i++) {
        get<0>(a[i]) = mp[get<0>(a[i])];
        get<1>(a[i]) = mp[get<1>(a[i])];

        auto [l, r, j, ind] = a[i];
        diff[l]++;
        diff[r + 1]--;
    }
    int s = 0;
    for (int i = 0; i < N; i++) {
        s += diff[i];
        ct[i] = s;
    }

    sort(a.begin(), a.end());
    priority_queue<int> pq;
    int mx = 0, cur = 0;
    for (int i = 0; i < q; i++) {
        auto [l, r, j, ind] = a[i];
        while (pq.size() && -pq.top() < l) {
            cur--;
            pq.pop();
        }
        if (ct[r] == n) {
            ans[ind] = 1;
            cur++;
            pq.push(-r);
        }
        mx = max(mx, cur);
    }
    if (mx > k) {
        cout << "impossible";
        return 0;
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i];
    }

    return 0;
}
