//https://www.codechef.com/START186A/problems/SEGTREECON
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e6;

bool seen[N];
int parent[N];
int leaf[N];
int ans[N];

priority_queue<pair<int, int>> pq;

int build(int node, int d, int n) {
    leaf[node] = N;
    if (d < n) {
        parent[2 * node + 1] = node;
        parent[2 * node + 2] = node;
        leaf[node] = min(leaf[node], build(2 * node + 1, d + 1, n));
        leaf[node] = min(leaf[node], build(2 * node + 2, d + 1, n));
    } else {
        leaf[node] = node;
    }
    return leaf[node];
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        int s = (1 << (n + 1)) - 1;
        if (s == k) {
            cout << "Yes" << endl;
            for (int i = 0; i < 1 << n; i++) {
                cout << 1;
            }
            cout << endl;
            continue;
        }
        if (s - k <= n) {
            cout << "No" << endl;
            continue;
        }
        cout << "Yes" << endl;
        build(0, 0, n);
        for (int i = (1 << n) - 1; i < s; i++) {
            ans[i] = 1;
        }
        int need = s;
        pq.push(make_pair(n + 1, leaf[0]));
        while (pq.size()) {
            auto [d, node] = pq.top();
            pq.pop();
            if (need - d < k) {
                continue;
            }
            need -= d;
            ans[node] = 0;
            int level = 0;
            while (1) {
                node = parent[node];
                if (seen[node]) {
                    break;
                }
                level++;
                seen[node] = true;
                pq.push(make_pair(level, leaf[2 * node + 2]));
                if (node == 0) {
                    break;
                }
            }
        }
        for (int i = (1 << n) - 1; i < s; i++) {
            cout << ans[i];
        }
        cout << endl;
        for (int i = 0; i < s; i++) {
            seen[i] = false;
        }

    }

    return 0;

}
