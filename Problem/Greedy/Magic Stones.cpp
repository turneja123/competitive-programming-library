//https://codeforces.com/contest/1110/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    string ans = "Yes";
    if (a[0] != b[0] || a[n - 1] != b[n - 1]) {
        ans = "No";
    }
    vector<int> da, db;
    for (int i = 1; i < n; i++) {
        da.push_back(a[i] - a[i - 1]);
        db.push_back(b[i] - b[i - 1]);
    }
    sort(da.begin(), da.end());
    sort(db.begin(), db.end());
    for (int i = 0; i < n - 1; i++) {
        if (da[i] != db[i]) {
            ans = "No";
        }
    }
    cout << ans << endl;

    return 0;
}
