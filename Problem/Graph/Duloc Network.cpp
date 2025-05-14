//https://algotester.com/en/ArchiveProblem/DisplayWithEditor/71131
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 205;

int query(vector<bool> &vis) {
    cout << "? ";
    for (int i = 0; i < vis.size(); i++) {
        cout << vis[i];
    }
    cout << endl;
    int t;
    cin >> t;
    return t;
}

int main() {
    //IOS;
    int n;
    cin >> n;
    vector<bool> visited(n, 0);
    visited[0] = true;
    for (int i = 1; i < n; i++) {
        int cur = query(visited);
        if (cur == 0) {
            cout << "! " << 0;
            return 0;
        }
        vector<int> v;
        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                v.push_back(j);
            }
        }
        int l = 0, r = v.size() - 1, node = 0;
        while (l <= r) {
            vector<bool> tmp1 = visited;
            vector<bool> tmp2(n, false);
            int mid = (l + r) / 2;
            for (int j = 0; j <= mid; j++) {
                tmp1[v[j]] = true;
                tmp2[v[j]] = true;
            }
            int x = query(tmp1), y = query(tmp2);
            if (cur + y == x) {
                l = mid + 1;
            } else {
                node = mid;
                r = mid - 1;
            }
        }
        visited[v[node]] = true;
    }
    cout << "! " << 1;
    return 0;
}
