#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int seg[2 * N];
pair<pair<int, int>, int> v[N];
pair<pair<int, int>, pair<int, int>> q[N];
int ans[N];

void update(int pos, int val, int n) {
    pos += n;
    seg[pos] = val;
    while (pos > 1) {
        pos /= 2;
        seg[pos] = seg[2 * pos] + seg[2 * pos + 1];
    }
}

int rsq(int l, int r, int n) {
    l += n;
    r += n;
    int s = 0;
    while (l < r) {
        if (r % 2 == 1) {

            s += seg[--r];
        }
        if (l % 2 == 1) {
            s += seg[l++];
        }
        l /= 2;
        r /= 2;
    }
    return s;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> v[i].first.first >> v[i].first.second;
        v[i].second = i;
    }
    for (int i = 0; i < m; i++) {
        cin >> q[i].second.first >> q[i].second.second >> q[i].first.first;
        q[i].first.second = i;
    }
    sort(v, v + n);
    sort(q, q + m);
    priority_queue<pair<int, int>> pq;
    for (int i = 0, j = 0; i < m; i++) {
        int x = q[i].first.first;
        while (j < n && x >= v[j].first.first) {
            int ind = v[j].second;
            update(ind, 1, n);
            pq.push(make_pair(-v[j].first.second, ind));
            j++;
        }
        int c = pq.size() ? -((pq.top()).first) : 0;
        while (pq.size() && c < x) {
            update((pq.top()).second, 0, n);
            pq.pop();
            c = pq.size() ? -((pq.top()).first) : 0;
        }
        ans[q[i].first.second] = rsq(q[i].second.first - 1, q[i].second.second, n);
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i] << endl;
    }



    return 0;
}
