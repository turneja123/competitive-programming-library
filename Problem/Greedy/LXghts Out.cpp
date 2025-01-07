//https://dmoj.ca/problem/utso24p3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> sizes;
    char last = s[0]; int ct = 1;
    for (int i = 1; i < n; i++) {
        if (last != s[i]) {
            if (last == '1') {
                sizes.push_back(ct);
            }
            ct = 0;
            last = s[i];
        }
        ct++;
    }
    if (last == '1') {
        sizes.push_back(ct);
    }
    if (sizes.empty()) {
        cout << 0;
        return 0;
    }
    sort(sizes.begin(), sizes.end());
    if (n % 3 == 2 && sizes[0] == 2 && sizes[sizes.size() - 1] == 2 && k == 0 && sizes.size() == (n + 1) / 3) {
        cout << -1;
        return 0;
    }
    int ans = 0;
    for (int i = 0; i < sizes.size(); i++) {
        if (sizes[i] % 2 == 0) {
            if (k > 0) {
                k--;
                sizes[i]--;
            } else {
                ans += 2;
            }
        }
        ans += sizes[i];
    }
    ans = max(0, ans - k);
    cout << ans;

    return 0;
}
