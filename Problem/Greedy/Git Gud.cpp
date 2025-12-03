//https://codeforces.com/contest/2157/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int B = 100;

bool comp(pair<int, int> a, pair<int, int> b) {
    if (a.first % B != b.first % B) {
        return a.first % B < b.first % B;
    }
    return a.first > b.first;
}

int main() {
    IOS;
    int n;
    cin >> n;
    if (n == 4) {
        cout << 4 << endl << "1 4" << endl << "3 1" << endl << "2 1" << endl << "3 1" << endl;
        return 0;
    }
    vector<pair<int, int>> ans1, ans2, ans3, ans;
    for (int i = 1; i < n; i++) {
        if (i % B != 0) {
            ans1.push_back({i, 1});
        }
    }
    sort(ans1.begin(), ans1.end(), comp);
    for (int i = B; i < n; i += B) {
        if ((i / B) % B != 0) {
            ans2.push_back({i / B, 1});
        }
    }
    sort(ans2.begin(), ans2.end(), comp);
    for (auto [x, d] : ans1) {
        ans.push_back({x, d});
    }
    for (auto [x, d] : ans2) {
        ans.push_back({x * B, d * B});
    }
    for (int i = B * B; i < n; i += B * B) {
        ans.push_back({i, B * B});
    }

    cout << ans.size() << endl;

    for (auto [x, d] : ans) {
        cout << x << " " << d << endl;
    }

    return 0;
}
