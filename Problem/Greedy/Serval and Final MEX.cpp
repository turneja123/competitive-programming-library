//https://codeforces.com/contest/2085/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

void print(vector<pair<int, int>> &ans) {
    cout << ans.size() << endl;
    for (auto [x, y] : ans) {
        cout << x + 1 << " " << y + 1 << endl;
    }
    return;
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        vector<int> pos;
        vector<pair<int, int>> ans;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        if (a[n - 1] == 0) {
            ans.push_back(make_pair(n - 2, n - 1));
            a.pop_back();
            a.pop_back();
            a.push_back(1);
        }
        n = a.size();
        for (int i = 0; i < n; i++) {
            if (a[i] == 0) {
                pos.push_back(i);
            }
        }
        if (pos.empty()) {
            ans.push_back(make_pair(0, n - 1));
            print(ans);
            continue;
        }
        int l = pos[0];
        int r;
        if (pos.size() == 1) {
            r = l + 1;
        } else {
            r = pos.back();
        }
        ans.push_back(make_pair(l, r));
        n -= r - l;
        ans.push_back(make_pair(0, n - 1));
        print(ans);
    }
    return 0;
}
