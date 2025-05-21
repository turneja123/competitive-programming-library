//https://www.codechef.com/problems/MODMAKEY
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 405;
const int M = 5e4 + 5;

int a[N];
bool seen[M];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, x, y;
        cin >> n >> x >> y;
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        int l = 0, r = n - 1, first = N;
        while (l <= r) {
            int mid = (l + r) / 2;
            queue<int> q;
            for (int i = 0; i <= mid; i++) {
                seen[x % a[i]] = true;
                q.push(x % a[i]);
            }
            while (q.size()) {
                auto x = q.front();
                q.pop();
                for (int j = 0; j <= mid; j++) {
                    if (!seen[x % a[j]]) {
                        seen[x % a[j]] = true;
                        q.push(x % a[j]);
                    }
                }
            }
            if (seen[y]) {
                r = mid - 1;
                first = mid;
            } else {
                l = mid + 1;
            }
            for (int i = 0; i < M; i++) {
                seen[i] = false;
            }
        }

        int mn = M;
        for (int i = 0; i < n; i++) {
            mn = min(mn, a[i]);
            if (mn <= y) {
                break;
            }
            if (first <= i) {
                ans.push_back(i);
            }
        }
        cout << ans.size() << endl;
        for (int i : ans) {
            cout << i + 1 << " ";
        }
        cout << endl;
        for (int i = 0; i < M; i++) {
            seen[i] = false;
        }
    }

    return 0;

}
