#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

pair<int, int> a[N];
pair<int, int> seg[N];
int ans[N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
    for (int i = 0; i < n; i++) {
        cin >> seg[i].first >> seg[i].second;
    }
    sort(a, a + m);
    sort(seg, seg + n);
    priority_queue<int, vector<int>, greater<int>> pq;
    int j = 0;
    int cur = 0;
    for (int i = 0; i < m; i++) {
        while (j < n && seg[j].first <= a[i].first) {
            cur++;
            pq.push(seg[j++].second);
        }
        while (pq.size() && pq.top() < a[i].first) {
            cur--;
            pq.pop();
        }
        ans[a[i].second] = cur;
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
