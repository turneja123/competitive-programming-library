//https://www.codechef.com/START166A/problems/COSTPERM
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int a[N];
int p[N];
bool vis[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
            p[a[i]] = i;
        }
        priority_queue<int> pq;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                int u = i; int l = 0;
                while (!vis[u]) {
                    vis[u] = true;
                    l++;
                    u = p[u];
                }
                pq.push(-l);

            }
        }
        long long ans = 0;
        while (pq.size() > 1) {
            int x = -pq.top();
            pq.pop();
            int y = -pq.top();
            pq.pop();
            ans += x + y;
            pq.push(-(x + y));
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            vis[i] = false;
        }
    }

    return 0;
}
