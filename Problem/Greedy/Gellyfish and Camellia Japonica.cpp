//https://codeforces.com/contest/2115/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int b[N];
int mx[N];
int sim[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            cin >> b[i];
            mx[i] = b[i];
        }
        vector<tuple<int, int, int>> v;
        for (int i = 0; i < q; i++) {
            int x, y, z;
            cin >> x >> y >> z;
            x--, y--, z--;
            v.push_back(make_tuple(x, y, z));
        }
        reverse(v.begin(), v.end());
        int can = 1;
        for (auto [x, y, z] : v) {
            mx[x] = max(mx[x], mx[z]);
            mx[y] = max(mx[y], mx[z]);
            if (x != z && y != z) {
                mx[z] = 0;
            }
        }
        for (int i = 0; i < n; i++) {
            sim[i] = mx[i];
        }
        reverse(v.begin(), v.end());
        for (auto [x, y, z] : v) {
            sim[z] = min(sim[x], sim[y]);
        }
        for (int i = 0; i < n; i++) {
            if (sim[i] != b[i]) {
                can = 0;
            }
        }
        if (!can) {
            cout << -1 << endl;
        } else {
            for (int i = 0; i < n; i++) {
                cout << mx[i] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
