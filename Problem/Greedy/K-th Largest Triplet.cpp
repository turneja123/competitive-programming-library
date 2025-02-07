//https://atcoder.jp/contests/abc391/tasks/abc391_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

long long a[N], b[N], c[N];

long long ans[N];

int main() {
    IOS;
    int n, kk;
    cin >> n >> kk;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    sort(a, a + n, greater<long long>());
    sort(b, b + n, greater<long long>());
    sort(c, c + n, greater<long long>());
    priority_queue<pair<long long, tuple<int, int, int>>> pq;
    pq.push(make_pair(a[0] * b[0] + a[0] * c[0] + b[0] * c[0], make_tuple(0, 0, 0)));
    int ind = 0;
    set<tuple<int, int, int>> st;

    while (pq.size()) {
        auto [i, j, k] = pq.top().second;
        long long val = pq.top().first;
        ans[ind++] = val;
        if (ind > kk) {
            break;
        }
        pq.pop();
        if (i + 1 < n && st.find(make_tuple(i + 1, j, k)) == st.end()) {
            st.insert(make_tuple(i + 1, j, k));
            long long cur = a[i + 1] * b[j] + a[i + 1] * c[k] + b[j] * c[k];
            pq.push(make_pair(cur, make_tuple(i + 1, j, k)));
        }
        if (j + 1 < n && st.find(make_tuple(i, j + 1, k)) == st.end()) {
            st.insert(make_tuple(i, j + 1, k));
            long long cur = a[i] * b[j + 1] + a[i] * c[k] + b[j + 1] * c[k];
            pq.push(make_pair(cur, make_tuple(i, j + 1, k)));
        }
        if (k + 1 < n && st.find(make_tuple(i, j, k + 1)) == st.end()) {
            st.insert(make_tuple(i, j, k + 1));
            long long cur = a[i] * b[j] + a[i] * c[k + 1] + b[j] * c[k + 1];
            pq.push(make_pair(cur, make_tuple(i, j, k + 1)));
        }
    }
    cout << ans[kk - 1];
    return 0;
}
