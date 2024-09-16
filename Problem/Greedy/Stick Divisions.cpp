//https://cses.fi/problemset/task/1161/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int n, d; long long ans = 0;
    cin >> d >> n;
    priority_queue<int> pq;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        pq.push(-a);
    }
    while (pq.size() > 1) {
        int x = -pq.top();
        pq.pop();
        int y = -pq.top();
        pq.pop();
        ans += x + y;
        pq.push(-(x + y));
    }
    cout << ans;
    return 0;
}
