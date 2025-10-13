//https://qoj.ac/contest/1452/problem/7933
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int ans[N];

int main() {
    IOS;
    int n;
    cin >> n;
    vector<pair<int, int>> ord;
    for (int i = 0; i < n; i++) {
        int j;
        cin >> j;
        a[i] = j;
        ord.push_back({j, i});
    }
    sort(ord.begin(), ord.end());
    for (int i = 0; i < n; i++) {
        ans[ord[i].second] = ord[n - 1 - i].second;
    }
    int can = 1, s = a[0] + a[ans[0]];
    for (int i = 0; i < n; i++) {
        if (a[i] + a[ans[i]] != s) {
            can = 0;
        }
    }
    if (!can) {
        cout << -1 << endl;
    } else {
        for (int i = 0; i < n; i++) {
            cout << ans[i] + 1 << " ";
        }
    }
    return 0;
}
